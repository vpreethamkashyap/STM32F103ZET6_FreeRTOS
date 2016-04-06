/*
 * usart.h
 */

#ifndef USART_H_
#define USART_H_
#include "STM32f10x.h"
void Usart1Init(void);
uint32_t Usart1GetChar(char *ch);
uint32_t Usart1PutChar(char ch);
void  USART1PutString( const char * const pcString, unsigned long ulStringLength);
#endif /* USART_H_ */
