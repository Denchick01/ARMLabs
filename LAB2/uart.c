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
#include "uart.h"



/* Сервисные утилиты */


void InitUART(void) 
{
	u32 D;
	u32 C;
	u8 x;
	u8 y;
	u8 str[10];
	u8 b[10];
	u8 i=0;
	u8 err = 0xb7;
	FONT *OldFont = CurrentFont;
	CurrentMethod = MET_FIX;
    LCD_CLS();
    PORTF->ANALOG |= (0x03);                     /* 0 and 1 chanel*/ 
    PORTF->PWR    |= (0x0F);                     /* 0 and 1 chanel*/ 
	PORTF->FUNC   |= (0x0F); 
	PORTC->FUNC   &= ~(0x00F00000); 

	RST_CLK->HS_CONTROL = 0x01; // Enable HSE
	while (RST_CLK->CLOCK_STATUS &(1<<3)==0) {};
	RST_CLK->CPU_CLOCK = 3 | 1<<8; // Enable HSE/2
		 
	RST_CLK->UART_CLOCK = 0x02000000; // Enable UART 2 UARTCLK = HSE/2 
   	UART2->IBRD  = 0x11;
	UART2->FBRD  = 0x17;
	UART2->LCR_H = 0x3<<5 | 1<<4;
	UART2->IFLS  = 0x00;
	UART2->CR    = 0x00;
	UART2->CR    = 0x06 << 7 | 1;
	x=1;
	y=16;

    WAIT_UNTIL_KEY_RELEASED(SEL);
    DisplayMenuTitle("UART");
	CurrentMethod = MET_FIX;
    while ( !KEY_PRESSED(SEL))
    {


		if ((((UART2->FR)&0x00000010))==0) // буфер не пуст
		{
			b[0] = (u8)(UART2->DR);
			LCD_PUTC(x,y,b[0]);
			if ((((UART2->FR)&0x00000020))==0) // буфер не занят
					UART2->DR =b[0]; 
			if (x<120)x=x+6;
			else 
			{
			 x=1;
			 if (y<56) y=y+8;
			 else y=16;
			}

		 }
		if (i>9) 
		i=0;
		else i++;

    };
    CurrentFont = OldFont;
    DisplayMenu();
}

/*============================================================================================
 * Конец файла leds.c
 *============================================================================================*/
