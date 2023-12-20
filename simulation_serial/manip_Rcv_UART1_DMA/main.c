//usart_send_polling

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Private typedef -----------------------------------------------------------*/

char Compare_Buffer[20]="ABCDEFGHIJ0123456789";
char Receive_Buffer[20]; 
char Transmit_Buffer[]="PWDISOK";

// Structures
GPIO_InitTypeDef GPIO_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
USART_InitTypeDef USART_InitStructure;
DMA_InitTypeDef DMA_InitStructure;
 
/* Private functions ---------------------------------------------------------*/
void Delay(vu32 nCount);

void Config_USART1_RX_WITH_DMA (void);

int main(void)
{
/* ================  Configure the Periph Clocks ===================== */

  /* Enable GPIOx and AFIO clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);

	
  /* ================  Configure the GPIO ports ===================== */

    /*Configure PA5 as Output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
	 
/*----------------------------------------------------------*/
// Configure USART1 to Receieve and Store Data Using DMA Channel
Config_USART1_RX_WITH_DMA();



 while(1)
 {
	}

}//END MAIN                

  
/******************** Function Name  : Delay**************************/
void Delay(vu32 nCount)
{  for(; nCount != 0; nCount--);}



void Config_USART1_RX_WITH_DMA (void)
{
		/* Enable DMA1 clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	/* Enable USART1 clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	

	
  /* Configure USART1 Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);


/* ====================  USART1 configuration ======================*/
    /*  - BaudRate = 9600 baud - Word Length = 8 Bits- One Stop Bit - No parity
        - Receive enabled   */
	
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx;

  USART_Init(USART1, &USART_InitStructure);
  	
	/*Enable  Rx DMA Request (s) on USART1*/
			USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);

  /* Enable the USART1*/
  USART_Cmd(USART1, ENABLE);
	
/* ====================  DMA configuration ======================*/

		//DMAx channelx (UART1 RX) configuration */
		//DMA_DeInit(DMA1_Channel5);
		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) &USART1->DR;
		DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Receive_Buffer;
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
		DMA_InitStructure.DMA_BufferSize = 20;
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
		DMA_InitStructure.DMA_Priority = DMA_Priority_High;
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	
		
		DMA_Init(DMA1_Channel5, &DMA_InitStructure);

//  /* Enable DMAx Channely Transfer Complete/ Half Transfer interrupts */
		DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);

			/* Enable DMA1 Channelx transfer */
			DMA_Cmd(DMA1_Channel5, ENABLE);

//     /* Enable and set DMAx Channel y Interrupt  */
   NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
}
	