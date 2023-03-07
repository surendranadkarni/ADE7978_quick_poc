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
#define SSB_A D4


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


double IRMS_AVE;





void dready_irq(){
 DREADY_COUNT++;
}

void CF1_irq(){
 CF1_COUNT++;
}

void CF2_irq(){
 CF2_COUNT++;
}

void CF3_irq(){
 CF3_COUNT++;
}

void IRQ0_irq(){
  irq0_cnt++;
 ADE7978_SPI_WRITE(STATUS0,ADE7978_SPI_READ(STATUS0, 4),4);   // read and clear irq
}

void IRQ1_irq(){
  irq1_cnt++;
   ADE7978_SPI_WRITE(STATUS1,ADE7978_SPI_READ(STATUS1, 4),4);  // read and clear irq

}


void ADE7978_reg_config()
{

  //ADE7978_SPI_WRITE(AIGAIN, 0xFF800000, 4);
  ADE7978_SPI_WRITE(AIGAIN, 0x0, 4);
  Serial.print("AIGAIN = ");
  Serial.println(ADE7978_SPI_READ(AIGAIN,4), HEX);

  //ADE7978_SPI_WRITE(BIGAIN, 0xFF800000, 4);
  ADE7978_SPI_WRITE(BIGAIN, 0x0, 4);
  Serial.print("BIGAIN = ");
  Serial.println(ADE7978_SPI_READ(BIGAIN,4), HEX);

  //ADE7978_SPI_WRITE(CIGAIN, 0xFF800000, 4);
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

   ADE7978_SPI_WRITE(CF1DEN, 0x283d , 2);
  Serial.print("CF1DEN = ");
  Serial.println(ADE7978_SPI_READ(CF1DEN,2), HEX);

   ADE7978_SPI_WRITE(CF2DEN, 0x283d , 2);
  Serial.print("CF2DEN = ");
  Serial.println(ADE7978_SPI_READ(CF2DEN,2), HEX);

   ADE7978_SPI_WRITE(CF3DEN, 0x283d , 2);
  Serial.print("CF3DEN = ");
  Serial.println(ADE7978_SPI_READ(CF3DEN,2), HEX);





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
  Serial.print(ADE7978_SPI_READ(AWATT,4), HEX);
  Serial.print("  AWATTHR =  ");
  Serial.print(ADE7978_SPI_READ(AWATTHR,4), HEX);

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

  //attachInterrupt(digitalPinToInterrupt(DREADY), READ_RMS_AVERAGE_PRINT, FALLING );
  //attachInterrupt(digitalPinToInterrupt(DREADY), READ_SAMPLE_ON_IRQ, FALLING );
    attachInterrupt(digitalPinToInterrupt(DREADY),dready_irq,FALLING); // response about 5.2us
   attachInterrupt(digitalPinToInterrupt(CF1),CF1_irq,FALLING); // response about 5.2us
   attachInterrupt(digitalPinToInterrupt(CF2),CF2_irq,FALLING); // response about 5.2us
   attachInterrupt(digitalPinToInterrupt(CF3),CF3_irq,FALLING); // response about 5.2us
   attachInterrupt(digitalPinToInterrupt(IRQ0),IRQ0_irq,FALLING); // response about 5.2us
   attachInterrupt(digitalPinToInterrupt(IRQ1),IRQ1_irq,FALLING); // response about 5.2us

   Serial.println("Setup completed\n");
}


void loop() {

    if(millis()-last_millis >= 1000)
    {
      static uint32_t count = 0;
    Serial.print("CF1_COUNT = ");
    Serial.println(CF1_COUNT);
    Serial.print("CF2_COUNT = ");
    Serial.println(CF2_COUNT);
    Serial.print("CF3_COUNT = ");
    Serial.println(CF3_COUNT);
    Serial.print("irq1_cnt = ");
    Serial.println(irq1_cnt);
    Serial.print("irq0_cnt = ");
    Serial.println(irq0_cnt);

    Serial.print("DREADY_COUNT = ");
    Serial.println(DREADY_COUNT);

    last_millis = millis();
    READ_RMS_ENERGIES_PRINT();
    Serial.println(" ");
    Serial.println(count++);

    Serial.println(" ");
    }

}