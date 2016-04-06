/*
 * usart.c
 */
#include "usart.h"
#include "mytasks.h"
#define serPUT_STRING_CHAR_DELAY                ( 5 / portTICK_RATE_MS )

void Usart1Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef  USART_ClockInitStructure;
	//enable bus clocks
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	//Set USART1 Tx (PA.09) as AF push-pull
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//Set USART1 Rx (PA.10) as input floating
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	USART_ClockStructInit(&USART_ClockInitStructure);
	USART_ClockInit(USART1, &USART_ClockInitStructure);

	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	//Write USART1 parameters
	USART_Init(USART1, &USART_InitStructure);
	//Enable USART1
	USART_Cmd(USART1, ENABLE);
	USART_DMACmd( USART1, ( USART_DMAReq_Tx | USART_DMAReq_Rx ), ENABLE );

	//configure NVIC
	NVIC_InitTypeDef NVIC_InitStructure;
	//select NVIC channel to configure
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	//set priority to lowest
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	//set subpriority to lowest
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	//enable IRQ channel
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//update NVIC registers
	NVIC_Init(&NVIC_InitStructure);
	//disable Transmit Data Register empty interrupt
	USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
	//enable Receive Data register not empty interrupt
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}
uint32_t Usart1PutChar(char ch)
{
  if( xQueueSend( TxQueue, &ch, 10 ) == pdPASS )
    {
      USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
      return pdTRUE;
    }else{
     return pdFAIL;
    }
}
void  USART1PutString( const char * const pcString, unsigned long ulStringLength)
{

unsigned long ul;
        for( ul = 0; ul < ulStringLength; ul++ )

                {
                        if( xQueueSend( TxQueue, &( pcString[ ul ] ), serPUT_STRING_CHAR_DELAY ) != pdPASS )
                        {
                                /* Cannot fit any more in the queue.  Try turning the Tx on to
                                clear some space. */
                                USART_ITConfig( USART1, USART_IT_TXE, ENABLE );
                                vTaskDelay( serPUT_STRING_CHAR_DELAY );

                                /* Go back and try again. */
                                continue;
                        }
                }

        USART_ITConfig( USART1, USART_IT_TXE, ENABLE );
}



uint32_t Usart1GetChar(char *ch){
  if(xQueueReceive( RxQueue, ch, 0 ) == pdPASS)
    {
      return pdTRUE;
    }
  return pdFALSE;
}
