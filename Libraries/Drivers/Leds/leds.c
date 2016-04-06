/*
 * leds.c
 *
 *  Created on: Nov 3, 2011
 *      Author: MMM
 */
#include "leds.h"

void LEDsInit(void)
{
  //GPIO structure used to initialize LED port
  GPIO_InitTypeDef GPIO_InitStructure;
  //Enable clock on APB2 pripheral bus where LEDs are connected
  RCC_APB2PeriphClockCmd(LEDPORTCLK,  ENABLE);
  //select pins to initialize LED
  GPIO_InitStructure.GPIO_Pin = LED1|LED2|LED3|LED4|LED5;
  //select output push-pull mode
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  //select GPIO speed
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LEDPORT, &GPIO_InitStructure);
  //initially LEDs off
  GPIO_SetBits(LEDPORT, LED1|LED2|LED3|LED4|LED5);
}
void LEDOn(uint32_t LED_n)
{
  if (LED_n==1)
  {
	  GPIO_ResetBits(LEDPORT, LED1);
  }
  if (LED_n==2)
  {
	  GPIO_ResetBits(LEDPORT, LED2);
  }
  if (LED_n==3)
  {
	  GPIO_ResetBits(LEDPORT, LED3);
  }
  if (LED_n==4)
  {
	  GPIO_ResetBits(LEDPORT, LED4);
  }
  if (LED_n==5)
  {
	  GPIO_ResetBits(LEDPORT, LED5);
  }
}
void LEDOff(uint32_t LED_n)
{
  if (LED_n==1)
  {
	  GPIO_SetBits(LEDPORT, LED1);
  }
  if (LED_n==2)
  {
	  GPIO_SetBits(LEDPORT, LED2);
  }
  if (LED_n==3)
  {
	  GPIO_SetBits(LEDPORT, LED3);
  }
  if (LED_n==4)
  {
	  GPIO_SetBits(LEDPORT, LED4);
  }
  if (LED_n==5)
  {
	  GPIO_SetBits(LEDPORT, LED5);
  }
}
void LEDToggle(uint32_t LED_n)
{
  if (LED_n==1)
  {
	  if(GPIO_ReadOutputDataBit(LEDPORT, LED1))  //toggle led
	  {
		  GPIO_ResetBits(LEDPORT, LED1); //set to zero
	  }
	     else
	     {
	    	 GPIO_SetBits(LEDPORT, LED1);//set to one
	     }
  }
  if (LED_n==2)
  {
	  if(GPIO_ReadOutputDataBit(LEDPORT, LED2))  //toggle led
	  {
		  GPIO_ResetBits(LEDPORT, LED2); //set to zero
	  }
	     else
	     {
	    	 GPIO_SetBits(LEDPORT, LED2);//set to one
	     }
  }
  if (LED_n==3)
  {
	  if(GPIO_ReadOutputDataBit(LEDPORT, LED3))  //toggle led
	  {
		  GPIO_ResetBits(LEDPORT, LED3); //set to zero
	  }
	     else
	     {
	    	 GPIO_SetBits(LEDPORT, LED3);//set to one
	     }
  }
  if (LED_n==4)
  {
	  if(GPIO_ReadOutputDataBit(LEDPORT, LED4))  //toggle led
	  {
		  GPIO_ResetBits(LEDPORT, LED4); //set to zero
	  }
	     else
	     {
	    	 GPIO_SetBits(LEDPORT, LED4);//set to one
	     }
  }
  if (LED_n==5)
  {
	  if(GPIO_ReadOutputDataBit(LEDPORT, LED5))  //toggle led
	  {
		  GPIO_ResetBits(LEDPORT, LED5); //set to zero
	  }
	     else
	     {
	    	 GPIO_SetBits(LEDPORT, LED5);//set to one
	     }
  }
}
