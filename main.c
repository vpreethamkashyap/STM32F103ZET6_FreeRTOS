//STM32F103ZET6 FreeRTOS Test
#include "stm32f10x.h"
//#include "stm32f10x_it.h"
#include "mytasks.h"


//task priorities
#define mainLED_TASK_PRIORITY			( tskIDLE_PRIORITY )
#define mainButton_TASK_PRIORITY                   ( tskIDLE_PRIORITY )
#define mainButtonLEDs_TASK_PRIORITY                   ( tskIDLE_PRIORITY + 1 )
#define mainLCD_TASK_PRIORITY                   ( tskIDLE_PRIORITY )
#define mainUSART_TASK_PRIORITY                   ( tskIDLE_PRIORITY )

#define mainLCD_TASK_STACK_SIZE configMINIMAL_STACK_SIZE+50
#define mainUSART_TASK_STACK_SIZE configMINIMAL_STACK_SIZE+50
int main(void)
{
  //init hardware
  LEDsInit();
  ButtonsInit();
  LCD_Init();
  Usart1Init();
  xTaskCreate( vLEDFlashTask, ( signed char * ) "LED", configMINIMAL_STACK_SIZE, NULL, mainLED_TASK_PRIORITY, NULL );
  xTaskCreate( vButtonCheckTask, ( signed char * ) "Button", configMINIMAL_STACK_SIZE, NULL, mainButton_TASK_PRIORITY, NULL );
  xTaskCreate( vButtonLEDsTask, ( signed char * ) "ButtonLED", configMINIMAL_STACK_SIZE, NULL, mainButtonLEDs_TASK_PRIORITY, NULL );
  xTaskCreate( vLCDTask, ( signed char * ) "LCD", mainLCD_TASK_STACK_SIZE, NULL, mainLCD_TASK_PRIORITY, NULL );
  xTaskCreate( vUSARTTask, ( signed char * ) "USART", mainUSART_TASK_STACK_SIZE, NULL, mainUSART_TASK_PRIORITY, NULL );
  //start scheduler
  vTaskStartScheduler();
  //you should never get here
  while(1)
	{ }
}
void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed portCHAR *pcTaskName )
{
  //indicate stack overflow
  LEDOn(1);
  LEDOn(2);
  LEDOn(3);
  LEDOn(4);
  LEDOn(5);
  for( ;; );
}
