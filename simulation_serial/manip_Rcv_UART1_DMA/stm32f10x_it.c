// Interupts EXTI Project

/**
  ******************************************************************************
  * @file    EXTI/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15/09/2010
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */



/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include <string.h>

void Delay(vu32 nCount);
uint8_t stringCompare(char str1[],char str2[], uint8_t StrLength);


/** @addtogroup Examples
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
int inc = 0 ; 
// 0,01 * 6000
void parsegps(void);
void SysTick_Handler(void)
{
	inc++;
	if (inc >= 1000 ){
		inc = 0 ; 
		parsegps();
	}
	
}

/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
  * @brief  This function handles External line0 interrupt request.
  * @param  None
  * @retval None
  */

void EXTI15_10_IRQHandler(void)
{
    
	if (EXTI_GetFlagStatus(EXTI_Line13)==RESET )
	{
			
	}

    // Remise à zéro du bit déclenchant l'interruption
  EXTI_ClearITPendingBit(EXTI_Line13);
}
// usart2 tnajem tkoun tikteb wa9it saytou i3awed yinzel 
// m3neha we need to check if the button is pressed and the usart2 is empty to send the ReceivedLine





/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles DMA interrupt requests.
  * @param  None
  * @retval None
  */

 
void DMA1_Channel5_IRQHandler(void)
{
  /* Test on DMAx Channely Transfer Half interrupt */
  if(DMA_GetITStatus(DMA1_IT_TC5)){
	
    DMA_ClearITPendingBit(DMA1_IT_TC5); 
	} 
}


void DMA1_Channel7_IRQHandler(void){
		if(DMA_GetITStatus(DMA1_IT_TC7)){
	
    DMA_ClearITPendingBit(DMA1_IT_TC7); 
	} 

}
/**
  * @brief  This function handles USART1 RX interrupt requests.
  * @param  None
  * @retval None
  */
int i = 0;
int z = 0 ; 
int k = 0;
int j = 0 ; 
char* gprmc[14];
char* gpgga[15];
char* ReceivedLine[8];
extern char Receive_Buffer[];

void parsegps(void){
    char* token = strtok(Receive_Buffer, "$" );
    char* arr[14];

    while (token != NULL) {
        arr[i++] = token;
        token = strtok(NULL, "$");
    }
    for ( ; j < i ; j++){
        
        if (strncmp(arr[j], "GPGGA", 5) == 0){            
            char* token = strtok(arr[j], ",");
            while (token != NULL) {
                gpgga[k++] = token;
                token = strtok(NULL, ",");
            }
        }

        if (strncmp(arr[j], "GPRMC", 5) == 0){           
            char* token = strtok(arr[j], ",");
            while (token != NULL) {
                gprmc[z++] = token;
                token = strtok(NULL, ",");
            }
        }

       
    }
    if (z > 0 && k >0){
        ReceivedLine[0] = gpgga[1];  // heure
        ReceivedLine[1] = gpgga[2];  // date
        ReceivedLine[2] = gpgga[3];  // position valide
        ReceivedLine[3] = gpgga[4];  // position N
        ReceivedLine[4] = gpgga[5];	 // N
        ReceivedLine[5] = gpgga[6];		// 
        ReceivedLine[6] = gpgga[7];
        ReceivedLine[7] = gprmc[1];		// nb de sati
    }
		i = 0 ; k = 0 ; z = 0 ; j = 0 ; 
}
// '\0'
int txcount=0;
extern char Transmit_Buffer[];

void USART2_IRQHandler(void)
{
  /* Test on USART2 TX Interrupt */
  if(USART_GetITStatus(USART2, USART_IT_TXE))
  {
    /* Code a ajouter pour assurer le fonctionnement désiré */
		USART_SendData (USART2, Transmit_Buffer[txcount++]);
   /* Clear USART1 Rx interrupt pending bit */
    USART_ClearITPendingBit(USART1 , USART_IT_RXNE);
	  if (txcount==32){
			txcount=0;
			USART_Cmd(USART2, DISABLE);
		}
	}

}


/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
