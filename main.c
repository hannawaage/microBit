#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "gpio.h"

ssize_t _write(int fd, const void *buf, size_t count){
	char * letter = (char *)(buf);
	for(int i = 0; i < count; i++){
		uart_send(*letter);
		letter++;
	}
	return count;
}

int main(void) 
{
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	} 
	
	// Configure buttons
	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;

	int sleep = 0;
	uart_init();

	iprintf("Norway has %d counties.\n\r", 18);

	while(1) 
	{
		listen(); 
		send_A_B(); 
		sleep = 10000;
		while(--sleep);
	}
}
