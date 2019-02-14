#include <stdint.h>

#define GPIO ((NRF_GPIO_REGS*)0x50000000)

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t RESERVED1[120];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;

	int sleep = 0;
	int b_pressed = 1; 
	int a_pressed = 1; 
	while(1){
		 
		/* Check if button B is pressed;
		 * turn on LED matrix if it is. */
		b_pressed = GPIO->IN & 0b00000100000000000000000000000000;	
		a_pressed = GPIO->IN & 0b00000000000000100000000000000000;	
		if(!b_pressed){
			for(int i = 13; i <= 15; i++){
				GPIO->OUTSET = (1 << i);
			}
		}

		/* Check if button A is pressed;
		 * turn off LED matrix if it is. */
		if(!a_pressed){
			for(int i = 13; i <= 15; i++){
				GPIO->OUTCLR = (1 << i);
			}   
		}


		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
