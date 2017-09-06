/*============================================================================================
 *
 *  (C) 2010, Phyton
 *
 *  Демонстрационный проект для 1986BE91 testboard
 *
 *  Данное ПО предоставляется "КАК ЕСТЬ", т.е. исключительно как пример, призванный облегчить
 *  пользователям разработку их приложений для процессоров Milandr 1986BE91T1. Компания Phyton
 *  не несет никакой ответственности за возможные последствия использования данного, или
 *  разработанного пользователем на его основе, ПО.
 *
 *--------------------------------------------------------------------------------------------
 *
 *  Файл leds.c: Работа со светодиодами
 *
 *============================================================================================*/

#include "leds.h"
#include "lcd.h"
#include "text.h"
#include "joystick.h"
#include "menu.h"
#include "analog.h"



/* Сервисные утилиты */

void InitADC(void) {

	u32 D;
	u32 C;
	u8 str[10];
	u8 i;
	u8 err;
	u32 t;
	u8 TRIM;
	FONT *OldFont = CurrentFont;
	CurrentMethod = MET_FIX;
	TRIM=0;
    LCD_CLS();
    PORTD->ANALOG &= (0x03<<7); 
    PORTD->ANALOG &= (0x03<<0); 
	PORTD->PULL   = (0xFFFF & ~(0x3<<7)) & 0x0ffff;

	                    /* Analog  7 and 8 chanel*/ 
	ADC->ADC2_CFG = 1 | 1<<1|  1<<3 | 1<<9 |/*1<<11|*/ 1<<17 |  1<<18 ;//| 0x7<<25;
	ADC->ADC2_CHSEL  = 1<<7 | 1<<8 ; // 7 & 8 chanel 	 

	ADC->ADC1_CFG = 1 | /*1<<11|*/ 1 <<17 ;//| ;//|1<<11;

    WAIT_UNTIL_KEY_RELEASED(SEL);
    DisplayMenuTitle("ADC");
	CurrentMethod = MET_FIX;
    while ( !KEY_PRESSED(SEL))
    {


		if	(KEY_PRESSED(UP)) TRIM++;
		WAIT_UNTIL_KEY_RELEASED(UP);
		if	(KEY_PRESSED(DOWN)) TRIM--;
		WAIT_UNTIL_KEY_RELEASED(DOWN);


		ADC->ADC1_CFG = ADC->ADC1_CFG & ~(0x07<<21) | (TRIM & 0x07)<<21;

		LCD_PUTSL(6,8,"TRIM=",5);
			int2string((TRIM&0x07),str);
			LCD_PUTSL(6+6*5,8,str+9,1);




		while (ADC->ADC2_STATUS<0x04) {};
		D = ADC->ADC2_RESULT;
		if ((D>>16)==7)
		{
			LCD_PUTSL(6,16,"ADC2: CHNL[",11);
			int2string((D>>16),str);
			LCD_PUTSL(6+6*11,16,str+8,2);
			LCD_PUTSL(6+6*13,16,"]=",2);
			int2string((D&0xFFFF),str);
			LCD_PUTSL(6+6*15,16,str+6,4);
		}
		else
		{
			LCD_PUTSL(6,24,"ADC2: CHNL[",11);
			int2string((D>>16),str);
			LCD_PUTSL(6+6*11,24,str+8,2);
			LCD_PUTSL(6+6*13,24,"]=",2);
			int2string((D&0xFFFF),str);
			LCD_PUTSL(6+6*15,24,str+6,4);
		}
	  
	// 7 канал 
	
	t  = ADC->ADC1_CFG & ~0x000001F0 ;
	t |= 7<<4;
	t |= 1<<1;
	ADC->ADC1_CFG = t; 
	while (ADC->ADC1_STATUS<0x04) {};
	D = ADC->ADC1_RESULT;
			LCD_PUTSL(6,32,"ADC1: CHNL[",11);
			int2string((D>>16),str);
			LCD_PUTSL(6+6*11,32,str+8,2);
			LCD_PUTSL(6+6*13,32,"]=",2);
			int2string((D&0xFFFF),str);
			LCD_PUTSL(6+6*15,32,str+6,4);
	// 8 канал 
	t = ADC->ADC1_CFG & ~0x000001F0 ;
	t |= 8<<4;
	t |= 1<<1;
	ADC->ADC1_CFG = t; 
	while (ADC->ADC1_STATUS<0x04) {};
	D = ADC->ADC1_RESULT;
			LCD_PUTSL(6,40,"ADC1: CHNL[",11);
			int2string((D>>16),str);
			LCD_PUTSL(6+6*11,40,str+8,2);
			LCD_PUTSL(6+6*13,40,"]=",2);
			int2string((D&0xFFFF),str);
			LCD_PUTSL(6+6*15,40,str+6,4);
	
	 
	// 30 канал Vref 
	ADC->ADC1_CFG &= ~0x001C01F0;
	ADC->ADC1_CFG |= 30<<4 | 1<<18 | 1<<20;
  //  SysTickDelay(1);
	ADC->ADC1_CFG |= 1<<1;
	while (ADC->ADC1_STATUS<0x04) {};
	D = ADC->ADC1_RESULT;
			LCD_PUTSL(6,48,"ADC1: CHNL[",11);
			int2string((D>>16),str);
			LCD_PUTSL(6+6*11,48,str+8,2);
			LCD_PUTSL(6+6*13,48,"]=",2);
			int2string((D&0xFFFF),str);
			LCD_PUTSL(6+6*15,48,str+6,4);
 	// 31 канал TEMP 
	ADC->ADC1_CFG &= ~0x001C01F0;
	ADC->ADC1_CFG |= 31<<4 | 1<<18 | 1<<19;
  //  SysTickDelay(1);
	ADC->ADC1_CFG |= 1<<1;
	while (ADC->ADC1_STATUS<0x04) {};
	D = ADC->ADC1_RESULT;
			LCD_PUTSL(6,56,"ADC1: CHNL[",11);
			int2string((D>>16),str);
			LCD_PUTSL(6+6*11,56,str+8,2);
			LCD_PUTSL(6+6*13,56,"]=",2);
			int2string((D&0xFFFF),str);
			LCD_PUTSL(6+6*15,56,str+6,4);
			
	ADC->ADC1_CFG &= ~0x001C01F0;
	
    };
    CurrentFont = OldFont;
    DisplayMenu();
}

void InitDAC(void) 
{
	u32 D;
	u32 C;
	u32 x;
	u8 str[10];
	u8 i;
	u8 err = 0xb7;
	FONT *OldFont = CurrentFont;
	CurrentMethod = MET_FIX;
    LCD_CLS();													    
	PORTE->ANALOG &= ~(0x03);// |0x01<<9 ); 
	PORTE->ANALOG |=  (0x03);// |0x01<<9 ); 
	                    /* Dac1 и 2 */
  //  PORTD->ANALOG &= (0x03<<7); 
  //  PORTD->ANALOG &= (0x03<<0); 
//	PORTD->PULL   = 0xFFFF;
 //  DAC->CFG = 0x0E;

    WAIT_UNTIL_KEY_RELEASED(SEL);
    DisplayMenuTitle("DAC");
	CurrentMethod = MET_FIX;
    while ( !KEY_PRESSED(SEL))
    {
//	   DAC->CFG = 0x3<<2;
	   if (KEY_PRESSED(RIGHT)) DAC->DAC2_DATA=DAC->DAC2_DATA+10;
	   else if (KEY_PRESSED(LEFT)) DAC->DAC2_DATA=DAC->DAC2_DATA+100;
   		WAIT_UNTIL_KEY_RELEASED(RIGHT);
		WAIT_UNTIL_KEY_RELEASED(LEFT);


	   if (KEY_PRESSED(UP)) DAC->DAC2_DATA++;
	   else if (KEY_PRESSED(DOWN)) DAC->DAC2_DATA--;
	   		WAIT_UNTIL_KEY_RELEASED(UP);
			WAIT_UNTIL_KEY_RELEASED(DOWN);



		 //   LCD_PUTSL(6,16,"DAC1 = ",7);
		//	int2string((DAC->DAC1_DATA&0xFFFF),str);
		//	LCD_PUTSL(6+6*7,16,str+6,4);

		    LCD_PUTSL(6,24,"DAC2 = ",7);
			int2string((DAC->DAC2_DATA&0xFFFF),str);
			LCD_PUTSL(6+6*7,24,str+6,4);


    };
    CurrentFont = OldFont;
    DisplayMenu();
}

void InitHSILSI(void)
{

	u32 D;
	u32 C;
	u32 x;
	u8 str[10];
	u8 i;
	u8 err = 0xb7;
	u8 HSInLSI;
	u8 HSITRIM = 0;
	u8 LSITRIM = 0;
	FONT *OldFont = CurrentFont;
	HSInLSI=0;
	CurrentMethod = MET_FIX;
    LCD_CLS();													    
	PORTD->ANALOG |= 0x1F <<10;
	PORTD->PWR    |= 0x3FF <<20;
	PORTD->FUNC   &= ~(0x3FF<<20);
	PORTD->FUNC   |= 0x55<<20; // Timer 1


  	RST_CLK->TIM_CLOCK = 0x01000000;
	TIMER1->ARR = 0x10;
	TIMER1->PSG = 0xffff;
	TIMER1->CNTRL = 0x001;
	TIMER1->CCR2 = 0x05;
	TIMER1->CCR3 = 0x05;
	TIMER1->CH2_CNTRL = 0xE00;
	TIMER1->CH2_CNTRL1 = 0x909;
	TIMER1->CH3_CNTRL = 0xE00;
	TIMER1->CH3_CNTRL1 = 0x909;

    WAIT_UNTIL_KEY_RELEASED(SEL);
    DisplayMenuTitle("HSI LSI");
	CurrentMethod = MET_FIX;
    while ( !KEY_PRESSED(SEL))
    {
	   WAIT_UNTIL_ANY_KEY
	   RST_CLK->CPU_CLOCK = (RST_CLK->CPU_CLOCK&~(0x03<<8));

	   if (HSInLSI&0x01)
	   {
	   if (KEY_PRESSED(RIGHT)) LSITRIM++ ;
	   else if (KEY_PRESSED(LEFT)) LSITRIM--;
	   WAIT_UNTIL_KEY_RELEASED(RIGHT);		 
	   WAIT_UNTIL_KEY_RELEASED(LEFT);
	   BKP->REG_0F = (BKP->REG_0F & ~(0x001F<<16)) | (LSITRIM&0x001F)<<16; 
	   }
	   else
	   {
	   if (KEY_PRESSED(RIGHT)) HSITRIM++ ;
	   else if (KEY_PRESSED(LEFT)) HSITRIM--;
	   WAIT_UNTIL_KEY_RELEASED(RIGHT);
	   WAIT_UNTIL_KEY_RELEASED(LEFT);
	   BKP->REG_0F = (BKP->REG_0F & ~(0x003F<<24)) | (HSITRIM&0x003F)<<24; 
	   }


	   if (KEY_PRESSED(UP)) 
	   {
	   		HSInLSI++; 
	   }
	   WAIT_UNTIL_KEY_RELEASED(UP);
	    


		    LCD_PUTSL(6,24,"HSITRIM = ",10);
			int2string((HSITRIM &0x3F),str);
			LCD_PUTSL(6+6*10,24,str+8,2);

		    LCD_PUTSL(6,32,"LSITRIM = ",10);
			int2string((LSITRIM&0x1F),str);
			LCD_PUTSL(6+6*10,32,str+8,2);

	   if (HSInLSI & 0x01)
	   {
	   LCD_PUTSL(6,16,"LSI SELECTED",12);
	   RST_CLK->CPU_CLOCK = (RST_CLK->CPU_CLOCK&~(0x03<<8)) | 0x03<<8;
	   }
	   else
	   {
	   LCD_PUTSL(6,16,"HSI SELECTED",12);
	   RST_CLK->CPU_CLOCK = (RST_CLK->CPU_CLOCK&~(0x03<<8));
	   }

    };

    RST_CLK->CPU_CLOCK = (RST_CLK->CPU_CLOCK&~(0x03<<8));
    CurrentFont = OldFont;
    DisplayMenu();

}


/*============================================================================================
 * Конец файла leds.c
 *============================================================================================*/
