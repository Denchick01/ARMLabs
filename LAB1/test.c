#include "test.h"
#include "leds.h"
#include "lcd.h"
#include "text.h"
#include "joystick.h"
#include "menu.h"

void TEST2(void)
{
u32 i,b;
	RST_CLK->PER_CLOCK=0xFFFFFFFF;
				 // TRIM	JTAG  SLRT		LOW
	BKP->REG_0E =  0x2<<8 | 1<<7 | 0x6<<3 | 0x6;
	
//	RST_CLK->CPU_CLOCK = 0x100;
	 

	for (i=0;i<1000000;i++) {};

//	RST_CLK->PLL_CONTROL = 0x8<<8 | 5<<4; // mul = 2
//	RST_CLK->PLL_CONTROL|= 1<<2 | 1; // Pll on
//	while (RST_CLK->CLOCK_STATUS==0) {}; 

//	RST_CLK->CPU_CLOCK   = 1<<8|1<<2;// 0x8<<4;


	RST_CLK->USB_CLOCK   = 1<<8 | 1<<2;
	RST_CLK->CAN_CLOCK   = 0x03 << 24;
	RST_CLK->UART_CLOCK  = 0x03 << 24;
	RST_CLK->SSP_CLOCK   = 0x03 << 24;
	
	PORTD->ANALOG = 0x3<<10;
	PORTD->OE     = 0x3<<10;
	PORTD->RXTX   = 0x3<<10;
	PORTD->PWR    = 0xF<<20;

	for (i=0;i<1000000;i++) {};

	
	BKP->REG_0F |= 1<<4 | 1<<31 | 1<<15;
	BKP->REG_0F &= ~(1<<31);
	BKP->REG_0F |= 1<<4;
	while (BKP->RTC_CS != 0x6) {};
	BKP->REG_0F &= ~(1<<4);

  	i = 0x00000000;
	PORTD->RXTX   = 0x0;
	BKP->REG_0E =  0x2<<8 | 1<<7 | 0x4<<3 | 0x4;
	BKP->REG_0F = i;
	while (1) {};


	b=0;
	while (1) {
//	b++;
	for (i=0;i<750000*(1);i++) {};
//	RST_CLK->PLL_CONTROL = (b&0x0F)<<8 | 5<<4 | 1<<2|1; // mul = 2
	RST_CLK->CPU_CLOCK   = 1<<8 |1<<2;// 0x8<<4;
	for (i=0;i<750000*(16);i++) {};
//	RST_CLK->PLL_CONTROL = (b&0x0F)<<8 | 5<<4 | 1<<2|1; // mul = 2
	RST_CLK->CPU_CLOCK   = 1<<2;//1<<8 |1<<2;// 0x8<<4;
	};


	BKP->REG_0F &= ~(0x3); // LSEON = 0;
	BKP->RTC_CS = 0x7;
	BKP->REG_0F |= 0x80008000;//~(0x01 << 15 | 0x01 << 22);
	BKP->REG_0F &= ~0x80000000;//~(0x01 << 15 | 0x01 << 22);
	BKP->REG_0F |= 0x00000010;//~(0x01 << 15 | 0x01 << 22);
	while (BKP->RTC_CS==0) {}; 

	BKP->REG_0F &= ~0x00000010;//~(0x01 << 15 | 0x01 << 22);

//	BKP->REG_0E &= ~0x0000003F;//~(0x01 << 15 | 0x01 << 22);
//	BKP->REG_0E |= 0x00000024;//~(0x01 << 15 | 0x01 << 22);
	BKP->RTC_PRL = 0xfffff;//~(0x01 << 15 | 0x01 << 22);
	while (BKP->RTC_CS>=1<<6) {};
	BKP->RTC_CS =  0x0000006;//~(0x01 << 15 | 0x01 << 22);
//	BKP->REG_0F = 0x40000000;//~(0x01 << 15 | 0x01 << 22);
//	PORTD->ANALOG = 0xFFFF;
//	PORTD->OE     = 0xff00;
//	PORTD->RXTX   = 0xFF00;
//	PORTD->PWR    = 0xFFFF0000;
	PORTD->ANALOG = 0xFFFF;
	PORTD->OE     = 0xff00;
	PORTD->RXTX   = 0xFF00;
	PORTD->PWR    = 0xFFFF0000;
	for (i=0;i<10000;i++) {};

	while (1) {
	i =  BKP->REG_0F;
//	i &= (~0x00008000);
	i = 0x40408000;
	BKP->REG_0F = i;
//	while (1) {}//~(0x01 << 15 | 0x01 << 22);

	};


}

void TEST(void)
{
u32 i;
//	volatile float i;
//	volatile float y;
	RST_CLK->PER_CLOCK=0xFFFFFFFF;
	BKP->REG_0F &= ~(0x3); // LSEON = 0;
//	PORTE->ANALOG |= (1<<6 | 1<<7);

//	while (1) {};



//	EEPROM->CMD=0;
//	RST_CLK->PER_CLOCK= 1 << 4;//| 0xA<<4;
	RST_CLK->PLL_CONTROL = 0xA<<8 | 5<<4; // mul = 2
	RST_CLK->PLL_CONTROL|= 1<<2 | 1; // Pll on
	RST_CLK->CPU_CLOCK   = 1<<8 |1<<2;// 0x8<<4;


	RST_CLK->USB_CLOCK   = 1<<8 | 1<<2;
	RST_CLK->CAN_CLOCK   = 0x03 << 24;
	RST_CLK->UART_CLOCK  = 0x03 << 24;
	RST_CLK->SSP_CLOCK   = 0x03 << 24;
//	RST_CLK->CPU_CLOCK   = 0x3 << 8;

	while (1){};

	RST_CLK->PER_CLOCK |=1<<27 | 1<<24 ;


	BKP->RTC_CS = 0x7;
	BKP->REG_0F |= 0x80008000;//~(0x01 << 15 | 0x01 << 22);
	BKP->REG_0F &= ~0x80000000;//~(0x01 << 15 | 0x01 << 22);
	BKP->REG_0F |= 0x00000010;//~(0x01 << 15 | 0x01 << 22);
	while (BKP->RTC_CS==0) {}; 
	BKP->REG_0F &= ~0x00000010;//~(0x01 << 15 | 0x01 << 22);

	BKP->REG_0E &= ~0x0000003F;//~(0x01 << 15 | 0x01 << 22);
	BKP->REG_0E |= 0x00000024;//~(0x01 << 15 | 0x01 << 22);
	BKP->RTC_PRL = 0xfffff;//~(0x01 << 15 | 0x01 << 22);
	while (BKP->RTC_CS>=1<<6) {};
	BKP->RTC_CS =  0x0000006;//~(0x01 << 15 | 0x01 << 22);
	BKP->REG_0F = 0x40000000;//~(0x01 << 15 | 0x01 << 22);
	PORTD->ANALOG = 0xFFFF;
	PORTD->OE     = 0xff00;
	PORTD->RXTX   = 0xFF00;
	PORTD->PWR    = 0xFFFF0000;
	for (i=0;i<10000;i++) {};

	while (1) {
	i =  BKP->REG_0F;
	i &= (~0x00F08000);
	i |= 0x40000000;
	while (1) {	BKP->REG_0F = i;}//~(0x01 << 15 | 0x01 << 22);

	};


};

void COMPINIT(void)
{
u32 i;
	u8 str[10];
u8 LEVEL;
u16 DACLEVEL;
FONT *OldFont = CurrentFont;
CurrentMethod = MET_FIX;
LCD_CLS();													    

PORTE->ANALOG = 0xFFFF;
COMP->CFG = 0;

  PORTE->ANALOG &= ~(1<<8 | 1<<9); 	//IN3 COMP & DAC1_OUT
  PORTE->ANALOG &= ~(1<<2 | 1<<3); 	//IN1 COMP IN2
  PORTE->ANALOG &= ~(1<<4 | 1<<5); 	//REF+ REF-




  PORTB->ANALOG = 1<<8;
  PORTB->PWR    = 0x2<<16;
//  PORTB->FUNC   = 0x2<<16; // Comp_Out

  PORTB->OE    = 0x1<<8;



  COMP->CFG = 1 | 1<<1 | 1<<2 | 1<<3 | 0<<8 | 0x2<<9 ;
  while ((COMP->CFG & 1<<12)!=1<<12) {}; // wait ready
  DAC->CFG 	= 0x3<<2;

    WAIT_UNTIL_KEY_RELEASED(SEL);
    DisplayMenuTitle("COMPARATOR");
	CurrentMethod = MET_FIX;
    while ( !KEY_PRESSED(SEL))
    {
	   if (KEY_PRESSED(RIGHT)) LEVEL++ ;
	   else if (KEY_PRESSED(LEFT)) LEVEL--;
	   WAIT_UNTIL_KEY_RELEASED(RIGHT);		 
	   WAIT_UNTIL_KEY_RELEASED(LEFT);

	   if (KEY_PRESSED(UP)) DACLEVEL++ ;
	   else if (KEY_PRESSED(DOWN)) DACLEVEL--;

	   DAC->DAC1_DATA = DACLEVEL & 0xFFF;  // Set DAC
	   COMP->CFG = (COMP->CFG & ~(0xf<<4)) | ((LEVEL & 0xf)<<4); // Set level voltage

		LCD_PUTSL(6,24,"DAC = ",6);
		int2string((DACLEVEL &0xFFF),str);
		LCD_PUTSL(6+6*6,24,str+6,4);

		LCD_PUTSL(6,32,"CVR = ",6);
		int2string((LEVEL &0xF),str);
		LCD_PUTSL(6+6*6,32,str+8,2);

		if (COMP->RESULT & 0x1 == 0x1)
		{
		LCD_PUTSL(6,48,"CVR more then DAC",17);
		LCD_PUTSL(6,56,"RESULT = 1",10);
		PORTB->RXTX   |= (0x1<<8);

		}

		else
		{
		LCD_PUTSL(6,48,"DAC more then CVR",17);
		LCD_PUTSL(6,56,"RESULT = 0",10);
		PORTB->RXTX   &= ~(0x1<<8);
		}
     
    };
    CurrentFont = OldFont;
    DisplayMenu();

};

void PADINIT(void)
{
u32 i;
u8 str[10];


u8 AN; //0
u8 TX; //1
u8 OE; //2
u8 PWR; //3
u8 PU; //4
u8 PD; //5
u8 GF; //6
u8 PR; //7
u8 SHM; //8
u8 var;
u8 RX;

FONT *OldFont = CurrentFont;
CurrentMethod = MET_FIX;
LCD_CLS();													    
var =0;


    WAIT_UNTIL_KEY_RELEASED(SEL);
    DisplayMenuTitle("TEST PAD F[7]");
	CurrentMethod = MET_FIX;
    while ( !KEY_PRESSED(SEL))
    {

	   if (KEY_PRESSED(RIGHT) & var<8) var++;
	   if (KEY_PRESSED(LEFT) & var>0)  var--;
	   WAIT_UNTIL_KEY_RELEASED(RIGHT);
	   WAIT_UNTIL_KEY_RELEASED(LEFT);
	   if (var==0)
	   {
	   LCD_PUTSL(1,56,"SELECT ANALOG",13);
	   if (KEY_PRESSED(UP)) AN++;
	   if (KEY_PRESSED(DOWN))  AN--;
	   WAIT_UNTIL_KEY_RELEASED(UP);
	   WAIT_UNTIL_KEY_RELEASED(DOWN);
	   }
	   if (var==1)
	   {
	   LCD_PUTSL(1,56,"SELECT TX    ",13);
	   if (KEY_PRESSED(UP)) TX++;
	   if (KEY_PRESSED(DOWN))  TX--;
	   WAIT_UNTIL_KEY_RELEASED(UP);
	   WAIT_UNTIL_KEY_RELEASED(DOWN);
	   }
	   if (var==2)
	   {
	   LCD_PUTSL(1,56,"SELECT OE    ",13);
	   if (KEY_PRESSED(UP)) OE++;
	   if (KEY_PRESSED(DOWN))  OE--;
	   WAIT_UNTIL_KEY_RELEASED(UP);
	   WAIT_UNTIL_KEY_RELEASED(DOWN);
	   }
	   if (var==3)
	   {
	   LCD_PUTSL(1,56,"SELECT PWR   ",13);
	   if (KEY_PRESSED(UP)) PWR++;
	   if (KEY_PRESSED(DOWN))  PWR--;
	   WAIT_UNTIL_KEY_RELEASED(UP);
	   WAIT_UNTIL_KEY_RELEASED(DOWN);
	   }
	   if (var==4)
	   {
	   LCD_PUTSL(1,56,"SELECT PULLUP",13);
	   if (KEY_PRESSED(UP)) PU++;
	   if (KEY_PRESSED(DOWN))  PU--;
	   WAIT_UNTIL_KEY_RELEASED(UP);
	   WAIT_UNTIL_KEY_RELEASED(DOWN);
	   }
	   if (var==5)
	   {
	   LCD_PUTSL(1,56,"SELECT PULLDW",13);
	   if (KEY_PRESSED(UP)) PD++;
	   if (KEY_PRESSED(DOWN))  PD--;
	   WAIT_UNTIL_KEY_RELEASED(UP);
	   WAIT_UNTIL_KEY_RELEASED(DOWN);
	   }
	   if (var==6)
	   {
	   LCD_PUTSL(1,56,"SELECT GFEN  ",13);
	   if (KEY_PRESSED(UP)) GF++;
	   if (KEY_PRESSED(DOWN))  GF--;
	   WAIT_UNTIL_KEY_RELEASED(UP);
	   WAIT_UNTIL_KEY_RELEASED(DOWN);
	   }
	   if (var==7)
	   {
	   LCD_PUTSL(1,56,"SELECT DR    ",13);
	   if (KEY_PRESSED(UP)) PR++;
	   if (KEY_PRESSED(DOWN))  PR--;
	   WAIT_UNTIL_KEY_RELEASED(UP);
	   WAIT_UNTIL_KEY_RELEASED(DOWN);
	   }

	   if (var==8)
	   {
	   LCD_PUTSL(1,56,"SELECT SHM   ",13);
	   if (KEY_PRESSED(UP)) SHM++;
	   if (KEY_PRESSED(DOWN))  SHM--;
	   WAIT_UNTIL_KEY_RELEASED(UP);
	   WAIT_UNTIL_KEY_RELEASED(DOWN);
	   }
	RX = (PORTF->RXTX & (1<<7))>>7;
	PORTF->ANALOG = (PORTF->ANALOG & ~(1<<7)) | ((AN&0x1)<<7);
	PORTF->RXTX   = (PORTF->RXTX   & ~(1<<7)) | ((TX&0x1)<<7);
	PORTF->OE 	  = (PORTF->OE     & ~(1<<7)) | ((OE&0x1)<<7);
	PORTF->PWR    = (PORTF->PWR    & ~(0x3<<14)) | ((PWR&0x3)<<14);

	PORTF->PULL   = ((PORTF->PULL   & ~(1<<7))   | ((PD&0x1)<<7));
	PORTF->PULL   = ((PORTF->PULL  & ~(1<<(7+16)))| ((PU&0x1)<<(7+16)));

	PORTF->PD     = ((PORTF->PD   & ~(1<<7))   | ((PR&0x1)<<7));
	PORTF->PD     =	((PORTF->PD  & ~(1<<(7+16)))| ((SHM&0x1)<<(7+16)));

	PORTF->GFEN	  = (PORTF->GFEN   & ~(1<<7)) | ((GF&0x1)<<7);
				  //12345678901234567890123456789012345678901
	LCD_PUTSL(1,16,"A O T R P P P D S G",19);
	LCD_PUTSL(1,24,"N E X X W U D R H F",19);
	LCD_PUTSL(1,32,"        R P N   M E",19);

	int2string((AN&0x1),str);
	LCD_PUTSL(1+6*0,40,str+9,1);

	int2string((OE&0x1),str);
	LCD_PUTSL(1+6*2,40,str+9,1);

	int2string((TX&0x1),str);
	LCD_PUTSL(1+6*4,40,str+9,1);

	int2string((RX&0x1),str);
	LCD_PUTSL(1+6*6,40,str+9,1);

	int2string((PWR&0x3),str);
	LCD_PUTSL(1+6*8,40,str+9,1);

	int2string((PU&0x1),str);
	LCD_PUTSL(1+6*10,40,str+9,1);

	int2string((PD&0x1),str);
	LCD_PUTSL(1+6*12,40,str+9,1);

	int2string((PR&0x1),str);
	LCD_PUTSL(1+6*14,40,str+9,1);

	int2string((SHM&0x1),str);
	LCD_PUTSL(1+6*16,40,str+9,1);

	int2string((GF&0x1),str);
	LCD_PUTSL(1+6*18,40,str+9,1);

     
    };
    CurrentFont = OldFont;
    DisplayMenu();

};


void ADCTEST(void)
{
u32 i;
u8 str[10];
u8  st[16];
u8 LEVEL;
u32 D[4];
u16 L;
FONT *OldFont = CurrentFont;
CurrentMethod = MET_FIX;
LCD_CLS();	
L=0;												    

PORTD->ANALOG = 0;
PORTD->ANALOG = 0xFFFF;
PORTD->RXTX   = 0xFFFF;
PORTD->OE     = 0xFFFF;
PORTD->PWR    = 0xFFFFFFFF;


ADC->ADC2_CFG = 1 | 1<<1|  1<<3 | 1<<9 |3<<12| 1<<17 |  1<<18;// |1<<11 ;
ADC->ADC2_CHSEL  = 0x8; // 7 & 8 chanel 	 
ADC->ADC1_CFG = 0 | 0<<1|  0<<3 | 0<<9 |3<<12| 1<<17;// |1<<11;
//ADC->ADC1_CHSEL  = 0x1; // 7 & 8 chanel 



    WAIT_UNTIL_KEY_RELEASED(SEL);
    DisplayMenuTitle("ADC CHNL CORREL");
	CurrentMethod = MET_FIX;
				  //012345678901234567891
	LCD_PUTSL(0,16,"CH   0    1    2    3",24);
    while ( !KEY_PRESSED(SEL))
    {

	   if (KEY_PRESSED(UP))    L = L |   0x01;
	   if (KEY_PRESSED(DOWN))  L = L & (~0x01);
	   WAIT_UNTIL_KEY_RELEASED(UP);
	   WAIT_UNTIL_KEY_RELEASED(DOWN);

	   if (KEY_PRESSED(RIGHT))    L = L << 1;
	   if (KEY_PRESSED(LEFT))     L = L >> 1;
	   WAIT_UNTIL_KEY_RELEASED(RIGHT);
	   WAIT_UNTIL_KEY_RELEASED(LEFT);
	   PORTD->RXTX   = L;

		for (i=0;i<4;i++)
		{
			while (ADC->ADC2_STATUS<0x04) {};
			D[i] = ADC->ADC2_RESULT;
		}

		for (i=0;i<4;i++)
		{
		LCD_PUTSL(0,24,"A2:",2);
		int2string((D[i]&0xFFFF),str);
		if ((D[i]>>16)==0)
		LCD_PUTSL(6*3,24,str+6,4);
		if ((D[i]>>16)==1)
		LCD_PUTSL(6*8-2,24,str+6,4);
		if ((D[i]>>16)==2)
		LCD_PUTSL(6*12+2,24,str+6,4);
		if ((D[i]>>16)==3)
		LCD_PUTSL(6*17,24,str+6,4);
		}


	/*	for (i=0;i<4;i++)
		{
		while (ADC->ADC1_STATUS<0x04) {};
		D[i] = ADC->ADC1_RESULT;
		}

		for (i=0;i<4;i++)
		{
		LCD_PUTSL(0,32,"A1:",2);
		int2string((D[i]&0xFFFF),str);
		if ((D[i]>>16)==0)
		LCD_PUTSL(6*3,32,str+6,4);
		if ((D[i]>>16)==1)
		LCD_PUTSL(6*8-2,32,str+6,4);
		if ((D[i]>>16)==2)
		LCD_PUTSL(6*12+2,32,str+6,4);
		if ((D[i]>>16)==3)
		LCD_PUTSL(6*17,32,str+6,4);
		}
	  */
		for (i=0;i<=15;i++)
		if ((L>>i)&0x01==0x01) st[i]=0x31;
		else st[i]=0x30;

					  //012345678901234567890123
		LCD_PUTSL(6,40,"PD:           111111 ",24);
		LCD_PUTSL(6,48,"PD: 0123456789012345 ",24);
		LCD_PUTSL(6+6*4,56,st,16);


    };
    CurrentFont = OldFont;
    DisplayMenu();

};

