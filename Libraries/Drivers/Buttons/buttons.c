/*
 * buttons.c
 *
 *  Created on: Nov 7, 2011
 *      Author: MMM
 */

#include "buttons.h"
static volatile uint32_t buttonStatus=0;
void ButtonSetStatus(uint32_t status)
{
	buttonStatus = status;
}
void ButtonResetStatus(void)
{
	buttonStatus = 0;
}
uint32_t ButtonGetStatus(void)
{
	uint32_t temp;
	temp=buttonStatus;
	ButtonResetStatus();
	return temp;
}
void ButtonsInit(void)
{
  //GPIO structure used to initialize Button pins
  GPIO_InitTypeDef GPIO_InitStructure;
  //Enable clock on APB2 pripheral bus where buttons are connected
  RCC_APB2PeriphClockCmd(BWAKEUPPORTCLK|BTAMPERPORTCLK|BUSER1PORTCLK|BUSER2PORTCLK,  ENABLE);
  //select pins to initialize WAKEUP and USER1 buttons
  GPIO_InitStructure.GPIO_Pin = BWAKEUP|BUSER1;
  //select floating input mode
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  //select GPIO speed
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(BWAKEUPPORT, &GPIO_InitStructure);
  //select pins to initialize TAMPER button
  GPIO_InitStructure.GPIO_Pin = BTAMPER;
  GPIO_Init(BTAMPERPORT, &GPIO_InitStructure);
  //select pins to initialize USER2 button
  GPIO_InitStructure.GPIO_Pin = BUSER2;
  GPIO_Init(BUSER2PORT, &GPIO_InitStructure);
}
void ButtonsInitEXTI(void)
{
	//enable AFIO clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,  ENABLE);
	EXTI_InitTypeDef EXTI_InitStructure;
	//NVIC structure to set up NVIC controller
	NVIC_InitTypeDef NVIC_InitStructure;
	//GPIO structure used to initialize Button pins
	//Connect EXTI Lines to Button Pins
	GPIO_EXTILineConfig(BWAKEUPPORTSOURCE, BWAKEUPPINSOURCE);
	GPIO_EXTILineConfig(BTAMPERPORTSOURCE, BTAMPERPINSOURCE);
	GPIO_EXTILineConfig(BUSER1PORTSOURCE, BUSER1PINSOURCE);
	GPIO_EXTILineConfig(BUSER2PORTSOURCE, BUSER2PINSOURCE);
	//select EXTI line0
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	//select interrupt mode
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	//generate interrupt on rising edge
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	//enable EXTI line
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	//send values to registers
	EXTI_Init(&EXTI_InitStructure);
	//select EXTI line13
	EXTI_InitStructure.EXTI_Line = EXTI_Line13;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_InitStructure.EXTI_Line = EXTI_Line3;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_InitStructure.EXTI_Line = EXTI_Line8;
	EXTI_Init(&EXTI_InitStructure);
	//disable AFIO clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,  DISABLE);
	//configure NVIC
	//select NVIC channel to configure
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	//set priority to lowest
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	//set subpriority to lowest
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	//enable IRQ channel
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//update NVIC registers
	NVIC_Init(&NVIC_InitStructure);
	//select NVIC channel to configure
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_Init(&NVIC_InitStructure);
}
uint32_t ButtonRead(GPIO_TypeDef* Button_Port, uint16_t Button)
{
  return !GPIO_ReadInputDataBit(Button_Port, Button);
}
