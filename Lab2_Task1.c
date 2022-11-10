/*
Name: Lab2_Task1.c
Desc: Takes input from joystick and returns a string to the device connected to USART2.
	  Each output just describes the input as text.
	  The 'Delay' functions are used prevent multiple inputs from holding the key.(Lab2_Task1_Error.png shows the result if no delay function is present)
*/

//Load header
#include "st_basic.h"

int main(void)	{
	//Initiate clock settings
    ClockInit();
    //Initiate USART2 settings
    USART2_Init();
	
	//Setup GPIO for the inputs from joystick(left, right, up, down, center)
	GPIO_Init(GPIOA, 0, GPIO_INPUT_PULLDOWN);
	GPIO_Init(GPIOA, 1, GPIO_INPUT_PULLDOWN);
	GPIO_Init(GPIOA, 2, GPIO_INPUT_PULLDOWN);
	GPIO_Init(GPIOA, 3, GPIO_INPUT_PULLDOWN);
	GPIO_Init(GPIOA, 5, GPIO_INPUT_PULLDOWN);

	while (1)	{	
		//If left is pressed print "Left"
		if(GPIOA->IDR & GPIO_IDR_ID1)	{
			USART2_TX_String("Left\n");
			Delay(400);
		}
		//If right is pressed print "Right"
		else if(GPIOA->IDR & GPIO_IDR_ID2) {
			USART2_TX_String("Right\n");
			Delay(400);
		}
		//If up is pressed print "Up"
		else if(GPIOA->IDR & GPIO_IDR_ID3) {
			USART2_TX_String("Up\n");
			Delay(400);
		}
		//If down is pressed print "Down"
		else if(GPIOA->IDR & GPIO_IDR_ID5) {
			USART2_TX_String("Down\n");
			Delay(400);
		}
		//If center is pressed print "Center"
		else if(GPIOA->IDR & GPIO_IDR_ID0) {
			USART2_TX_String("Center\n");
			Delay(400);
		}
	}
}
