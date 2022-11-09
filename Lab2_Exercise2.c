/*
Name: Lab2_Exercise2.c
Desc: Copied exercise 2 from documents.
	  Used to learn about the basics of USART.
      Sends a basic string to the device connected to the USART2.
      Then will keep sending the input it got from the same device.(In this case PuTTY)
*/

//Load header
#include "st_basic.h"

int main(void)  {
    //Initiate clock settings
    ClockInit();
    //Initiate USART2 settings
    USART2_Init();
    //Send a message to device connected to USART2
    USART2_TX_String("Welcome to Embedded System!\n");
    
    while(1)    {
        //Keep sending the input from the device back to the same device
        USART2_TX(USART2_RX());
    }
}