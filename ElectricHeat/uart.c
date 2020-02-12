/*
 * uart.c
 *
 * Created: 26.12.2017 15:46:01
 *  Author: mike
 */ 
#define BAUD 9600

#include <avr/io.h>
#include <util/setbaud.h>

void USART_init(){
	UCSR0A=0x00;
	UCSR0B=(1<<RXEN0) | (1<<TXEN0);
	UCSR0C=0x06;
	UBRR0H=UBRRH_VALUE;
	UBRR0L=UBRRL_VALUE;
}

void USART0_write(uint8_t data){
	while(!( UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

