#include <stdint.h>
#include "gpio.h"
#include "uart.h"
#define UART ((NRF_UART_REG*)0X40002000)

typedef struct {
//TASKS
	volatile uint32_t STARTRX; 
	volatile uint32_t STORPRX; 
	volatile uint32_t STARTTX; 
	volatile uint32_t STOPTX;
	volatile uint32_t BUFFER0[3];
	volatile uint32_t SUSPEND;
	volatile uint32_t BUFFER1[56];
//EVENTS
	volatile uint32_t CTS;
	volatile uint32_t NCTS;
	volatile uint32_t RXDRDY;
	volatile uint32_t BUFFER2[4];
	volatile uint32_t TXDRDY;
	volatile uint32_t BUFFER3[1];
	volatile uint32_t ERROR;
	volatile uint32_t BUFFER4[7];
	volatile uint32_t RXTO;
	volatile uint32_t BUFFER5[110];
//REGISTERS
	volatile uint32_t INTEN;
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t BUFFER6[93];
	volatile uint32_t ERRORSRC;
	volatile uint32_t BUFFER7[31];
	volatile uint32_t ENABLE;
	volatile uint32_t BUFFER8;
	volatile uint32_t PSELRTS;
	volatile uint32_t PSELTXD;
	volatile uint32_t PSELCTS;
	volatile uint32_t PSELRXD; 
	volatile uint32_t RXD;
	volatile uint32_t TXD;
	volatile uint32_t BUFFER9;
	volatile uint32_t BAUDRATE; 
	volatile uint32_t BUFFER10[17];
	volatile uint32_t CONFIG;
} NRF_UART_REG;



void uart_init() {
	GPIO->PIN_CNF[24] = 1;
	GPIO->PIN_CNF[25] = 0;
	UART->BAUDRATE = 0x00275000;  
	UART->PSELCTS = 0xFFFFFFFF;
	UART->PSELRTS = 0xFFFFFFFF;
	UART->PSELTXD = 24;
	UART->PSELRXD = 25;
	UART->ENABLE = 4; 
	UART->STARTRX = 1; 
}

void uart_send(char letter) {
	UART->STARTTX = 1;
	UART->TXD = letter;
	while(!UART->TXDRDY);
	UART->TXDRDY = 0;  
	UART->STOPTX = 1;
}
char uart_read()
{
	if(!UART->RXDRDY)
		return '\0'; 
	UART->RXDRDY = 0;
	return UART->RXD;  	
}

void send_A_B() 
{
	int b_pressed = GPIO->IN & (1 << 26);		
	int a_pressed = GPIO->IN & (1 << 17);

	if(!b_pressed){
		uart_send('B');
	}

	if(!a_pressed){
		uart_send('A'); 
	}

}

void listen() 
{
	if(uart_read() != '\0')
	{
		if(!(GPIO->OUT & (1 << 13))) 
		{
			for(int i = 13; i <= 15; i++){
				GPIO->OUTSET = (1 << i);
			}
		}
		else 
		{
			for(int i = 13; i <= 15; i++){
				GPIO->OUTCLR = (1 << i);
			} 
		}
	}
}



