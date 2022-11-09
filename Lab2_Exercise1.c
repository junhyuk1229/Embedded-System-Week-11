/*
Name: Lab2_Exercise1.c
Desc: Copied exercise 1 from documents.
	  Used to learn about the basics of GPIO.
	  Turns LEDs on and off depending on the input of the joystick.
	  Left and right turn on each of the LEDs, while up and down turn them off.
	  If center is pressed both LEDs turn off.
*/

//Load header
#include "st_basic.h"

int main(void)
{
	//Initiate clock settings
	ClockInit();

	//Setup GPIO for the inputs from joystick(left, right, up, down, center)
	GPIO_Init(GPIOA, 0, GPIO_INPUT_PULLDOWN);
	GPIO_Init(GPIOA, 1, GPIO_INPUT_PULLDOWN);
	GPIO_Init(GPIOA, 2, GPIO_INPUT_PULLDOWN);
	GPIO_Init(GPIOA, 3, GPIO_INPUT_PULLDOWN);
	GPIO_Init(GPIOA, 5, GPIO_INPUT_PULLDOWN);
	//Setup GPIO outputs for the LEDS
	GPIO_Init(GPIOB, 2, GPIO_OUTPUT);
	GPIO_Init(GPIOE, 8, GPIO_OUTPUT);
	
	while (1)
	{
		//If left is pressed turn on red LED
		if (GPIOA->IDR & GPIO_IDR_ID1) GPIOB->BSRR = GPIO_BSRR_BS2;
		//If right is pressed turn on green LED
		else if (GPIOA->IDR & GPIO_IDR_ID2) GPIOE->BSRR = GPIO_BSRR_BS8;
		//If up is pressed turn off red LED
		else if (GPIOA->IDR & GPIO_IDR_ID3) GPIOB->BSRR = GPIO_BSRR_BR2;
		//If down is pressed turn off green LED
		else if (GPIOA->IDR & GPIO_IDR_ID5) GPIOE->BSRR = GPIO_BSRR_BR8;
		//If center is pressed turn off both LEDs
		else if (GPIOA->IDR & GPIO_IDR_ID0)
		{
			GPIOB->BSRR = GPIO_BSRR_BR2;
			GPIOE->BSRR = GPIO_BSRR_BR8;
		}
	}
}
