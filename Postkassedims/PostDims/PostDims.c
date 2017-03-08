/*
* PostDims.c
*
* Created: 16-Feb-17 15:00:24
*  Author: Andreas
*/


#include <avr/io.h>
#define F_CPU 3868400
#include <util/delay.h>
#include <stdio.h>
#include <avr/cpufunc.h>
#include "memoryHandler.h"
#include "smsHandler.h"
#include "uart.h"

#define DDR_switch DDRA
#define PIN_switch PINA
#define DDR_led DDRB
#define PORT_led PORTB
int main(void)
{
	DDR_switch = 0x00;
	DDR_led = 0xFF;
	PORT_led = 0xFF;
	SetupMemory();
	InitUART(9600, 8);
	InitSMS('0', '1', "3257");
	DeleteAll(20);
	
	char receivedChar = 0;
	char header[100] = {0};
	char body[100] = {0};
	
	while (1) {
		receivedChar = ReadChar();
		
		if(receivedChar == '+') {
			while (ReadChar() != ',') {
			}
			char index = ReadChar();
			ReadChar();
			ReadChar();
			ReadSMS(index, header, body);
			char number[8];
			ExtractNumber(header, number);
			ReplySMS(number, body, 100);
		}
		
		if ((PIN_switch & 0b00000001) == 0) {
			break;
		}
	}
	
	_NOP();
	
	while (1);
}