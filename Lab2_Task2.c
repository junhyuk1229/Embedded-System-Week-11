/*
Name: Lab2_Task2.c
Desc: Takes input from USART2(PuTTY) and changes state of LED.
	  Each direction is shown as the keys 'w', 'a', 's', 'd', ' ' for top, left, down, right, center
	  Left and right turn on each of the LEDs, while up and down turn them off.
	  If center is pressed both LEDs turn off.
*/

//Load header
#include "st_basic.h"

int main(void)	{
	//Initiate clock settings
    ClockInit();
    //Initiate USART2 settings
    USART2_Init();
	
	//Setup GPIO outputs for the LEDS
	GPIO_Init(GPIOB, 2, GPIO_OUTPUT);
	GPIO_Init(GPIOE, 8, GPIO_OUTPUT);
	
	while (1)	{	
		//Read character input from USART2 and save it in 'tempChar'
		char tempChar = USART2_RX();
		//If input is left, turn on red light
		if(tempChar == 'a') GPIOB->BSRR = GPIO_BSRR_BS2;
		//If input is right, turn on green light
		else if(tempChar == 'd') GPIOE->BSRR = GPIO_BSRR_BS8;
		//If input is up, turn off red light
		else if(tempChar == 'w') GPIOB->BSRR = GPIO_BSRR_BR2;
		//If input is down, turn off green light
		else if(tempChar == 's') GPIOE->BSRR = GPIO_BSRR_BR8;
		//If input is center, turn off both lights
		else if(tempChar == ' ')	{
			GPIOB->BSRR = GPIO_BSRR_BR2;
			GPIOE->BSRR = GPIO_BSRR_BR8;
		}
	}
}
