#define	AIGAIN		0x4380	//	R/W	24	32	ZPSE	S	0x000000	Phase	A	current	gain	adjust.													
#define	AVGAIN		0x4381	//	R/W	24	32	ZPSE	S	0x000000	Phase	A	voltage	gain	adjust.													
#define	AV2GAIN		0x4382	//	R/W	24	32	ZPSE	S	0x000000	Phase	A	V2P	channel	gain													
#define	BIGAIN		0x4383	//	R/W	24	32	ZPSE	S	0x000000	Phase	B	current	gain	adjust.													
#define	BVGAIN		0x4384	//	R/W	24	32	ZPSE	S	0x000000	Phase	B	voltage	gain	adjust.													
#define	BV2GAIN		0x4385	//	R/W	24	32	ZPSE	S	0x000000	Phase	B	V2P	channel	gain													
#define	CIGAIN		0x4386	//	R/W	24	32	ZPSE	S	0x000000	Phase	C	current	gain	adjust.													
#define	CVGAIN		0x4387	//	R/W	24	32	ZPSE	S	0x000000	Phase	C	voltage	gain	adjust.													
#define	CV2GAIN		0x4388	//	R/W	24	32	ZPSE	S	0x000000	Phase	C	V2P	channel	gain													
#define	NIGAIN		0x4389	//	R/W	24	32	ZPSE	S	0x000000	Neutral	current	gain	adjust.														
#define	NVGAIN		0x438A	//	R/W	24	32	ZPSE	S	0x000000	Neutral	line	V1P	channel	gain													
#define	NV2GAIN		0x438B	//	R/W	24	32	ZPSE	S	0x000000	Neutral	line	V2P	channel	gain													
#define	AIRMSOS		0x438C	//	R/W	24	32	ZPSE	S	0x000000	Phase	A	current	rms	offset.													
#define	AVRMSOS		0x438D	//	R/W	24	32	ZPSE	S	0x000000	Phase	A	voltage	rms	offset.													
#define	AV2RMSOS	0x438E	//	R/W	24	32	ZPSE	S	0x000000	Phase	A	V2P	voltage	rms														
#define	BIRMSOS		0x438F	//	R/W	24	32	ZPSE	S	0x000000	Phase	B	current	rms	offset.													
#define	BVRMSOS		0x4390	//	R/W	24	32	ZPSE	S	0x000000	Phase	B	voltage	rms	offset.													
#define	BV2RMSOS	0x4391	//	R/W	24	32	ZPSE	S	0x000000	Phase	B	V2P	voltage	rms														
#define	CIRMSOS		0x4392	//	R/W	24	32	ZPSE	S	0x000000	Phase	C	current	rms	offset.													
#define	CVRMSOS		0x4393	//	R/W	24	32	ZPSE	S	0x000000	Phase	C	voltage	rms	offset.													
#define	CV2RMSOS	0x4394	//	R/W	24	32	ZPSE	S	0x000000	Phase	C	V2P	voltage	rms														
#define	NIRMSOS		0x4395	//	R/W	24	32	ZPSE	S	0x000000	Neutral	current	rms	offset.														
#define	NVRMSOS		0x4396	//	R/W	24	32	ZPSE	S	0x000000	Neutral	line	V1P	voltage	rms													
#define	NV2RMSOS	0x4397	//	R/W	24	32	ZPSE	S	0x000000	Neutral	line	V2P	voltage	rms														
#define	ISUMLVL		0x4398	//	R/W	24	32	ZPSE	S	0x000000	Threshold	used	to	compare	the													
#define	APGAIN		0x4399	//	R/W	24	32	ZPSE	S	0x000000	Phase	A	power	gain	adjust.													
#define	BPGAIN		0x439A	//	R/W	24	32	ZPSE	S	0x000000	Phase	B	power	gain	adjust.													
#define	CPGAIN		0x439B	//	R/W	24	32	ZPSE	S	0x000000	Phase	C	power	gain	adjust.													
#define	AWATTOS		0x439C	//	R/W	24	32	ZPSE	S	0x000000	Phase	A	total	active	power													
#define	BWATTOS		0x439D	//	R/W	24	32	ZPSE	S	0x000000	Phase	B	total	active	power													
#define	CWATTOS		0x439E	//	R/W	24	32	ZPSE	S	0x000000	Phase	C	total	active	power													
#define	AVAROS		0x439F	//	R/W	24	32	ZPSE	S	0x000000	Phase	A	total	reactive	power													
#define	BVAROS		0x43A0	//	R/W	24	32	ZPSE	S	0x000000	Phase	B	total	reactive	power													
#define	CVAROS		0x43A1	//	R/W	24	32	ZPSE	S	0x000000	Phase	C	total	reactive	power													
#define	VLEVEL		0x43A2	//	R/W	24	32	ZPSE	S	0x000000	Register	used	in	the	algorithm													
#define	AFWATTOS	0x43A3	//	R/W	24	32	ZPSE	S	0x000000	Phase	A	fundamental	active	power														
#define	BFWATTOS	0x43A4	//	R/W	24	32	ZPSE	S	0x000000	Phase	B	fundamental	active	power														
#define	CFWATTOS	0x43A5	//	R/W	24	32	ZPSE	S	0x000000	Phase	C	fundamental	active	power														
#define	AFVAROS		0x43A6	//	R/W	24	32	ZPSE	S	0x000000	Phase	A	fundamental	reactive	power													
#define	BFVAROS		0x43A7	//	R/W	24	32	ZPSE	S	0x000000	Phase	B	fundamental	reactive	power													
#define	CFVAROS		0x43A8	//	R/W	24	32	ZPSE	S	0x000000	Phase	C	fundamental	reactive	power													
#define	AFIRMSOS	0x43A9	//	R/W	24	32	ZPSE	S	0x000000	Phase	A	fundamental	current	rms														
#define	BFIRMSOS	0x43AA	//	R/W	24	32	ZPSE	S	0x000000	Phase	B	fundamental	current	rms														
#define	CFIRMSOS	0x43AB	//	R/W	24	32	ZPSE	S	0x000000	Phase	C	fundamental	current	rms														
#define	AFVRMSOS	0x43AC	//	R/W	24	32	ZPSE	S	0x000000	Phase	A	fundamental	voltage	rms														
#define	BFVRMSOS	0x43AD	//	R/W	24	32	ZPSE	S	0x000000	Phase	B	fundamental	voltage	rms														
#define	CFVRMSOS	0x43AE	//	R/W	24	32	ZPSE	S	0x000000	Phase	C	fundamental	voltage	rms														
#define	TEMPCO		0x43AF	//	R/W	24	32	ZPSE	S	0x000000	Temperature	coefficient	of	the	shunt.													
#define	ATEMP0		0x43B0	//	R/W	24	32	ZPSE	S	0x000000	Phase	A	ADE7933/ADE7932	ambient	temperature													
#define	BTEMP0		0x43B1	//	R/W	24	32	ZPSE	S	0x000000	Phase	B	ADE7933/ADE7932	ambient	temperature													
#define	CTEMP0		0x43B2	//	R/W	24	32	ZPSE	S	0x000000	Phase	C	ADE7933/ADE7932	ambient	temperature													
#define	NTEMP0		0x43B3	//	R/W	24	32	ZPSE	S	0x000000	Neutral	line	ADE7923	or	ADE7933/ADE7932													
#define	ATGAIN		0x43B4	//	R/W	24	32	ZPSE	S	0x000000	Phase	A	temperature	gain	adjust.													
#define	BTGAIN		0x43B5	//	R/W	24	32	ZPSE	S	0x000000	Phase	B	temperature	gain	adjust.													
#define	CTGAIN		0x43B6	//	R/W	24	32	ZPSE	S	0x000000	Phase	C	temperature	gain	adjust.													
#define	NTGAIN		0x43B7	//	R/W	24	32	ZPSE	S	0x000000	Neutral	line	temperature	gain	adjust.													
																												
#define	AIRMS		0x43C0	//	R	24	32	ZP	S	N/A	Phase	A	current	rms	value.													
#define	AVRMS		0x43C1	//	R	24	32	ZP	S	N/A	Phase	A	voltage	rms	value.													
#define	AV2RMS	0x43C2	//	R	24	32	ZP	S	N/A	Phase	A	V2P	voltage	rms													
#define	BIRMS		0x43C3	//	R	24	32	ZP	S	N/A	Phase	B	current	rms	value.													
#define	BVRMS		0x43C4	//	R	24	32	ZP	S	N/A	Phase	B	voltage	rms	value.													
#define	BV2RMS	0x43C5	//	R	24	32	ZP	S	N/A	Phase	B	V2P	voltage	rms													
#define	CIRMS		0x43C6	//	R	24	32	ZP	S	N/A	Phase	C	current	rms	value.													
#define	CVRMS		0x43C7	//	R	24	32	ZP	S	N/A	Phase	C	voltage	rms	value.													
#define	CV2RMS	0x43C8	//	R	24	32	ZP	S	N/A	Phase	C	V2P	voltage	rms													
#define	NIRMS		0x43C9	//	R	24	32	ZP	S	N/A	Neutral	current	rms	value.														
#define	ISUM		0x43CA	//	R	28	32	ZP	S	N/A	Sum	of	"IAWV,"	"IBWV,"	and													
#define	ATEMP		0x43CB	//	R	24	32	ZP	S	N/A	Phase	A	ADE7933/ADE7932	temperature.														
#define	BTEMP		0x43CC	//	R	24	32	ZP	S	N/A	Phase	B	ADE7933/ADE7932	temperature.														
#define	CTEMP		0x43CD	//	R	24	32	ZP	S	N/A	Phase	C	ADE7933/ADE7932	temperature.														
#define	NTEMP		0x43CE	//	R	24	32	ZP	S	N/A	Neutral	line	ADE7923	or	ADE7933/ADE7932													
//#define	Reserved	0xE203	//	R/W	16	U	0x0000	This	address	should	not	be	written	for														
#define	RUN		  0xE228	//	R/W	16	U	0x0000	The	run	register	starts	and	stops	the																																								
																												
#define	AWATTHR		0xE400	//	R	32	S	0x00000000	Phase	A	total	active	energy	accumulation.														
#define	BWATTHR		0xE401	//	R	32	S	0x00000000	Phase	B	total	active	energy	accumulation.														
#define	CWATTHR		0xE402	//	R	32	S	0x00000000	Phase	C	total	active	energy	accumulation.														
#define	AFWATTHR	0xE403	//	R	32	S	0x00000000	Phase	A	fundamental	active	energy	accumulation.															
#define	BFWATTHR	0xE404	//	R	32	S	0x00000000	Phase	B	fundamental	active	energy	accumulation.															
#define	CFWATTHR	0xE405	//	R	32	S	0x00000000	Phase	C	fundamental	active	energy	accumulation.															
#define	AVARHR		0xE406	//	R	32	S	0x00000000	Phase	A	total	reactive	energy	accumulation.														
#define	BVARHR		0xE407	//	R	32	S	0x00000000	Phase	B	total	reactive	energy	accumulation.														
#define	CVARHR		0xE408	//	R	32	S	0x00000000	Phase	C	total	reactive	energy	accumulation.														
#define	AFVARHR		0xE409	//	R	32	S	0x00000000	Phase	A	fundamental	reactive	energy	accumulation.														
#define	BFVARHR		0xE40A	//	R	32	S	0x00000000	Phase	B	fundamental	reactive	energy	accumulation.														
#define	CFVARHR		0xE40B	//	R	32	S	0x00000000	Phase	C	fundamental	reactive	energy	accumulation.														
#define	AVAHR		  0xE40C	//	R	32	S	0x00000000	Phase	A	apparent	energy	accumulation.															
#define	BVAHR		  0xE40D	//	R	32	S	0x00000000	Phase	B	apparent	energy	accumulation.															
#define	CVAHR		  0xE40E	//	R	32	S	0x00000000	Phase	C	apparent	energy	accumulation.															
																												
#define	IPEAK		  0xE500	//	R	32	32	U	N/A	Current	peak	register	(see	Figure	70													
#define	VPEAK		  0xE501	//	R	32	32	U	N/A	Voltage	peak	register	(see	Figure	70													
#define	STATUS0		0xE502	//	R/W	32	32	U	N/A	Interrupt	Status	Register	0	(see	Table													
#define	STATUS1		0xE503	//	R/W	32	32	U	N/A	Interrupt	Status	Register	1	(see	Table													
																												
#define	OILVL		0xE507	//	R/W	24	32	ZP	U	0xFFFFFF	Overcurrent	threshold.																
#define	OVLVL		0xE508	//	R/W	24	32	ZP	U	0xFFFFFF	Overvoltage	threshold.																
#define	SAGLVL	0xE509	//	R/W	24	32	ZP	U	0x000000	Voltage	sag	level	threshold.														
#define	MASK0		0xE50A	//	R/W	32	32	U	0x00000000	Interrupt	Enable	Register	0	(see	Table													
#define	MASK1		0xE50B	//	R/W	32	32	U	0x00000000	Interrupt	Enable	Register	1	(see	Table													
#define	IAWV		0xE50C	//	R	24	32	SE	S	N/A	Instantaneous	value	of	Phase	A													
#define	IBWV		0xE50D	//	R	24	32	SE	S	N/A	Instantaneous	value	of	Phase	B													
#define	ICWV		0xE50E	//	R	24	32	SE	S	N/A	Instantaneous	value	of	Phase	C													
#define	INWV		0xE50F	//	R	24	32	SE	S	N/A	Instantaneous	value	of	neutral	current.													
#define	VAWV		0xE510	//	R	24	32	SE	S	N/A	Instantaneous	value	of	Phase	A													
#define	VBWV		0xE511	//	R	24	32	SE	S	N/A	Instantaneous	value	of	Phase	B													
#define	VCWV		0xE512	//	R	24	32	SE	S	N/A	Instantaneous	value	of	Phase	C													
#define	VA2WV		0xE513	//	R	24	32	SE	S	N/A	Instantaneous	value	of	Phase	A													
#define	VB2WV		0xE514	//	R	24	32	SE	S	N/A	Instantaneous	value	of	Phase	B													
#define	VC2WV		0xE515	//	R	24	32	SE	S	N/A	Instantaneous	value	of	Phase	C													
#define	VNWV		0xE516	//	R	24	32	SE	S	N/A	Instantaneous	value	of	neutral	line													
#define	VN2WV		0xE517	//	R	24	32	SE	S	N/A	Instantaneous	value	of	neutral	line													
#define	AWATT		0xE518	//	R	24	32	SE	S	N/A	Instantaneous	value	of	Phase	A													
#define	BWATT		0xE519	//	R	24	32	SE	S	N/A	Instantaneous	value	of	Phase	B													
#define	CWATT		0xE51A	//	R	24	32	SE	S	N/A	Instantaneous	value	of	Phase	C													
#define	AVAR		0xE51B	//	R	24	32	SE	S	N/A	Instantaneous	value	of	Phase	A													
#define	BVAR		0xE51C	//	R	24	32	SE	S	N/A	Instantaneous	value	of	Phase	B													
#define	CVAR		0xE51D	//	R	24	32	SE	S	N/A	Instantaneous	value	of	Phase	C													
#define	AVA		  0xE51E	//	R	24	32	SE	S	N/A	Instantaneous	value	of	Phase	A													
#define	BVA		  0xE51F	//	R	24	32	SE	S	N/A	Instantaneous	value	of	Phase	B													
#define	CVA		  0xE520	//	R	24	32	SE	S	N/A	Instantaneous	value	of	Phase	C													
#define	AVTHD		0xE521	//	R	24	32	ZP	S	N/A	Total	harmonic	distortion	of	Phase													
#define	AITHD		0xE522	//	R	24	32	ZP	S	N/A	Total	harmonic	distortion	of	Phase													
#define	BVTHD		0xE523	//	R	24	32	ZP	S	N/A	Total	harmonic	distortion	of	Phase													
#define	BITHD		0xE524	//	R	24	32	ZP	S	N/A	Total	harmonic	distortion	of	Phase													
#define	CVTHD		0xE525	//	R	24	32	ZP	S	N/A	Total	harmonic	distortion	of	Phase													
#define	CITHD		0xE526	//	R	24	32	ZP	S	N/A	Total	harmonic	distortion	of	Phase													
																												
#define	NVRMS		  0xE530	//	R	24	32	ZP	S	N/A	Neutral	line	V1P	voltage	rms													
#define	NV2RMS		0xE531	//	R	24	32	ZP	S	N/A	Neutral	line	V2P	voltage	rms													
#define	CHECKSUM	0xE532	//	R	32	32	U	0x6BF87803	Checksum	verification	(see	the	Checksum	Register														
#define	VNOM		  0xE533	//	R/W	24	32	ZP	S	0x000000	Nominal	phase	voltage	rms	used													
#define	AFIRMS		0xE537	//	R	24	32	ZP	S	N/A	Phase	A	fundamental	current	rms													
#define	AFVRMS		0xE538	//	R	24	32	ZP	S	N/A	Phase	A	fundamental	voltage	rms													
#define	BFIRMS		0xE539	//	R	24	32	ZP	S	N/A	Phase	B	fundamental	current	rms													
#define	BFVRMS		0xE53A	//	R	24	32	ZP	S	N/A	Phase	B	fundamental	voltage	rms													
#define	CFIRMS		0xE53B	//	R	24	32	ZP	S	N/A	Phase	C	fundamental	current	rms													
#define	CFVRMS		0xE53C	//	R	24	32	ZP	S	N/A	Phase	C	fundamental	voltage	rms													
																												
#define	LAST_RWDATA32	0xE5FF	//	RWDATA32	R	32	32	U	N/A	Contains	the	data	from	the													
#define	PHSTATUS	0xE600	//	R	16	16	U	N/A	Phase	peak	register	(see	Table	49).														
#define	ANGLE0		0xE601	//	R	16	16	U	N/A	Time	Delay	0	(see	the	Time													
#define	ANGLE1		0xE602	//	R	16	16	U	N/A	Time	Delay	1	(see	the	Time section	Phases	//	for	more	information).								
#define	ANGLE2		0xE603	//	R	16	16	U	N/A	Time	Delay	2	(see	the	Time													
#define	PHNOLOAD	0xE608	//	R	16	16	U	N/A	Phase	no	load	register	(see	Table														
#define	LINECYC		0xE60C	//	R/W	16	16	U	0xFFFF	Line	cycle	accumulation	mode	count.														
#define	ZXTOUT		0xE60D	//	R/W	16	16	U	0xFFFF	Zero-crossing	timeout	count.																
#define	COMPMODE	0xE60E	//	R/W	16	16	U	0x01FF	Computation	mode	register	(see	Table	51).														
#define	Reserved	0xE60F	//	This	address	should	not	be	written	for	proper	operation.																
#define	CFMODE		0xE610	//	R/W	16	16	U	0x0E88	CFx	configuration	register	(see	Table	52).													
#define	CF1DEN		0xE611	//	R/W	16	16	U	0x0000	CF1	denominator.																	
#define	CF2DEN		0xE612	//	R/W	16	16	U	0x0000	CF2	denominator.																	
#define	CF3DEN		0xE613	//	R/W	16	16	U	0x0000	CF3	denominator.																	
#define	APHCAL		0xE614	//	R/W	10	16	ZP	U	0x0000	Phase	calibration	of	Phase	A													
#define	BPHCAL		0xE615	//	R/W	10	16	ZP	U	0x0000	Phase	calibration	of	Phase	B													
#define	CPHCAL		0xE616	//	R/W	10	16	ZP	U	0x0000	Phase	calibration	of	Phase	C													
#define	PHSIGN		0xE617	//	R	16	16	U	N/A	Power	sign	register	(see	Table	54).													
#define	CONFIG		0xE618	//	R/W	16	16	U	0x0010	ADE7978	configuration	register	(see	Table	55).													
																												
#define	MMODE		  0xE700	//	R/W	8	8	U	0x1C	Measurement	mode	register	(see	Table	56).													
#define	ACCMODE		0xE701	//	R/W	8	8	U	0x80	Accumulation	mode	register	(see	Table	57).													
#define	LCYCMODE	0xE702	//	R/W	8	8	U	0x78	Line	accumulation	mode	behavior	(see	Table														
#define	PEAKCYC		0xE703	//	R/W	8	8	U	0x00	Peak	detection	half	line	cycles.														
#define	SAGCYC		0xE704	//	R/W	8	8	U	0x00	Sag	detection	half	line	cycles.														
#define	CFCYC		  0xE705	//	R/W	8	8	U	0x01	Number	of	CF	pulses	between	two													
#define	HSDC_CFG	0xE706	//	R/W	8	8	U	0x00	HSDC	configuration	register	(see	Table	60).														
#define	Version		0xE707	//	R	8	8	U	Version	of	die.																	
#define	CONFIG3		0xE708	//	R/W	8	8	U	0x0F	ADE7933/ADE7932	or	ADE7923	configuration	register	(see													
#define	ATEMPOS		0xE709	//	R	8	8	S	N/A	Phase	A	ADE7933/ADE7932	temperature	sensor	offset													
#define	BTEMPOS		0xE70A	//	R	8	8	S	N/A	Phase	B	ADE7933/ADE7932	temperature	sensor	offset													
#define	CTEMPOS		0xE70B	//	R	8	8	S	N/A	Phase	C	ADE7933/ADE7932	temperature	sensor	offset													
#define	NTEMPOS		0xE70C	//	R	8	8	S	N/A	Neutral	line	ADE7923	or	ADE7933/ADE7932	temperature													
																																																							
#define	LAST_RWDATA8	0xE7FD	//	R	8	8	U	N/A	Contains	the	data	from	the	last																									
																												
#define	APF		    0xE902	//	R	16	16	U	N/A	Phase	A	power	factor.															
#define	BPF		    0xE903	//	R	16	16	U	N/A	Phase	B	power	factor.															
#define	CPF		    0xE904	//	R	16	16	U	N/A	Phase	C	power	factor.															
#define	APERIOD		0xE905	//	R	16	16	U	N/A	Line	period	on	Phase	A	voltage.													
#define	BPERIOD		0xE906	//	R	16	16	U	N/A	Line	period	on	Phase	B	voltage.													
#define	CPERIOD		0xE907	//	R	16	16	U	N/A	Line	period	on	Phase	C	voltage.													
#define	APNOLOAD	0xE908	//	R/W	16	16	U	0x0000	No	load	threshold	in	the	total/fundamental														
#define	VARNOLOAD	0xE909	//	R/W	16	16	U	0x0000	No	load	threshold	in	the	total/fundamental														
#define	VANOLOAD	0xE90A	//	R/W	16	16	U	0x0000	No	load	threshold	in	the	apparent														
																												
#define	LAST_ADD	0xE9FE	//	R	16	16	U	N/A	Contains	the	address	of	the	register														
#define	LAST_RWDATA16	0xE9FF	//	R	16	16	U	N/A	Contains	the	data	from	the	last														
#define	CONFIG2		0xEA00	//	R/W	8	8	U	0x00	Configuration	register	(see	Table	62).														
#define	LAST_OP		0xEA01	//	R	8	8	U	N/A	Indicates	the	type	(read	or	write)													
#define	WTHR		  0xEA02	//	R/W	8	8	U	0x03	Threshold	used	in	phase	total/fundamental	active													
#define	VARTHR		0xEA03	//	R/W	8	8	U	0x03	Threshold	used	in	phase	total/fundamental	reactive													
#define	VATHR		  0xEA04	//	R/W	8	8	U	0x03	Threshold	used	in	phase	apparent	energy													
																																							
																												
