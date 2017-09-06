
#include "opora.h"
#include "config.h"

uint8_t String[]="1";
uint32_t interrupt_flag=0, cnt=0;

int main()
{
	ClkConfig();
	PortConfig();
	UART1Config();
	SYS->ICPR=0x80000000;
	NVIC_EnableIRQ(EXT_INT4_IRQn);
	while(1)
	{
		if(interrupt_flag==1) PORTD->SETTX=1<<7;
		else PORTD->CLRTX=1<<7; 
	}
}

void EXT_INT4_Handler()
{
	PORTD->SETTX=1<<9;
	interrupt_flag=1;
	NVIC_EnableIRQ(UART1_IRQn);
	PORTD->CLRTX=1<<9;
}

void UART1_Handler()
{
	PORTD->SETTX=1<<8;
	UART1->DR=String[cnt++];
	if(String[cnt]==0)
	{
		cnt=0;
		interrupt_flag=0;
		NVIC_DisableIRQ(UART1_IRQn);
	}
	PORTD->CLRTX=1<<8;
}
