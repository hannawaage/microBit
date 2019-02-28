#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"
#define BUTTON_A_PIN 17
#define BUTTON_B_PIN 26
#define SUPPLY_PIN0 13
#define SUPPLY_PIN1 14
#define SUPPLY_PIN2 15


int main(void) 
{
	// Configure LED Matrix
	for(int i = 4; i < 13; ++i){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	} 
	
	// Configure buttons
	GPIO->PIN_CNF[BUTTON_A_PIN] = 0; // BUTTON A
	GPIO->PIN_CNF[BUTTON_B_PIN] = 0; // BUTTON B

	GPIOTE->CONFIG[0] |= (1 << 0) | (17 << 8 ) | (2 << 16); 
	for (int i = 1; i < 4; ++i) 
	{
		GPIOTE->CONFIG[i] |= (3 << 0) | ((i + 12) << 8) | (3 << 16) | (0 << 20);
	}

	for (int i = 1; i < 4; ++i) 
	{
		PPI->PPI_CH[i].EEP = (uint32_t)&(GPIOTE->IN[0]);
		PPI->PPI_CH[i].TEP = (uint32_t)&(GPIOTE->OUT[i]);
		PPI->CHENSET = (1 << i);
	}
	

	while(1);
	return 0; 
}

