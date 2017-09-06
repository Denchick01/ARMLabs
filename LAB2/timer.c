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
#include "timer.h"



/* Сервисные утилиты */


void InitPWM(void) 
{
	u32 D;
	u32 C;
	u8 x;
	u8 LEVEL;
	u8 y;
	u8 str[10];
	u8 b[10];
	u8 i=0;
	u8 err = 0xb7;
	FONT *OldFont = CurrentFont;
	CurrentMethod = MET_FIX;
    LCD_CLS();
	RST_CLK->TIM_CLOCK = 0x03000000;

	PORTD->ANALOG |= 0x1F <<10;
	PORTD->PWR    |= 0x3FF <<20;
	PORTD->FUNC   &= ~(0x3FF<<20);
	PORTD->FUNC   |= 0x15<<20; // Timer 1
	PORTD->FUNC   |= 0x0A<<26; // Timer 2



	TIMER1->ARR = 0x100;
	TIMER1->PSG = 0xffff;
	TIMER1->CNTRL = 0x001;
	if (TIMER1->CCR2 < 0x050)
{
	TIMER1->CCR2 = 0x050;
	TIMER1->CCR3 = 0x050;
	TIMER1->CCR4 = 0x050;
	TIMER1->CCR21 = 0x090;
	TIMER1->CCR31 = 0x090;
	TIMER1->CCR41 = 0x090;
}
else
{
	TIMER1->CCR2 ++;
	TIMER1->CCR3 ++;
	TIMER1->CCR4 ++;
	TIMER1->CCR21 ++;
	TIMER1->CCR31 ++;
	TIMER1->CCR41 ++;
}

	TIMER1->CH2_CNTRL = 0xE00;
	TIMER1->CH2_CNTRL1 = 0x00A;
	TIMER1->CH2_CNTRL2 = 0x004;

	TIMER1->CH3_CNTRL = 0xE00;
	TIMER1->CH3_CNTRL1 = 0x00A;
	TIMER1->CH3_CNTRL2 = 0x004;

	TIMER1->CH4_CNTRL = 0xE00;
	TIMER1->CH4_CNTRL1 = 0x00A;
	TIMER1->CH4_CNTRL2 = 0x004;


	TIMER2->ARR = 0x100;
	TIMER2->PSG = 0x0FFF;
	TIMER2->CNTRL = 0x001;
	TIMER2->CCR2 ++;
	TIMER2->CCR3 ++;
	TIMER2->CCR4 ++;

	TIMER2->CH2_CNTRL = 0xE00;
	TIMER2->CH2_CNTRL1 = 0x00A;

	TIMER2->CH3_CNTRL = 0xE00;
	TIMER2->CH3_CNTRL1 = 0x00A;

	TIMER2->CH4_CNTRL = 0xE00;
	TIMER2->CH4_CNTRL1 = 0x00A;

	RST_CLK->PLL_CONTROL = 1<<8 ;//| 5<<4; // mul = 2
	RST_CLK->PLL_CONTROL|= 1<<2 ;//| 1; // Pll on
	RST_CLK->CPU_CLOCK   = 1<<8 |1<<2;// 0x8<<4;
	EXT_BUS_CNTRL->EXT_BUS_CONTROL |= 0xF<<12; 


    WAIT_UNTIL_KEY_RELEASED(SEL);
    DisplayMenuTitle("Timer PWM");
	CurrentMethod = MET_FIX;
    while ( !KEY_PRESSED(SEL))
    {

	if (KEY_PRESSED(RIGHT)) LEVEL++ ;
	else if (KEY_PRESSED(LEFT)) LEVEL--;
	WAIT_UNTIL_KEY_RELEASED(RIGHT);		 
	WAIT_UNTIL_KEY_RELEASED(LEFT);
	RST_CLK->PLL_CONTROL = RST_CLK->PLL_CONTROL & 0xf0ff | (LEVEL & 0x0f) <<8  ;//| 5<<4; // mul = 2

	LCD_PUTSL(6,24,"CPU_PLL MUL = ",14);
	int2string((LEVEL &0x0F),str);
	LCD_PUTSL(6+6*14,24,str+9,1);

    };
    CurrentFont = OldFont;
    DisplayMenu();
	RST_CLK->CPU_CLOCK   = 0;// 0x8<<4;
	EXT_BUS_CNTRL->EXT_BUS_CONTROL &= ~(0xF<<12); 

}

/*============================================================================================
 * Конец файла leds.c
 *============================================================================================*/
