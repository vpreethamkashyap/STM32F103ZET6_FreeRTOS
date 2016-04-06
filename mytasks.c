/*
 * mytasks.c
 */
#include "mytasks.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char * const pcUsartTaskStartMsg = "USART task started.\r\n";
const char * const pcLCDTaskStartMsg = "   LCD task started.";

static xSemaphoreHandle xButtonWakeupSemaphore = NULL;
static xSemaphoreHandle xButtonTamperSemaphore = NULL;
static xSemaphoreHandle xButtonUser1Semaphore = NULL;
static xSemaphoreHandle xButtonUser2Semaphore = NULL;
xQueueHandle RxQueue, TxQueue;
char stringbuffer[39];
void vLEDFlashTask( void *pvParameters )
{
  portTickType xLastWakeTime;
  const portTickType xFrequency = 1000;
  xLastWakeTime=xTaskGetTickCount();
    for( ;; )
    {
	  LEDToggle(5);
	  vTaskDelayUntil(&xLastWakeTime,xFrequency);
    }
}
void vButtonCheckTask( void *pvParameters )
{
  //for debounce
  static uint8_t count;
  portTickType xLastWakeTime;
  const portTickType xFrequency = 20;
  xLastWakeTime=xTaskGetTickCount();
  //create semaphores for each button
  vSemaphoreCreateBinary(xButtonWakeupSemaphore);
  vSemaphoreCreateBinary(xButtonTamperSemaphore);
  vSemaphoreCreateBinary(xButtonUser1Semaphore);
  vSemaphoreCreateBinary(xButtonUser2Semaphore);
//check if semaphores were created successfully
  if((xButtonWakeupSemaphore!=NULL)&&(xButtonTamperSemaphore!=NULL)
   &&(xButtonUser1Semaphore!=NULL)&&(xButtonUser2Semaphore!=NULL))
  {
    //successfully created
    //resets initial semaphores to 0
    xSemaphoreTake(xButtonWakeupSemaphore, (portTickType)0);
    xSemaphoreTake(xButtonTamperSemaphore, (portTickType)0);
    xSemaphoreTake(xButtonUser1Semaphore, (portTickType)0);
    xSemaphoreTake(xButtonUser2Semaphore, (portTickType)0);
  }  else {
	  //send error of failure
  }

  for (;;)
    {
      if (ButtonRead(BWAKEUPPORT, BWAKEUP)==pdTRUE)
        {
          count++;
          if(count==DEBOUNCECOUNTS)
            {
              xSemaphoreGive(xButtonWakeupSemaphore);
              count = 0;
            }
        }
      if (ButtonRead(BTAMPERPORT, BTAMPER)==pdTRUE)
        {
          count++;
          if(count==DEBOUNCECOUNTS)
            {
              xSemaphoreGive(xButtonTamperSemaphore);
              count = 0;
            }
        }
      if (ButtonRead(BUSER1PORT, BUSER1)==pdTRUE)
        {
          count++;
          if(count==DEBOUNCECOUNTS)
            {
              xSemaphoreGive(xButtonUser1Semaphore);
              count = 0;
            }
        }
      if (ButtonRead(BUSER2PORT, BUSER2)==pdTRUE)
        {
          count++;
          if(count==DEBOUNCECOUNTS)
            {
              xSemaphoreGive(xButtonUser2Semaphore);
              count = 0;
            }
        }
      vTaskDelayUntil(&xLastWakeTime,xFrequency);
    }
}
void vButtonLEDsTask( void *pvParameters )
{
  portTickType xLastWakeTime;
  const portTickType xFrequency = 100;
  xLastWakeTime=xTaskGetTickCount();

  for( ;; )
  {
      if((xButtonWakeupSemaphore!=NULL)&&(xButtonTamperSemaphore!=NULL)
       &&(xButtonUser1Semaphore!=NULL)&&(xButtonUser2Semaphore!=NULL))
      {
         if (xSemaphoreTake(xButtonWakeupSemaphore, (portTickType)10)==pdTRUE)
             {
               LEDToggle(1);
               //give semaphore back
               xSemaphoreGive(xButtonWakeupSemaphore);
             }
         if (xSemaphoreTake(xButtonTamperSemaphore, (portTickType)10)==pdTRUE)
             {
               LEDToggle(2);
               xSemaphoreGive(xButtonTamperSemaphore);
             }
         if (xSemaphoreTake(xButtonUser1Semaphore, (portTickType)10)==pdTRUE)
             {
               LEDToggle(3);
               xSemaphoreGive(xButtonUser1Semaphore);
             }
         if (xSemaphoreTake(xButtonUser2Semaphore, (portTickType)10)==pdTRUE)
             {
               LEDToggle(4);
               xSemaphoreGive(xButtonUser2Semaphore);
             }
      }

    vTaskDelayUntil(&xLastWakeTime,xFrequency);
  }
}
void vLCDTask( void *pvParameters )
{
  extern uint8_t Image_Table[];
  portTickType xLastWakeTime;
  const portTickType xFrequency = 100;
  xLastWakeTime=xTaskGetTickCount();
  LCD_SetDisplayWindow(00, 00, 239, 319);
  LCD_Clear(Black);
  LCD_DisplayStringLine(Line4,  (char*)pcLCDTaskStartMsg, White, Black);
  for(;;)
    {
      if((xButtonWakeupSemaphore!=NULL)&&(xButtonTamperSemaphore!=NULL)
       &&(xButtonUser1Semaphore!=NULL)&&(xButtonUser2Semaphore!=NULL))
      {
         if (xSemaphoreTake(xButtonWakeupSemaphore, (portTickType)10)==pdTRUE)
             {
             LCD_Clear(Blue);
             LCD_WriteBMP_Dim(30, 30, 210, 210, Image_Table);
             }
         if (xSemaphoreTake(xButtonTamperSemaphore, (portTickType)10)==pdTRUE)
             {
             unsigned portBASE_TYPE uxTasks;
             uxTasks=uxTaskGetNumberOfTasks();
             sprintf(stringbuffer, "   Tasks: %ld", uxTasks);
             LCD_Clear(Black);
             LCD_DisplayStringLine(Line0, "   Hello   ",White, Black);
             LCD_DisplayStringLine(Line1, "   This is LCD DEMO  ", Black,Blue);
             LCD_DisplayStringLine(Line2, "   Click any button  ", Black,Green);
             LCD_DisplayStringLine(Line6, stringbuffer, Black,White);
             }
         if (xSemaphoreTake(xButtonUser1Semaphore, (portTickType)10)==pdTRUE)
             {
             LCD_Clear(White);
             LCD_SetTextColor(Black);
             LCD_DrawCircle(60, 60, 50);
             LCD_SetTextColor(Green);
             LCD_DrawCircle(100, 160, 53);
             LCD_DrawRect(10, 300, 50, 50);
             uint16_t i=0;
             for(;i<320;i++)
             {
                     LCD_SetTextColor(i+Red);
                     LCD_DrawLine(200, i, 30, Vertical);
             }
             }
         if (xSemaphoreTake(xButtonUser2Semaphore, (portTickType)10)==pdTRUE)
             {
             LCD_Clear(White);
             //LCDDrawLine(10, 10, 120, 200, Magenta);
             //LCDDrawLine(10, 2, 220, 100, Black);

             uint16_t xmax=239;
             uint16_t ymax=319;

             uint16_t x, y;
             uint8_t prx=0;
             uint8_t pry=0;
             LCD_SetTextColor(Green);
             LCD_DrawLine(0, ymax>>1, xmax, Vertical);
             LCD_DrawLine(xmax>>1, 0, ymax, Horizontal);
             LCD_SetTextColor(Blue);
             for (x=0;x<xmax;x++)
             {
             y=(uint16_t)((ymax>>2)*sin(x*M_PI/40)+(ymax>>1));
             if (x==0)
                     LCD_SetPoint(x, y, Black);
             else
                     {
                     LCDDrawLine(prx, pry, x, y, Black);
                     }
             prx=x;
             pry=y;
             }
             }
      }
    vTaskDelayUntil(&xLastWakeTime,xFrequency);
    }
}
void vUSARTTask( void *pvParameters )
{

  portTickType xLastWakeTime;
  const portTickType xFrequency = 50;
  xLastWakeTime=xTaskGetTickCount();
  char ch;
  // Create a queue capable of containing 128 characters.
  RxQueue = xQueueCreate( configCOM0_RX_BUFFER_LENGTH, sizeof( portCHAR ) );
  TxQueue = xQueueCreate( configCOM0_TX_BUFFER_LENGTH, sizeof( portCHAR ) );
  if(( TxQueue == 0 )||( RxQueue == 0 ))
  {
      // Failed to create the queue.
      LEDOn(1);
      LEDOn(3);
      LEDOn(5);
  }

  USART1PutString(pcUsartTaskStartMsg,strlen( pcUsartTaskStartMsg ));
  for( ;; )
  {
      //Echo back
      if (Usart1GetChar(&ch))
        {
          Usart1PutChar(ch);
        }
      vTaskDelayUntil(&xLastWakeTime,xFrequency);
  }
}

