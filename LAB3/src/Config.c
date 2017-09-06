
#ifndef __CONFIG_C
#define __CONFIG_C

#include "config.h"
#include "opora.h"
					   
//--- Clock configuration ---
void ClkConfig()
{
#ifdef REVISION_2
	RST_CLK->HS_CONTROL=0x00000001;					//HSE - On; Oscillator mode
	while((RST_CLK->CLOCK_STATUS&0x04)!=0x04);		//Wait until HSE not ready
	RST_CLK->CPU_CLOCK=0x00000002;					//CPU_C1 = HSE = 8 MHz

	RST_CLK->PLL_CONTROL=(11<<8)|(1<<2);			//PLL CPU On, PLL_MULL = 11;
	while((RST_CLK->CLOCK_STATUS&0x02)!=0x02);		//wait until PLL CPU not ready
	RST_CLK->PER_CLOCK|=0x08;						//EEPROM_CTRL Clock enable
	EEPROM->CMD=3<<3;								//Delay = 3
	RST_CLK->PER_CLOCK&=(~0x08);					//EEPROM_CTRL Clock disable
		 
	RST_CLK->CPU_CLOCK=0x00000106;					//CPU Clock = 12*8MHz = 96 MHz
#else
	RST_CLK->HS_CONTROL=0x00000003;					//HSE - On; Gen mode On
	while((RST_CLK->CLOCK_STATUS&0x04)!=0x04);		//Wait until HSE not ready
	RST_CLK->CPU_CLOCK=0x00000003;					//CPU clock = 12.5 MHz

	RST_CLK->PLL_CONTROL=(7<<8)|(1<<2);				//PLL CPU On;
	while((RST_CLK->CLOCK_STATUS&0x02)!=0x02);		//wait until PLL CPU not ready
	RST_CLK->PER_CLOCK|=0x08;						//EEPROM_CTRL Clock enable
	EEPROM->CMD=4<<3;								//Delay = 4
	RST_CLK->PER_CLOCK&=(~0x08);					//EEPROM_CTRL Clock disable	 
	RST_CLK->CPU_CLOCK=0x00000107;					//CPU Clock = 8*12.5MHz = 100 MHz
#endif	//REVISION_2

	RST_CLK->PER_CLOCK|=(1<<24)|(1<<23)|(1<<6); 	//clock of PORTD, PORTC, UART1
	RST_CLK->UART_CLOCK = (1<<24)|2;				//enable CLK of UART1, Uart1_Clock = HCLK/4 = 25MHz or 24MHz
}

//--- Ports configuration ---
void PortConfig()
{
	//PORTC_3 - UART1_TXD, PORTC_4 - UART1_RXD, PORTC_8 - External Interrupt 3
	PORTC->FUNC=0x00010140;
	PORTC->ANALOG=0x0118;	//PORTC_3, PORTC_4, PORTC_8 - Digital
	PORTC->PWR=0x000303C0;
	PORTC->PULL=0x00000100;	//подтяжка к GND PORTC_8

	//PORTD_7 - PORTD_14 - Leds
	PORTD->FUNC = 0;
	PORTD->ANALOG=0x7F80;
	PORTD->RXTX=0;
	PORTD->OE|=0x7F80;
	PORTD->PWR|=0x3FFFC000;
}
 
void UART1Config()
{
#ifdef REVISION_2
	UART1->IBRD = 0x000D;	// speed of UART1 = 115200 bit/s
	UART1->FBRD = 0x0001;	// speed of UART1 = 115200 bit/s
#else
	UART1->IBRD = 0x000D;	// speed of UART1 = 115200 bit/s
	UART1->FBRD = 0x0024;	// speed of UART1 = 115200 bit/s
#endif	//REVISION_2
	UART1->LCR_H = 0x0060;	// 8-bits word, FIFO disable, parity disable, 1 stop bit
	UART1->CR = 0x0301;		// UART1, Tx, Rx enable

	UART1->IMSC = 0x0020;	// Tx interrupt enable

	UART1->DR=0x01;
}

#endif	//__CONFIG_C
