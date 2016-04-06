/*
 * mytasks.h
 */

#ifndef MYTASKS_H_
#define MYTASKS_H_
#include "STM32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"
#include "leds.h"
#include "buttons.h"
#include "lcd.h"
#include "usart.h"
#include "main.h"
#define DEBOUNCECOUNTS 10
extern xQueueHandle RxQueue, TxQueue;
void vLEDFlashTask( void *pvParameters );
void vButtonCheckTask( void *pvParameters );
void vButtonLEDsTask( void *pvParameters );
void vLCDTask( void *pvParameters );
void vUSARTTask( void *pvParameters );
#endif /* MYTASKS_H_ */
