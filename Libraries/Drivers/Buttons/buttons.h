/*
 * buttons.h
 *
 *  Created on: Nov 7, 2011
 *      Author: MMM
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_
#include "STM32f10x.h"
//GPIO_PortSourceGPIOA, GPIO_PinSource0
#define BWAKEUP 			GPIO_Pin_0
#define BWAKEUPPORT			GPIOA
#define BWAKEUPPORTCLK		RCC_APB2Periph_GPIOA
#define BWAKEUPPINSOURCE 	GPIO_PinSource0
#define BWAKEUPPORTSOURCE	GPIO_PortSourceGPIOA

#define BTAMPER 			GPIO_Pin_13
#define BTAMPERPORT			GPIOC
#define BTAMPERPORTCLK		RCC_APB2Periph_GPIOC
#define BTAMPERPINSOURCE 	GPIO_PinSource13
#define BTAMPERPORTSOURCE	GPIO_PortSourceGPIOC

#define BUSER1 				GPIO_Pin_8
#define BUSER1PORT			GPIOA
#define BUSER1PORTCLK		RCC_APB2Periph_GPIOA
#define BUSER1PINSOURCE 	GPIO_PinSource8
#define BUSER1PORTSOURCE	GPIO_PortSourceGPIOA

#define BUSER2 				GPIO_Pin_3
#define BUSER2PORT			GPIOD
#define BUSER2PORTCLK		RCC_APB2Periph_GPIOD
#define BUSER2PINSOURCE 	GPIO_PinSource3
#define BUSER2PORTSOURCE	GPIO_PortSourceGPIOD

void ButtonsInit(void);
void ButtonsInitEXTI(void);
uint32_t ButtonRead(GPIO_TypeDef* Button_Port, uint16_t Button);
void ButtonSetStatus(uint32_t status);
void ButtonResetStatus(void);
uint32_t ButtonGetStatus(void);


#endif /* BUTTONS_H_ */
