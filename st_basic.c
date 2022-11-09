/*
Name: st_basic.c
Desc: Saves all functions used for class material.
	  Doesn't contain main function.
*/

//Load header
#include "st_basic.h"

//Saves milliseconds as global variable
static unsigned int sysMillis = 0;

/*
Function Name: ClockInit
Input Variables: None
Output Variables: None
Desc: Sets up initial settings for clock for use.
*/
void ClockInit(void)
{
	FLASH->ACR |= FLASH_ACR_LATENCY_4WS;
	
	RCC->PLLCFGR = RCC_PLLCFGR_PLLREN | (20 << RCC_PLLCFGR_PLLN_Pos)
	             | RCC_PLLCFGR_PLLM_0 | RCC_PLLCFGR_PLLSRC_HSI;
	
	RCC->CR |= RCC_CR_PLLON | RCC_CR_HSION;
	
	while (!((FLASH->ACR & FLASH_ACR_LATENCY_4WS) && (RCC->CR & RCC_CR_PLLRDY)
		    && (RCC->CR & RCC_CR_HSIRDY)));
	
	RCC->CFGR = RCC_CFGR_SW_PLL;
	
	RCC->CR &= ~RCC_CR_MSION;
	
	SysTick->LOAD = SysTick->CALIB & SysTick_LOAD_RELOAD_Msk;
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

/*
Function Name: GPIO_Init
Input Variables: None
Output Variables: None
Desc: Sets up initial settings for GPIO.
*/
void GPIO_Init(GPIO_TypeDef *port, unsigned int pin, GPIO_Mode mode)
{
	unsigned int modeIn32Bit = ((unsigned int)(mode & 3) << (2 * pin));
	unsigned int pullUpDown = ((unsigned int)(mode >> 2) << (2 * pin));
	
	RCC->AHB2ENR |= (1 << (((unsigned int)port - GPIOA_BASE) >> 10));
	
	port->MODER |= modeIn32Bit;
	port->MODER &= (modeIn32Bit | ~((unsigned int)3 << (2 * pin)));
	
	port->PUPDR |= pullUpDown;
	port->PUPDR &= (pullUpDown | ~((unsigned int)3 << (2 * pin)));
}

/*
Function Name: USART2_Init
Input Variables: None
Output Variables: None
Desc: Sets up initial settings for USART2 use.
*/
void USART2_Init(void)	{
	RCC->CCIPR |= RCC_CCIPR_USART2SEL_1;
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;
	
	GPIO_Init(GPIOD, 5, GPIO_ALTERNATIVE);
	GPIO_Init(GPIOD, 6, GPIO_ALTERNATIVE);
	GPIOD->AFR[0] |= (7 << GPIO_AFRL_AFSEL6_Pos) | (7 << GPIO_AFRL_AFSEL5_Pos);
	
	USART2->BRR = 139;
	USART2->CR3 |= USART_CR3_OVRDIS;
	USART2->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

/*
Function Name: Delay
Input Variables: duration: Time in milliseconds for program to delay.
Output Variables: None
Desc: Keeps delaying program till milliseconds in duration.
*/
void Delay(unsigned int duration)	{
	//Sets prevMillis as past milliseconds.
	unsigned int prevMillis = sysMillis;
	//If duration passed in milliseconds exit program.
	while (sysMillis - prevMillis <= duration);
}

/*
Function Name: USART2_RX
Input Variables: None
Output Variables: Character that is received through the USART2
Desc: Gets a character through USART2 from device to computer
*/
char USART2_RX(void)	{
	//Loop till input buffer is filled
	while (!(USART2->ISR & USART_ISR_RXNE));
	//Return input character
	return (char)USART2->RDR;
}

/*
Function Name: USART2_TX
Input Variables: character: Character that is going to be sent through the USART2
Output Variables: None
Desc: Sends a character through USART2 from computer to device
*/
void USART2_TX(char character)	{
	//Loop till output buffer is empty
	while (!(USART2->ISR & USART_ISR_TXE));
	//Send output through USART2
	USART2->TDR = character;
}

/*
Function Name: USART2_RX_String
Input Variables: string: Used to save input string from USART2
Output Variables: None
Desc: Gets a string through USART2 from device to computer
*/
void USART2_RX_String(char* string)	{
	//Variable used to get input character
	char tempChar;
	//Get character from USART2 and check if it is a 'Enter' key
	//If input is not 'Enter' key add input to output string
	while((tempChar = USART2_RX()) != '\r') strncat(string, &tempChar, 1);
}

/*
Function Name: USART2_TX_String
Input Variables: string: String that is going to be sent through the USART2
Output Variables: None
Desc: Sends a string through USART2 from computer to device
*/
void USART2_TX_String(const char *string)	{
	//Keeps looping till 'string' is empty
	//Sends char at address to USART2 then move address by 1
	while (*string != '\0') USART2_TX(*string++);
}

/*
Function Name: SysTick_Handler
Input Variables: None
Output Variables: None
Desc: Increments 'sysMillis' every millisecond
*/
void SysTick_Handler(void) { sysMillis++; }
