#include "1986be91t1.h"
#include "MDR32F9Qx_it.h"

void RSTconf(void)
{
	RST_CLK -> PER_CLOCK =0xFFFFFFFF;
	RST_CLK -> TIM_CLOCK |=(1<<24)|(1<<25);
	RST_CLK -> UART_CLOCK |= (1<<24|(1<<0)); 
}
void PORTconf(void)
{
	PORTA->OE |=(1<<7);
	PORTD->OE |=(1<<10)|(1<<11)|(1<<12)|(1<<13)|(1<<14);
	PORTA->ANALOG	|=(1<<6)|(1<<7);
	PORTD->ANALOG	|=(1<<10)|(1<11)|(1<<12)|(1<<13)|(1<<14);
	PORTA->FUNC	|=(3<<6*2)|(3<<7*2);
	PORTD->FUNC	|=(1<<10*2)|(1<<11*2)|(1<<12*2)|(1<<13*2)|(1<<14*2);
	PORTA->PWR	|=(3<<6*2)|(3<<7*2);
	PORTD->PWR	|=(3<<10*2)|(3<<11*2)|(3<<12*2)|(3<<13*2)|(3<<14*2);
}
void TIMconf(void)
{
	TIMER2->PSG	=30;
	TIMER1->ARR	=65535;
	TIMER2->ARR	=65535;
//	TIMER2->CNTRL |=(2<<8); // CNT==ARR tim2
	TIMER1->CCR2	=30000;
	TIMER1->CCR3	=30000;
	TIMER1->CCR4	=30000;
	TIMER1->CH2_CNTRL	|=(6<<9);
	TIMER1->CH3_CNTRL	|=(6<<9);
	TIMER1->CH4_CNTRL	|=(6<<9);
	TIMER1->CH2_CNTRL1	|=(1<<0)|(2<<2)|(1<<8)|(1<<10)|(1<<12);
	TIMER1->CH3_CNTRL1	|=(1<<0)|(2<<2)|(1<<8)|(1<<10)|(1<<12);
	TIMER1->CH4_CNTRL1	|=(1<<0)|(2<<2)|(1<<8)|(1<<10)|(1<<12);
	TIMER2->IE	|=(1<<1); //IE
}
void UARTconf(void)	
{
	UART1->IBRD	=0x002;;
	UART1->FBRD	=0x0B; //115200
	UART1->LCR_H	|=(3<<5)|(1<<4);//8N-1
	UART1->CR	|=(1<<9)|(1<<0);
	UART1->IMSC	|=(1<<4);
}

int main(void)
{
	RSTconf();
	PORTconf();
	TIMconf();
	UARTconf();
	NVIC_EnableIRQ (Timer2_IRQn);
	NVIC_EnableIRQ (UART1_IRQn);
	TIMER1->CNTRL |=(1<<0);
	TIMER2->CNTRL |=(1<<0);
	while(1)
	{
	}
}
	
	
	