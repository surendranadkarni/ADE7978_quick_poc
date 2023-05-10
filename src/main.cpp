#include <Arduino.h>
#include <SPI.h>
#include "ADE7978_reg.h"



void ADE7978_SPI_WRITE(uint16_t Address , uint32_t Data , uint8_t Number_of_bytes);
uint32_t ADE7978_SPI_READ (uint16_t Address, uint8_t Number_of_bytes);
void READ_RMS_ENERGIES_PRINT();
void ADE7978_reg_config();

#ifdef TARGET_ARDUINO_NANO33BLE
#define SPI_SPEED_HZ (800000U)
// NANO 33 BLE         ADE7978
//D4  > SSB_A   >> SSB
//D13  > sclk    >> SCLK
//D12  > miso    >> MISO
//D11  > mosi    >> MOSI

//D2  > PM1
//A7 > PM0

//D9 > IRQ0    >> IRQ0
//D8 > IRQ1    >> IRQ1

//D7  > RSTB    >> RESET_B
//D5 > DREADY/EVENT/CF4  >> ZX/DRDY_B

//D3  > CF1     >> CF1
//A6  > CF2     >> CF2
//A3 > CF3     >> CF3

//outputs
#define PM_0 D2
#define PM_1 PIN_A7

#define RESET_B D7
#define SSB_A D2


//inputs
#define CF1 D3
#define CF2 PIN_A6
#define CF3 PIN_A3
#define IRQ0 D9
#define IRQ1 D8
#define DREADY D5

#else // for Bluepill
    //SPI_1 Chip Select pin is PA4. You can change it to the STM32 pin you want.
//LED1=PC_13  SERIAL_TX=PA_2  I2C_SCL=PB_8  SPI_MOSI=PA_7  PWM_OUT=PB_3
//            SERIAL_RX=PA_3  I2C_SDA=PB_9  SPI_MISO=PA_6
//                                          SPI_SCK =PA_5


// bluepill         ADE7978
//PA4  > SSB_A   >> SSB
//PB5  > SSB_B
//PB4  > SSB_C

//PA5  > sclk    >> SCLK
//PA6  > miso    >> MISO
//PA7  > mosi    >> MOSI

//PA8  > PM1
//PB15 > PM0
//PB14 > IRQ0    >> IRQ0
//PB13 > IRQ1    >> IRQ1

//PB9  > scl
//PB8  > sda

//PB3  > RSTB    >> RESET_B
//PB12 > DREADY/EVENT/CF4  >> ZX/DRDY_B

//PB6  > CF1     >> CF1
//PB7  > CF2     >> CF2
//PC14 > CF3     >> CF3

//outputs
#define PM_0 PB15
#define PM_1 PA8
#define RESET_B PB3
#define SSB_A PA4


//inputs
#define CF1 PB6
#define CF2 PB7
#define CF3 PC14
#define IRQ0 PB14
#define IRQ1 PB13
#define DREADY PB12

#endif

byte data;

int CF1_COUNT = 0;
int CF2_COUNT = 0;
int CF3_COUNT = 0;
uint32_t irq0_cnt = 0;
uint32_t irq1_cnt = 0;
byte IRQ_STATUS = 0;
uint32_t DREADY_COUNT = 0;
int last_millis = 0;
int32_t temp;
float cf_freq =0;
uint32_t last_cf_edge;

double IRMS_AVE;


auto foo = false;


void dready_irq(){
 DREADY_COUNT++;
  //ADE7978_SPI_WRITE(STATUS1,ADE7978_SPI_READ(STATUS1, 4),4);  // read and clear irq
}

void CF1_irq(){
 CF1_COUNT++;
 cf_freq = 1/((micros()-last_cf_edge)/1000000.00);
 last_cf_edge = micros();
}

void CF2_irq(){
 CF2_COUNT++;
}

void CF3_irq(){
 CF3_COUNT++;
}


void IRQ0_irq(){
  irq0_cnt++;
  //auto val = ADE7978_SPI_READ(STATUS0, 4);
  //ADE7978_SPI_WRITE(STATUS0, ~val, 4);
}

void IRQ1_irq(){
  //ADE7978_SPI_WRITE(STATUS1,ADE7978_SPI_READ(STATUS1, 4),4);  // read and clear irq
  foo = true;
  irq1_cnt++;
}

void ADE7978_reg_config()
{

  ADE7978_SPI_WRITE(AIGAIN, 0x0, 4);
  Serial.print("AIGAIN = ");
  Serial.println(ADE7978_SPI_READ(AIGAIN,4), HEX);

  ADE7978_SPI_WRITE(BIGAIN, 0x0, 4);
  Serial.print("BIGAIN = ");
  Serial.println(ADE7978_SPI_READ(BIGAIN,4), HEX);

  ADE7978_SPI_WRITE(CIGAIN, 0x0, 4);
  Serial.print("CIGAIN = ");
  Serial.println(ADE7978_SPI_READ(CIGAIN,4), HEX);

  ADE7978_SPI_WRITE(AVGAIN, 0x0 , 4);
  Serial.print("AVGAIN = ");
  Serial.println(ADE7978_SPI_READ(AVGAIN,4), HEX);

  ADE7978_SPI_WRITE(BVGAIN, 0x0 , 4);
  Serial.print("BVGAIN = ");
  Serial.println(ADE7978_SPI_READ(BVGAIN,4), HEX);

  ADE7978_SPI_WRITE(CVGAIN, 0x0 , 4);
  Serial.print("CVGAIN = ");
  Serial.println(ADE7978_SPI_READ(CVGAIN,4), HEX);

  ADE7978_SPI_WRITE(CFMODE, 0x0088 , 2);
  Serial.print("CFMODE = ");
  Serial.println(ADE7978_SPI_READ(CFMODE,2), HEX);

  ADE7978_SPI_WRITE(COMPMODE, 0x0049 , 2);     // THIS IS SET FOR CHANNEL A ONLY FOR TESTING CALIBRATION
  Serial.print("COMPMODE = ");
  Serial.println(ADE7978_SPI_READ(COMPMODE,2), HEX);

  //setup for linecycle mode//

  ADE7978_SPI_WRITE(LINECYC,300,2);
  Serial.print("LINECYC = ");
  Serial.println(ADE7978_SPI_READ(LINECYC,2), HEX);

  ADE7978_SPI_WRITE(LCYCMODE, 0x0F ,1);  // enable ZXA for linecycle accumulation set bit (3) clr (4)(5) , disable read with reset clr bit(6) ,enable linecycle mode watt(0) var(1) va(2)
  Serial.print("LCYCMODE = ");
  Serial.println(ADE7978_SPI_READ(LCYCMODE,1), HEX);



  ADE7978_SPI_WRITE(RUN, 0x0001, 2); //write run bit
  Serial.print("RUN = ");
  Serial.println(ADE7978_SPI_READ(RUN,2), HEX);
}

void READ_RMS_ENERGIES_PRINT()
{
  Serial.print("  AIRM = ");
  Serial.print(ADE7978_SPI_READ(AIRMS,4), DEC);
  Serial.print("  AVRMS =  ");
  Serial.print(ADE7978_SPI_READ(AVRMS,4), DEC);
  Serial.print("  AWATT =  ");
  Serial.print(ADE7978_SPI_READ(AWATT,4), DEC);
  Serial.print("  AWATTHR =  ");
  Serial.print(ADE7978_SPI_READ(AWATTHR,4), DEC);
  Serial.println(" ");
  return;
  Serial.print("  BIRM = ");
  Serial.print(ADE7978_SPI_READ(BIRMS,4), DEC);
  Serial.print("  CIRMS =  ");
  Serial.print(ADE7978_SPI_READ(CIRMS,4), DEC);
  Serial.print("  AVRMS =  ");
  Serial.print(ADE7978_SPI_READ(AVRMS,4), DEC);
  Serial.print("  BVRMS =  ");
  Serial.print(ADE7978_SPI_READ(BVRMS,4), DEC);
  Serial.print("  CVRMS =  ");
  Serial.print(ADE7978_SPI_READ(CVRMS,4), DEC);
  Serial.print("  AWATT =  ");
  Serial.print(ADE7978_SPI_READ(AWATT,4), HEX);
  Serial.print("  BWATT =  ");
  Serial.print(ADE7978_SPI_READ(BWATT,4), HEX);
  Serial.print("  CWATT =  ");
  Serial.print(ADE7978_SPI_READ(CWATT,4), HEX);
  Serial.print(" ");
  Serial.println(" ");

}




void ADE7978_SPI_WRITE(uint16_t Address , uint32_t Data , uint8_t Number_of_bytes)
{
  uint8_t mhb = 0, hb = 0, mb = 0, lb = 0, p = 0;
  uint32_t j;

  j = Data & 0xff;
  lb = j;
  j = (Data & 0xff00) >> 8;
  mb = j;
  j = (Data & 0xff0000) >> 16;
  hb = j;
  j = (Data & 0xff000000) >> 24;
  mhb = j;

#ifdef SPI_HAS_TRANSACTION
  SPI.beginTransaction( SPISettings( SPI_SPEED_HZ, MSBFIRST, SPI_MODE3 ) );
#endif
  digitalWrite(SSB_A, LOW);   //set csb low


  data = SPI.transfer(0x00);  // send address with read bit modified

  data = SPI.transfer((Address & 0xFF00) >> 8);      // send upper address with write bit modified

  data = SPI.transfer(Address & 0xFF);       // send lower address with write bit modified

  //send requested number of bytes
  switch (Number_of_bytes) {
    case 4:
      data = SPI.transfer(mhb);
    case 3:
      data = SPI.transfer(hb);
    case 2:
      data = SPI.transfer(mb);
    case 1:
      data = SPI.transfer(lb);

    default:
      break;
  }

  digitalWrite(SSB_A, HIGH);  //set csb high
#ifdef SPI_HAS_TRANSACTION
  SPI.endTransaction();
#endif
}





// ADE7978_SPI_READ is working~ 7/7/15
uint32_t ADE7978_SPI_READ (uint16_t Address, uint8_t Number_of_bytes)
{
  uint8_t mhb = 0, hb = 0, mb = 0, lb = 0;
  uint32_t j;

#ifdef SPI_HAS_TRANSACTION
  SPI.beginTransaction( SPISettings( SPI_SPEED_HZ, MSBFIRST, SPI_MODE3 ) );
#endif
  digitalWrite(SSB_A, LOW);   //set csb low


  data = SPI.transfer(0x01);  // send address with read bit modified

  data = SPI.transfer((Address & 0xFF00) >> 8);      // send upper address with write bit modified

  data = SPI.transfer(Address & 0xFF);       // send lower address with write bit modified


  hb = 0;

  switch (Number_of_bytes) {
    case 4:
      mhb = SPI.transfer(0x0);   // dummy write
    case 3:
      hb = SPI.transfer(0x0);
    case 2:
      mb = SPI.transfer(0x0);
    case 1:
      lb = SPI.transfer(0x0);
    default:
      break;
  }

  digitalWrite(SSB_A, HIGH);  //set csb high
#ifdef SPI_HAS_TRANSACTION
  SPI.endTransaction();
#endif
  j = mhb << 24;
  j = j + (hb << 16);
  j = j + (mb << 8);
  j = j + lb;
  return j;
}

void calibrate_ade7978() {

  delay(10000); //wait for RMS to settle

  // enter values
  double V_TEST = 220.0;//volts RMS
  double I_TEST = 9;//Amps RMS
  double Power_factor = 1;
  int meter_constant = 1000;  //1000 imp/Kwh for cf output rate
  int Line_Freq = 50;
  int accumulation_time = 3; //sec


  double R1 = 1000000; //big resistor or sum of upper resisters
  double R2 = 1000; //small resistor

  double Shunt_value_in_ohms = 0.000300; // for 200uOhms

  //constants
#define  PMAX 26991271
#define  Sample_Rate 8000
#define  WTHR_Value 3
#define  I_channel_ADC_FS  .02209375
#define  V_channel_ADC_FS  .3535
#define  RMS_FS_Codes 3761808


  //calculated
  double Percent_FS_Voltage = (((R2 / (R1 + R2)) * V_TEST) / V_channel_ADC_FS);
  double Percent_FS_Current = (I_TEST * Shunt_value_in_ohms) / I_channel_ADC_FS;
  double V_Fullscale = V_TEST / Percent_FS_Voltage;
  double I_Fullscale = I_TEST / Percent_FS_Current;
  double Expected_CF_Freq = (meter_constant / 1000 * V_TEST * I_TEST * Power_factor) / 3600;
  double IRMS_LSB = 0;
  double VRMS_LSB = 0;
  double WATT_LSB = 0;
  double KWH_LSB = 0;
  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  //note the datasheet specs CF freq with wthr =3 and cfden=1 is 68.8Khz this may be incorrect and will cause errors in cf output after cfden is written
  //The number I get is 68651 x 3 for Wthr = 205953 which is what I am using below. After cfden is written expected cf is on cf pin
  //see page 8 of https://www.analog.com/media/en/technical-documentation/data-sheets/ade7978_7933_7932_7923.pdf spec table
  //see page 8 of https://www.analog.com/media/en/technical-documentation/application-notes/AN-1259.pdf
  // The 205593 comes from setting the  WTHR=3, CFDEN =1, AWATTOS = PMAX = 0x19BDAA7, AIGAIN = AVGAIN = 0xFF800000 , CFMODE= 0x0088, RUN = 0x1 measure CF freq with counter
  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  uint16_t CFDEN_CAL_VALUE = (uint16_t)((205953 / WTHR_Value) * Power_factor * Percent_FS_Voltage * Percent_FS_Current) / Expected_CF_Freq;
  int32_t AIGAIN_CAL_VALUE = (int32_t)((((RMS_FS_Codes * Percent_FS_Current) / (double)ADE7978_SPI_READ(AIRMS, 4)) - 1) * 8388608); // 2^23 = 8388608
  int32_t AVGAIN_CAL_VALUE = (int32_t)((((RMS_FS_Codes * Percent_FS_Voltage) / (double)ADE7978_SPI_READ(AVRMS, 4)) - 1) * 8388608); // 2^23 = 8388608


  Serial.println("");
  Serial.print("  V_TEST Used For Calibration = "); Serial.println(V_TEST);
  Serial.print("  I_TEST Used For Calibration = "); Serial.println(I_TEST);
  Serial.print("  Power_factor Used For Calibration = "); Serial.println(Power_factor);
  Serial.print("  Line_Freq Used For Calibration = "); Serial.println(Line_Freq);
  Serial.print("  Accumulation Time Used For Calibration = "); Serial.println(accumulation_time);
  Serial.println("");

  Serial.print("  Vlevel Calculated Register Value = "); Serial.println((uint32_t)((V_Fullscale / V_TEST) * 4000000), HEX);
  Serial.println("");

  ADE7978_SPI_WRITE(VLEVEL, (uint32_t)((V_Fullscale / V_TEST) * 4000000), 4);

  Serial.print("  V_TEST = "); Serial.print(Percent_FS_Voltage * 100, 2); Serial.print("% Fullscale"); Serial.print(" = "); Serial.print(V_channel_ADC_FS * Percent_FS_Voltage,4);Serial.print(" VRMS at ADC input and ");Serial.print(V_Fullscale, 2); Serial.println(" VRMS Fullscale");
  Serial.print("  I_TEST = "); Serial.print(Percent_FS_Current * 100, 2); Serial.print("% Fullscale"); Serial.print(" = "); Serial.print(I_channel_ADC_FS * Percent_FS_Current,4);Serial.print(" VRMS at ADC input and ");Serial.print(I_Fullscale, 2); Serial.println(" IRMS Fullscale");



  Serial.println("");
  Serial.print("  Expected_CF_Freq = "); Serial.println(Expected_CF_Freq, 6);
  Serial.print("  CFDEN_CAL_VALUE = "); Serial.println(CFDEN_CAL_VALUE);
  Serial.println("");

  ADE7978_SPI_WRITE(CF1DEN, CFDEN_CAL_VALUE, 2);
  ADE7978_SPI_WRITE(CF2DEN, CFDEN_CAL_VALUE, 2);
  ADE7978_SPI_WRITE(CF3DEN, CFDEN_CAL_VALUE, 2);

  Serial.print("  AIRMS Expected = "); Serial.println(Percent_FS_Current * RMS_FS_Codes ,0);
  Serial.print("  AVRMS Expected = "); Serial.println(Percent_FS_Voltage * RMS_FS_Codes ,0);
  Serial.print("  AIRMS RAW = "); Serial.println(ADE7978_SPI_READ(AIRMS, 4), DEC);
  Serial.print("  AVRMS RAW = "); Serial.println(ADE7978_SPI_READ(AVRMS, 4), DEC);
  Serial.println("");
  Serial.print("  AIGAIN_CAL_VALUE "); Serial.println(AIGAIN_CAL_VALUE);
  Serial.print("  AVGAIN_CAL_VALUE "); Serial.println(AVGAIN_CAL_VALUE);
  Serial.println("");

  ADE7978_SPI_WRITE(AIGAIN, AIGAIN_CAL_VALUE, 4);
  ADE7978_SPI_WRITE(AVGAIN, AVGAIN_CAL_VALUE, 4);

  ADE7978_SPI_WRITE(AWATTHR, 0, 4);

  ADE7978_SPI_WRITE(LINECYC, (accumulation_time / (1.00 / Line_Freq / 2)), 2); // 300 half linecycles or 3 sec at 50Hz  360 half line cycles at 60hz for 3 sec

  Serial.print("  LINECYCLES for "); Serial.print(accumulation_time); Serial.print(" SEC accumulation time = "); Serial.println(accumulation_time / (1.00 / Line_Freq / 2), 0);

  IRMS_LSB = I_TEST / (RMS_FS_Codes * Percent_FS_Current);
  VRMS_LSB = V_TEST / (RMS_FS_Codes * Percent_FS_Voltage);
  WATT_LSB = (V_TEST * I_TEST) / (PMAX * Percent_FS_Current * Percent_FS_Voltage);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  // you can use expected (WATTHR / watthr register read) to calculate KWH/LSB.
  /*
    delay(accumulation_time * 1000);
    //  need to wait for next accumulation time Watthr used for calculation
    ADE7978_SPI_WRITE(STATUS0,32,4);
    while( (ADE7978_SPI_READ(STATUS0, 4) & 32) != 32)
       {
          ADE7978_SPI_WRITE(STATUS0,32,4);
          KWH_LSB = (V_TEST * I_TEST * Power_factor * accumulation_time) / (ADE7978_SPI_READ(AWATTHR,4) * 3600);
       }
  */


  //Or KWH/LSB can be calculated by using expected values and the signal chain. (watthr over accumulation time) / (calculated watthr register over accumulation time )

  KWH_LSB = ((double)(((V_TEST * I_TEST * Power_factor) / 3600) * accumulation_time) / (((double)(PMAX * Percent_FS_Current * Percent_FS_Voltage  * 1024000 * accumulation_time )) / ((double)(WTHR_Value * pow(2, 27))))); // (watthr over accumulation time) / (calculated watthr register over accumulation time )
  //Serial.print("calculated KWH/LSB = "); Serial.println(KWH_LSB, 8);
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


  Serial.println("");
  Serial.print("  IRMS_LSB = "); Serial.println(IRMS_LSB, 8);
  Serial.print("  VRMS_LSB = "); Serial.println(VRMS_LSB, 8);
  Serial.print("  WATT_LSB = "); Serial.println(WATT_LSB, 8);
  Serial.print("  KWH_LSB  = "); Serial.println(KWH_LSB, 8);
  Serial.println("");

  delay(10000);

  Serial.print("  Cf Frequency Measured By Micro = "); Serial.print(cf_freq, 6); Serial.println(" HZ "); Serial.println("");
  Serial.println("");
  last_millis = millis();
  while (1) {
    if ( (ADE7978_SPI_READ(STATUS0, 4) & 32) == 32)
    {
      ADE7978_SPI_WRITE(STATUS0, 32, 4);

      Serial.print("  Updated Every "); Serial.print(accumulation_time / (1.00 / Line_Freq / 2),0); Serial.println(" Half Lincycles ");
      Serial.println("");
      Serial.print(millis() - last_millis);
      last_millis = millis();
      Serial.println("MilliSeconds \n");
      Serial.print("  AIRMS = "); Serial.print(ADE7978_SPI_READ(AIRMS, 4) * IRMS_LSB,4); Serial.println(" IRMS");
      Serial.print("  AVRMS = "); Serial.print(ADE7978_SPI_READ(AVRMS, 4) * VRMS_LSB,4); Serial.println(" VRMS");
      Serial.print("  AWATT = "); Serial.print(ADE7978_SPI_READ(AWATT, 4) * 16 * WATT_LSB,4); Serial.println(" WATTS"); //div by 2^4 in figure 79 pg 57
      //https://www.analog.com/media/en/technical-documentation/data-sheets/ade7978_7933_7932_7923.pdf
      Serial.print("  AWATTHR = "); Serial.print(ADE7978_SPI_READ(AWATTHR, 4) * KWH_LSB,4); Serial.println(" KW/HR");
      Serial.println("");
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  SPI.begin(); //Initialize the SPI_1 port.
#ifndef SPI_HAS_TRANSACTION
  SPI.setBitOrder(MSBFIRST); // Set the SPI_1 bit order
  SPI.setDataMode(SPI_MODE3); //Set the SPI_2 data mode 0
  SPI.setClockDivider(SPI_CLOCK_DIV16);      // Slow speed (72 / 16 = 4.5 MHz SPI_1 speed)
#endif
  delay(1000);
  //outputs
  pinMode(SSB_A, OUTPUT);
  pinMode(RESET_B, OUTPUT);
  pinMode(PM_0, OUTPUT);
  pinMode(PM_1, OUTPUT);

 //inputs
  pinMode(CF1, INPUT);
  pinMode(CF2, INPUT);
  pinMode(CF3, INPUT);
  pinMode(IRQ0, INPUT);
  pinMode(IRQ1, INPUT);
  pinMode(DREADY, INPUT_PULLUP);  // used for IRQ


  digitalWrite(SSB_A, HIGH);
  digitalWrite(RESET_B, HIGH);

  //reset part
  digitalWrite(RESET_B, LOW);
  delay(10);
  digitalWrite(RESET_B, HIGH);
  Serial.println("Waiting for chip to start\n");
  last_millis = millis();
  while( digitalRead(IRQ1) == 1);        //wait for reset done
  auto time_elapsed = millis()-last_millis;
  Serial.print("Took time:");
  Serial.println(time_elapsed);
  ADE7978_SPI_WRITE(STATUS1,0xffffffff,0x4);

  //set spi port TOGGLE SSB 3 TIMES
  digitalWrite(SSB_A, LOW);
  delay(1);
  digitalWrite(SSB_A, HIGH);
  delay(1);
  digitalWrite(SSB_A, LOW);
  delay(1);
  digitalWrite(SSB_A, HIGH);
  delay(1);
  digitalWrite(SSB_A, LOW);
  delay(1);
  digitalWrite(SSB_A, HIGH);

  delay(2000);



  ADE7978_reg_config();
   ADE7978_SPI_WRITE(STATUS0,ADE7978_SPI_READ(STATUS0, 4),4);   //important after settign up attach IRQ0
   ADE7978_SPI_WRITE(STATUS1,ADE7978_SPI_READ(STATUS1, 4),4);  //important after settign up attach IRQ1
  //attachInterrupt(digitalPinToInterrupt(DREADY), READ_RMS_AVERAGE_PRINT, FALLING );
  //attachInterrupt(digitalPinToInterrupt(DREADY), READ_SAMPLE_ON_IRQ, FALLING );
    attachInterrupt(digitalPinToInterrupt(DREADY),dready_irq,FALLING); // response about 5.2us
   attachInterrupt(digitalPinToInterrupt(CF1),CF1_irq,FALLING); // response about 5.2us
   //attachInterrupt(digitalPinToInterrupt(CF2),CF2_irq,FALLING); // response about 5.2us
   //attachInterrupt(digitalPinToInterrupt(CF3),CF3_irq,FALLING); // response about 5.2us
   //attachInterrupt(digitalPinToInterrupt(IRQ0),IRQ0_irq,FALLING); // response about 5.2us
   //attachInterrupt(digitalPinToInterrupt(IRQ1),IRQ1_irq,FALLING); // response about 5.2us
  //ADE7978_SPI_WRITE(MASK1, 0x200 , 4);  //200 hex = channel a zerocross IRQ
  //Serial.print("MASK1 = ");
  //Serial.println(ADE7978_SPI_READ(MASK1,4), HEX);

   Serial.println("Setup completed\n");
}

void loop() {

    calibrate_ade7978();
    if(foo)
    {
      foo = false;
      ADE7978_SPI_WRITE(STATUS1,ADE7978_SPI_READ(STATUS1, 4),4);  //important after settign up attach IRQ1
    }



     if(millis()-last_millis >= 1000)
    {
      if( (ADE7978_SPI_READ(STATUS0, 4) & 32) == 32)
      {
      ADE7978_SPI_WRITE(STATUS0,32,4);
      READ_RMS_ENERGIES_PRINT();
      }
      Serial.print("CF1_COUNT = ");
      Serial.println(CF1_COUNT);
      Serial.print("CF2_COUNT = ");
      Serial.println(CF2_COUNT);
      Serial.print("CF3_COUNT = ");
      Serial.println(CF3_COUNT);
      Serial.print("DREADY CNT = ");
      Serial.println(DREADY_COUNT);
      Serial.print("irq1_cnt = ");
      Serial.println(irq1_cnt);
      Serial.print("irq0_cnt = ");
      Serial.println(irq0_cnt);
      last_millis = millis();
      Serial.println(" ");
    }


}