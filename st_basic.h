#ifndef _ST_BASIC_
#define _ST_BASIC_

#ifndef STM32L476xx
#define STM32L476xx
#endif

#include <stm32l4xx.h>
//Used in USART2_RX_String()
#include <string.h>

typedef enum GPIO_Mode	{
	GPIO_INPUT, GPIO_OUTPUT, GPIO_ALTERNATIVE, GPIO_ANALOG,
	GPIO_INPUT_PULLUP, GPIO_INPUT_PULLDOWN = 0x8
} GPIO_Mode;

void ClockInit(void);
void Delay(unsigned int duration);
void GPIO_Init(GPIO_TypeDef *port, unsigned int pin, GPIO_Mode mode);
void USART2_Init(void);
char USART2_RX(void);
void USART2_TX(char character);
void USART2_RX_String(char *string);
void USART2_TX_String(const char *string);
void SysTick_Handler(void);

#endif
