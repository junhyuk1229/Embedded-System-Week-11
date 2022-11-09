/*
Name: Lab2_Task2_Adv.c
Desc: Takes input from USART2(PuTTY) and saves it into a string.
	  Similar to 'Lab_Task2.c' but takes strings instead of characters
      Each direction is shown as the keys 'Up', 'Left', 'Down', 'Right', 'Center' for top, left, down, right, center
	  Left and right turn on each of the LEDs, while up and down turn them off.
	  If center is pressed both LEDs turn off.
*/

//Load header
#include "st_basic.h"
//Used for malloc in line 27
#include <stdlib.h>

int main(void)	{
	//Initiate clock settings
    ClockInit();
    //Initiate USART2 settings
    USART2_Init();
	
	//Setup GPIO outputs for the LEDS
	GPIO_Init(GPIOB, 2, GPIO_OUTPUT);
	GPIO_Init(GPIOE, 8, GPIO_OUTPUT);
	
	while (1)	{
		//Make a char address to save input string
		char *inputString = (char *)malloc(sizeof(char) * 5);
		//Read input string until enter is pressed and save it to the address
		USART2_RX_String(inputString);
		
		//If input string is "Left", turn on red light
		if(strcmp(inputString, "Left") == 0) GPIOB->BSRR = GPIO_BSRR_BS2;
		//If input string is "Right", turn on green light
		else if(strcmp(inputString, "Right") == 0) GPIOE->BSRR = GPIO_BSRR_BS8;
		//If input string is "Up", turn off red light
		else if(strcmp(inputString, "Up") == 0) GPIOB->BSRR = GPIO_BSRR_BR2;
		//If input string is "Down", turn off green light
		else if(strcmp(inputString, "Down") == 0) GPIOE->BSRR = GPIO_BSRR_BR8;
		//If input string is "Center", turn off both lights
		else if(strcmp(inputString, "Center") == 0)	{
			GPIOB->BSRR = GPIO_BSRR_BR2;
			GPIOE->BSRR = GPIO_BSRR_BR8;
		}
		
		//Free memory space to get next input string
		free(inputString);
	}
}
