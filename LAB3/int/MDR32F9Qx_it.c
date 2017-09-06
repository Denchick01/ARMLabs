/**
  ******************************************************************************
  * @file    Examples/MDR32F9Q1_EVAL/POWER/STOP/MDR32F9Qx_it.c
  * @author  Milandr Application Team
  * @version V1.2.0
  * @date    04/07/2011
  * @brief   Main Interrupt Service Routines.
  *
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 Milandr</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "1986BE91T1.h"
#include "MDR32F9Qx_port.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

static volatile unsigned int k=0;
/*******************************************************************************
* Function Name  : NMI_Handler
* Description    : This function handles NMI exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NMI_Handler(void)
{
}
/*******************************************************************************
* Function Name  : HardFault_Handler
* Description    : This function handles Hard Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
/*******************************************************************************
* Function Name  : MemManage_Handler
* Description    : This function handles Memory Manage exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}
/*******************************************************************************
* Function Name  : BusFault_Handler
* Description    : This function handles Bus Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
/*******************************************************************************
* Function Name  : UsageFault_Handler
* Description    : This function handles Usage Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
/*******************************************************************************
* Function Name  : SVC_Handler
* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SVC_Handler(void)
{
}
/*******************************************************************************
* Function Name  : DebugMon_Handler
* Description    : This function handles Debug Monitor exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DebugMon_Handler(void)
{
}
/*******************************************************************************
* Function Name  : PendSV_Handler
* Description    : This function handles Debug PendSV exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PendSV_Handler(void)
{
}
/*******************************************************************************
* Function Name  : SysTick_Handler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTick_Handler(void)
{
}
/*******************************************************************************
* Function Name  : CAN1_IRQHandler
* Description    : This function handles CAN1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN1_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : CAN2_IRQHandler
* Description    : This function handles CAN2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN2_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : USB_IRQHandler
* Description    : This function handles USB global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : DMA_IRQHandler
* Description    : This function handles DMA global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : UART1_IRQHandler
* Description    : This function handles UART1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART1_IRQHandler(void)
{
	static volatile unsigned int n,g,y = 0;
	n = UART1->DR; 
	if ( (n == 45)&&(g<60000)) //brighter 
	{
		g = g+10000;
	TIMER1->CCR2	= g;
	TIMER1->CCR3	= g;
	TIMER1->CCR4	= g;
	}
	else if ( (n == 61)&&(g>0)) //dimmer 
	{
		g = g-10000;
	TIMER1->CCR2	= g;
	TIMER1->CCR3	= g;
	TIMER1->CCR4	= g;
	}
	else if ( (n == 56)&&(y<60000)) //up speed
	{
		y = y+10000;
	TIMER2->ARR	= y;
	}	
	else if ( (n == 50)&&(y>0)) //down speed 
	{
		y = y-10000;
	TIMER2->ARR	= y;
	}
	else if (n == 52) //left 
		k = 1;
	else if (n == 54)  //right  
		k = 0 ;
	
}
/*******************************************************************************
* Function Name  : UART2_IRQHandler
* Description    : This function handles UART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART2_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : SSP1_IRQHandler
* Description    : This function handles SSP1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SSP1_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : I2C_IRQHandler
* Description    : This function handles I2C global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : POWER_IRQHandler
* Description    : This function handles POWER global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void POWER_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : WWDG_IRQHandler
* Description    : This function handles WWDG global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void WWDG_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : Timer1_IRQHandler
* Description    : This function handles Timer1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer1_IRQHandler(void)
{
	
		
}
/*******************************************************************************
* Function Name  : Timer2_IRQHandler
* Description    : This function handles Timer2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer2_IRQHandler(void)
	
{
	 volatile unsigned int i=0;
	static volatile unsigned int p=0;
	TIMER2->STATUS &= ~(1<<1);
	
if ( p > 4 )
 p=0;
if (k == 0)
{	
		if( p == 0 )
		{
			TIMER1->CH2_CNTRL1	|=(2<<2);
			TIMER1->CH2_CNTRL1	&=~(3<<10);
			TIMER1->CH3_CNTRL1	&=~(3<<2);
			//TIMER1->CH2_CNTRL1	&=~(3<<10);
			TIMER1->CH4_CNTRL1	&=~(3<<2);
			//TIMER1->CH2_CNTRL1	&=~((1<<0)|(2<<2)|(0<<8)|(0<<10)|(1<<12));
			//TIMER1->CH3_CNTRL1	&=~((0<<0)|(0<<2)|(0<<8)|(0<<10)|(1<<12));
			//TIMER1->CH4_CNTRL1	&=~((0<<0)|(0<<2)|(0<<8)|(0<<10)|(1<<12));
		}
		else if ( p == 1 )
		{
			TIMER1->CH2_CNTRL1	&=~(3<<2);
			TIMER1->CH2_CNTRL1	|=(2<<10);
			TIMER1->CH3_CNTRL1	&=~(3<<2);
			//TIMER1->CH2_CNTRL1	&=~(3<<10);
			TIMER1->CH4_CNTRL1	&=~(3<<2);
			//TIMER1->CH2_CNTRL1	&=~((1<<0)|(0<<2)|(1<<8)|(2<<10)|(1<<12));
			//TIMER1->CH3_CNTRL1	&=~((1<<0)|(0<<2)|(1<<8)|(0<<10)|(1<<12));
			//TIMER1->CH4_CNTRL1	&=~((1<<0)|(0<<2)|(1<<8)|(0<<10)|(1<<12));
		}
		else if ( p == 2 )
		{
			TIMER1->CH2_CNTRL1	&=~(3<<2);
			TIMER1->CH2_CNTRL1	&=~(3<<10);
			TIMER1->CH3_CNTRL1	|=(2<<2);
			//TIMER1->CH2_CNTRL1	&=~(3<<10);
			TIMER1->CH4_CNTRL1	&=~(3<<2);
		//	TIMER1->CH2_CNTRL1	&=~((1<<0)|(0<<2)|(1<<8)|(0<<10)|(1<<12));
		//	TIMER1->CH3_CNTRL1	&=~((1<<0)|(2<<2)|(1<<8)|(0<<10)|(1<<12));
			//TIMER1->CH4_CNTRL1	&=~((1<<0)|(0<<2)|(1<<8)|(0<<10)|(1<<12));
		}
		else if ( p == 3 )
		{
			TIMER1->CH2_CNTRL1	&=~(3<<2);
			TIMER1->CH2_CNTRL1	&=~(3<<2);
			TIMER1->CH3_CNTRL1	&=~(3<<2);
			//TIMER1->CH3_CNTRL1	|=(2<<10);
			TIMER1->CH4_CNTRL1	&=~(3<<2);
			//TIMER1->CH2_CNTRL1	&=~((1<<0)|(0<<2)|(1<<8)|(0<<10)|(1<<12));
			//TIMER1->CH3_CNTRL1	&=~((1<<0)|(0<<2)|(1<<8)|(2<<10)|(1<<12));
			//TIMER1->CH4_CNTRL1	&=~((1<<0)|(0<<2)|(1<<8)|(0<<10)|(1<<12));
		}
		else if ( p == 4 )
		{
		TIMER1->CH2_CNTRL1		&=~(3<<2);
			TIMER1->CH2_CNTRL1	&=~(3<<10);
			TIMER1->CH2_CNTRL1	&=~(3<<2);
			//TIMER1->CH2_CNTRL1	&=~(3<<10);
			TIMER1->CH4_CNTRL1	|=(2<<2);
			//TIMER1->CH2_CNTRL1	&=~((1<<0)|(0<<2)|(1<<8)|(0<<10)|(1<<12));
			//TIMER1->CH3_CNTRL1	&=~((1<<0)|(0<<2)|(1<<8)|(0<<10)|(1<<12));
			//TIMER1->CH4_CNTRL1	&=~((1<<0)|(2<<2)|(1<<8)|(0<<10)|(1<<12));
		}
		
	}
/*
else if (k == 1)
{	
		if( p == 0 )
		{
			TIMER1->CH2_CNTRL1	|=(1<<0)|(0<<2)|(1<<8)|(0<<10)|(1<<12);
			TIMER1->CH3_CNTRL1	|=(1<<0)|(0<<2)|(1<<8)|(0<<10)|(1<<12);
			TIMER1->CH4_CNTRL1	|=(1<<0)|(2<<2)|(1<<8)|(0<<10)|(1<<12);
		}
		else if ( p == 1 )
		{
			TIMER1->CH2_CNTRL1	|=(1<<0)|(0<<2)|(1<<8)|(0<<10)|(1<<12);
			TIMER1->CH3_CNTRL1	|=(1<<0)|(0<<2)|(1<<8)|(2<<10)|(1<<12);
			TIMER1->CH4_CNTRL1	|=(1<<0)|(0<<2)|(1<<8)|(0<<10)|(1<<12);
		}
		else if ( p == 2 )
		{
			TIMER1->CH2_CNTRL1	|=(1<<0)|(0<<2)|(1<<8)|(0<<10)|(1<<12);
			TIMER1->CH3_CNTRL1	|=(1<<0)|(2<<2)|(1<<8)|(0<<10)|(1<<12);
			TIMER1->CH4_CNTRL1	|=(1<<0)|(0<<2)|(1<<8)|(0<<10)|(1<<12);
		}
		else if ( p == 3 )
		{
			TIMER1->CH2_CNTRL1	|=(1<<0)|(0<<2)|(1<<8)|(2<<10)|(1<<12);
			TIMER1->CH3_CNTRL1	|=(1<<0)|(0<<2)|(1<<8)|(0<<10)|(1<<12);
			TIMER1->CH4_CNTRL1	|=(1<<0)|(0<<2)|(1<<8)|(0<<10)|(1<<12);
		}
		
		else if ( p == 4 )
		{
			TIMER1->CH2_CNTRL1	|=(1<<0)|(2<<2)|(1<<8)|(0<<10)|(1<<12);
			TIMER1->CH3_CNTRL1	|=(1<<0)|(0<<2)|(1<<8)|(0<<10)|(1<<12);
			TIMER1->CH4_CNTRL1	|=(1<<0)|(0<<2)|(1<<8)|(0<<10)|(1<<12);
		}
	}*/
		p++;
}
/*******************************************************************************
* Function Name  : Timer3_IRQHandler
* Description    : This function handles Timer3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer3_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : ADC_IRQHandler
* Description    : This function handles ADC global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : COMPARATOR_IRQHandler
* Description    : This function handles COMPARATOR global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void COMPARATOR_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : SSP2_IRQHandler
* Description    : This function handles SSP2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SSP2_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : BACKUP_IRQHandler
* Description    : This function handles BACKUP global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BACKUP_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : EXT_INT1_IRQHandler
* Description    : This function handles EXT_INT1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXT_INT1_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : EXT_INT2_IRQHandler
* Description    : This function handles EXT_INT2 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXT_INT2_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : EXT_INT3_IRQHandler
* Description    : This function handles EXT_INT3 global interrupt request.
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXT_INT3_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : EXT_INT4_IRQHandler
* Description    : This function handles EXT_INT4 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXT_INT4_IRQHandler(void)
{
}

/******************* (C) COPYRIGHT 2011 Milandr *********/
