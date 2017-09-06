#include "1986be91t1.h"



void RSTconf(void)
{
	RST_CLK -> PER_CLOCK =0xFFFFFFFF;
	RST_CLK -> TIM_CLOCK |=(1<<24)|(1<<25);
//RST_CLK -> CPU_CLOCK |=(3<<8);
	
}
void PORTconf(void)
{
	PORTD -> OE |= ((1<<10)|(1<<11)|(1<<12)|(1<<13)|(1<<14));
	PORTD -> ANALOG|=  ((1<<10)|(1<<11)|(1<<12)|(1<<13)|(1<<14));
	PORTD -> PWR |=  ((3<<(10*2))|(3<<(11*2))|(3<<(12*2))|(3<<(13*2))|(3<<(14*2)));
	PORTD->FUNC|= ((1<<(10*2))|(2<<(11*2))|(1<<(12*2))|(2<<(13*2))|(1<<(14*2)));
	
}
void TIMconf(void)
{
	TIMER1->PSG = 121;
	TIMER2->PSG = 121;
	TIMER1->ARR = 65535;
	TIMER2->ARR = 65535;
	TIMER1->CCR2 =10000;
	TIMER1->CCR3 =35000;
	TIMER1->CCR4 =50000;
	TIMER2->CCR2 =50000;
	TIMER2->CCR3 =35000;
	TIMER2->CCR4 =10000;
	TIMER1->CH3_CNTRL |=(6<<9);
	TIMER1->CH3_CNTRL1 |=((1<<0)|(2<<2)|(1<<8)|(2<<10));
	TIMER1->CH2_CNTRL |=(6<<9);
	TIMER1->CH2_CNTRL1 |=((1<<0)|(2<<2)|(1<<8)|(2<<10));
	TIMER1->CH4_CNTRL |=(6<<9);
	TIMER1->CH4_CNTRL1 |=((1<<0)|(2<<2)|(1<<8)|(2<<10));
	TIMER2->CH3_CNTRL |=(6<<9);
	TIMER2->CH3_CNTRL1 |=((1<<0)|(2<<2)|(1<<8)|(2<<10)|(1<<12));
	TIMER2->CH2_CNTRL |=(6<<9);
	TIMER2->CH2_CNTRL1 |=((1<<0)|(2<<2)|(1<<8)|(2<<10)|(1<<12));
	
}
int main(void)
{
	
 RSTconf ();
	TIMconf();
	PORTconf();
	TIMER1->CNTRL|=(1<<0);
	TIMER2->CNTRL|=(1<<0);
		while(1)
		{
		}
}