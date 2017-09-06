/***********************************************************************/
/*  This file is part of the ARM Toolchain package                     */
/*  Copyright KEIL ELEKTRONIK GmbH 2003 - 2008                         */
/***********************************************************************/
/*                                                                     */
/*  FlashDev.C:  Flash Programming Functions adapted                   */
/*               for Philips LPC2xxx 256kB Flash                       */
/*               using Flash Boot Loader with IAP                      */
/*                                                                     */
/***********************************************************************/

#include "C:\Keil_v5\ARM\Flash\FlashOS.H"        // FlashOS Structures

// Memory Mapping Control
	  
#define FLSH_CMD   (*((volatile unsigned int *) 0x40018000))
#define FLSH_ADR   (*((volatile unsigned int *) 0x40018004))
#define FLSH_DI    (*((volatile unsigned int *) 0x40018008))
#define FLSH_DO    (*((volatile unsigned int *) 0x4001800C))
#define FLSH_KEY    (*((volatile unsigned int *) 0x40018010))

#define PORTA_RXTX 		(*((volatile unsigned int *) 0x400A8000))
#define PORTA_OE	 		(*((volatile unsigned int *) 0x400A8004))
#define PORTA_FUNC	 		(*((volatile unsigned int *) 0x400A8008))
#define PORTA_ANALOG	 	(*((volatile unsigned int *) 0x400A800C))
#define PORTA_PULL	 		(*((volatile unsigned int *) 0x400A8010))
#define PORTA_PD	 		(*((volatile unsigned int *) 0x400A8014))
#define PORTA_PWR	 		(*((volatile unsigned int *) 0x400A8018))

#define PORTB_RXTX 		(*((volatile unsigned int *) 0x400B0000))
#define PORTB_OE	 		(*((volatile unsigned int *) 0x400b0004))
#define PORTB_FUNC	 		(*((volatile unsigned int *) 0x400b0008))
#define PORTB_ANALOG	 	(*((volatile unsigned int *) 0x400b000C))
#define PORTB_PULL	 		(*((volatile unsigned int *) 0x400b0010))
#define PORTB_PD	 		(*((volatile unsigned int *) 0x400b0014))
#define PORTB_PWR	 		(*((volatile unsigned int *) 0x400b0018))

#define PORTC_RXTX 		(*((volatile unsigned int *) 0x400B8000))
#define PORTC_OE	 		(*((volatile unsigned int *) 0x400b8004))
#define PORTC_FUNC	 		(*((volatile unsigned int *) 0x400b8008))
#define PORTC_ANALOG	 	(*((volatile unsigned int *) 0x400b800C))
#define PORTC_PULL	 		(*((volatile unsigned int *) 0x400b8010))
#define PORTC_PD	 		(*((volatile unsigned int *) 0x400b8014))
#define PORTC_PWR	 		(*((volatile unsigned int *) 0x400b8018))

#define PORTE_RXTX 		(*((volatile unsigned int *) 0x400c8000))
#define PORTE_OE	 		(*((volatile unsigned int *) 0x400c8004))
#define PORTE_FUNC	 		(*((volatile unsigned int *) 0x400c8008))
#define PORTE_ANALOG	 	(*((volatile unsigned int *) 0x400c800C))
#define PORTE_PULL	 		(*((volatile unsigned int *) 0x400c8010))
#define PORTE_PD	 		(*((volatile unsigned int *) 0x400c8014))
#define PORTE_PWR	 		(*((volatile unsigned int *) 0x400c8018))

#define PORTF_RXTX 		(*((volatile unsigned int *) 0x400e8000))
#define PORTF_OE	 		(*((volatile unsigned int *) 0x400e8004))
#define PORTF_FUNC	 		(*((volatile unsigned int *) 0x400e8008))
#define PORTF_ANALOG	 	(*((volatile unsigned int *) 0x400e800C))
#define PORTF_PULL	 		(*((volatile unsigned int *) 0x400e8010))
#define PORTF_PD	 		(*((volatile unsigned int *) 0x400e8014))
#define PORTF_PWR	 		(*((volatile unsigned int *) 0x400e8018))

#define EX_BUS_CONTROL		(*((volatile unsigned int *) 0x400F0054))
#define EX_BUS_NAND_CYCLES	(*((volatile unsigned int *) 0x400F0050))



#define PER_CLOCK 	(*((volatile unsigned int *)0x4002001C))


#define STACK_SIZE     128      // Stack Size


/*
 *  Initialize Flash Programming Functions
 *    Parameter:      adr:  Device Base Address
 *                    clk:  Clock Frequency (Hz)
 *                    fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed
 */
 /*
void InitEXTBUS(void)
{
PER_CLOCK = 0xFFFFFFFF;

PORTA_FUNC = 0x55555555;
PORTB_FUNC = 0x55555555;
PORTC_FUNC = 0x00005555;
PORTE_FUNC = 0x55555555;
PORTF_FUNC = 0x55555555;

PORTA_ANALOG = 0xFFFF;
PORTB_ANALOG = 0xFFFF;
PORTC_ANALOG = 0xFFFF;
PORTE_ANALOG = 0xFFFF;
PORTF_ANALOG = 0xFFFF;

PORTA_PULL = 0xFFFF;
PORTB_PULL = 0xFFFF;
PORTC_PULL = 0xFFFF;
PORTE_PULL = 0xFFFF;
PORTF_PULL = 0xFFFF;

PORTA_PD = 0x0000;
PORTB_PD = 0x0000;
PORTC_PD = 0x0000;
PORTE_PD = 0x0000;
PORTF_PD = 0x0000;

PORTA_PWR = 0xFFFFFFFF;
PORTB_PWR = 0xFFFFFFFF;
PORTC_PWR = 0xFFFFFFFF;
PORTE_PWR = 0xFFFFFFFF;
PORTF_PWR = 0xFFFFFFFF;

PORTC_RXTX = 0x00000000;
PORTC_OE = 0x0000FFFF;


EX_BUS_CONTROL = 0xF002;
}

   int ResetFLASH(void)
{
unsigned int i;
*(unsigned int *)((0x10000000)) = 0xF0F0F0F0;
i = (*(unsigned int *)((0x10000000)));
return i;

}

 unsigned int ReadFLASH(unsigned short ADR)
{
return (*(unsigned int *)((0x10000000+ADR)));
}

 unsigned int ReadIDFLASH(unsigned short ADR)
{
*(unsigned int *)
*(unsigned int *)((0x10000000+0x555*4)) = 0x90909090((0x10000000+0x555*4)) = 0xAAAAAAAA;
*(unsigned int *)((0x10000000+0x2AA*4)) = 0x55555555;;
return (*(unsigned int *)((0x10000000+ADR*4)));
}

  void WriteFLASH(unsigned short ADR, int DATA)
{
unsigned int i;
*(unsigned int *)((0x10000000+0x555*4)) = 0xAAAAAAAA;
*(unsigned int *)((0x10000000+0x2AA*4)) = 0x55555555;
*(unsigned int *)((0x10000000+0x555*4)) = 0xA0A0A0A0;
*(unsigned int *)((0x10000000+ADR)) = DATA;
do i = (*(unsigned int *)((0x10000000+ADR)));
while ((i & 0x80808080) == ((~DATA) & 0x80808080));
}


  void  EraseFLASH()
{
unsigned int i;
*(unsigned int *)((0x10000000+0x555*4)) = 0xAAAAAAAA;
*(unsigned int *)((0x10000000+0x2AA*4)) = 0x55555555;
*(unsigned int *)((0x10000000+0x555*4)) = 0x80808080;

*(unsigned int *)((0x10000000+0x555*4)) = 0xAAAAAAAA;
*(unsigned int *)((0x10000000+0x2AA*4)) = 0x55555555;
*(unsigned int *)((0x10000000+0x555*4)) = 0x10101010;

do i = (*(unsigned int *)((0x10000000)));
while ((i & 0x80808080) != 0x80808080);
}
	 */
int Init (unsigned long adr, unsigned long clk, unsigned long fnc) 
{

PER_CLOCK = 0xFFFFFFFF;

PORTA_FUNC = 0x55555555;
PORTB_FUNC = 0x55555555;
PORTC_FUNC = 0x00005555;
PORTE_FUNC = 0x55555555;
PORTF_FUNC = 0x55555555;

PORTA_ANALOG = 0xFFFF;
PORTB_ANALOG = 0xFFFF;
PORTC_ANALOG = 0xFFFF;
PORTE_ANALOG = 0xFFFF;
PORTF_ANALOG = 0xFFFF;

PORTA_PULL = 0xFFFF;
PORTB_PULL = 0xFFFF;
PORTC_PULL = 0xFFFF;
PORTE_PULL = 0xFFFF;
PORTF_PULL = 0xFFFF;

PORTA_PD = 0x0000;
PORTB_PD = 0x0000;
PORTC_PD = 0x0000;
PORTE_PD = 0x0000;
PORTF_PD = 0x0000;

PORTA_PWR = 0xFFFFFFFF;
PORTB_PWR = 0xFFFFFFFF;
PORTC_PWR = 0xFFFFFFFF;
PORTE_PWR = 0xFFFFFFFF;
PORTF_PWR = 0xFFFFFFFF;

PORTC_RXTX = 0x00000000;
PORTC_OE = 0x0000FFFF;


EX_BUS_CONTROL = 0xF002;

  return (0);
}


/*
 *  De-Initialize Flash Programming Functions
 *    Parameter:      fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed
 */

int UnInit (unsigned long fnc) {

   	
  return (0);
}


/*
 *  Erase complete Flash Memory
 *    Return Value:   0 - OK,  1 - Failed
 */

int EraseChip (void) {


unsigned int i;
*(volatile unsigned int *)((0x10000000)) = 0xF0F0F0F0;
i = (*(volatile unsigned int *)((0x10000000)));

*(volatile unsigned int *)((0x10000000+0x555*4)) = 0xAAAAAAAA;
*(volatile unsigned int *)((0x10000000+0x2AA*4)) = 0x55555555;
*(volatile unsigned int *)((0x10000000+0x555*4)) = 0x80808080;

*(volatile unsigned int *)((0x10000000+0x555*4)) = 0xAAAAAAAA;
*(volatile unsigned int *)((0x10000000+0x2AA*4)) = 0x55555555;
*(volatile unsigned int *)((0x10000000+0x555*4)) = 0x10101010;

do i = (*(volatile unsigned int *)((0x10000000)));
while ((i & 0x80808080) != 0x80808080);

  return (0);                                  // Finished without Errors
}


/*
 *  Erase Sector in Flash Memory
 *    Parameter:      adr:  Sector Address
 *    Return Value:   0 - OK,  1 - Failed
 */

int EraseSector (unsigned long adr) {


  return (0);                                  // Finished without Errors
}


/*
 *  Program Page in Flash Memory
 *    Parameter:      adr:  Page Start Address
 *                    sz:   Page Size
 *                    buf:  Page Data
 *    Return Value:   0 - OK,  1 - Failed
 */

int ProgramPage (unsigned long adr, unsigned long sz, unsigned char *buf) {


  int i,y;
  unsigned int DATA;
  unsigned short ADR;


*(volatile unsigned int *)((0x10000000)) = 0xF0F0F0F0;
i = (*(volatile unsigned int *)((0x10000000)));

 // 	DATA  = buf[3]<<24|buf[2]<<16|buf[1]<<8|buf[0];

  	for (i=0;i<sz;i=i+4)
  	{	
	  	ADR = (adr+i) & 0xFFFF;
	  	DATA  = buf[i+3]<<24|buf[i+2]<<16|buf[i+1]<<8|buf[i];

*(volatile unsigned int *)((0x10000000+0x555*4)) = 0xAAAAAAAA;
*(volatile unsigned int *)((0x10000000+0x2AA*4)) = 0x55555555;
*(volatile unsigned int *)((0x10000000+0x555*4)) = 0xA0A0A0A0;
*(volatile unsigned int *)((0x10000000+ADR)) = DATA;
do y = (*(volatile unsigned int *)((0x10000000+ADR)));
while ((y & 0x80808080) == ((~DATA) & 0x80808080));

  	}
  return (0);                                  // Finished without Errors
}

