#include "1986be91t1.h"



void RSTconf(void)
{
	RST_CLK -> PER_CLOCK |=((1<<23)|(1<<24));
}
void PORTconf(void)
{
	PORTD -> OE|= ((1<<10)|(1<<11)|(1<<12)|(1<<13)|(1<<14));
	PORTD -> ANALOG|=  ((1<<10)|(1<<11)|(1<<12)|(1<<13)|(1<<14));
	PORTC -> ANALOG|=  ((1<<14)|(1<<15));
	PORTD -> PWR |=  ((3<<(10*2))|(3<<(11*2))|(3<<(12*2))|(3<<(13*2))|(3<<(14*2)));
	PORTC -> PWR |=  ((3<<(14*2))|(3<<(15*2)));
}

int main(void)
{
	int i = 0;
RSTconf ();
PORTconf();
while(1)
{
		
	if(!((PORTC->RXTX)&(1<<13)))
	{
		if(i<(1<<14))
		{
			i=i<<1;
		}
		else
		{
			i=(1<<10);
		}
	}
	while(!((PORTC -> RXTX)&(1<<13)))
	{
	}
	if(!((PORTC->RXTX)&(1<<14)))
	{
		if(i>(1<<10))
		{
			i=i>>1;
		}
		else
		{
			i=(1<<14);
		}
	}
	while(!((PORTC -> RXTX)&(1<<14)))
	{
	}		
	PORTD -> RXTX = i;
	}
}
