/*
* PostDims.c
*
* Created: 16-Feb-17 15:00:24
*  Author: Andreas
*/


#include <avr/io.h>
#define F_CPU 3868400
#include <util/delay.h>
#include <avr/cpufunc.h>
#include <stdio.h>
#include <string.h>
#include "memoryHandler.h"
#include "localMemoryHandler.h"
#include "smsHandler.h"
#include "uart.h"
#include "phonenumber.h"

#define DDR_switch DDRA
#define PIN_switch PINA
#define DDR_led DDRB
#define PORT_led PORTB

FlushArray(char *array, char size);
SMSType ParseBody(char *number, char *body, char size);
void HandleMemoryFromType(SMSType type, char *number);

char receivedChar = 0;
char header[100] = {0};
char body[100] = {0};

phonenumber numbers[10];
char phoneNumberCounter = 0;

int main(void)
{
	// PRODUCTION  --v
	DDR_switch = 0x00;
	DDR_led = 0xFF;
	PORT_led = 0xFF;
	SetupMemory();
	PORT_led &= ~(1<<0);
	InitUART(9600, 8);
	PORT_led &= ~(1<<1);
	InitSMS('0', '1', "3257");
	PORT_led &= ~(1<<2);
	DeleteAll(20);
	PORT_led &= ~(1<<3);
	
	LoadAllNumbersFromEEPROM(numbers, &phoneNumberCounter);

	while (1) {
		receivedChar = ReadChar();
		
		if(receivedChar == '+') {
			PORT_led |= ((1<<4) | (1<<5) | (1<<6));
			while (ReadChar() != ',') {
			}
			char index = ReadChar();
			// Read CR and LF after index
			ReadChar();
			ReadChar();
			PORT_led &= ~(1<<4);
			ReadSMS(index, header, body);
			DeleteSMS(index);
			PORT_led &= ~(1<<5);
			char number[9];
			ExtractNumber(header, number);
			UART_Flush();
			SMSType type = ParseBody(number, body, 100);
			SendSMS(number, type);
			PORT_led &= ~(1<<6);

			// Handle local memory (subscribe/unsubscribe
			HandleMemoryFromType(type, number);

			// Empty header and body
			FlushArray(header, 100);
			FlushArray(body, 100);
		}
		
		if ((PIN_switch & 0b00000001) == 0) {
			break;
		}
	}
	
	_NOP();
	
	while (1);
}

FlushArray(char *array, char size) {
	for (char i = 0; i < size; i++) {
		if (array[i] == 0) {
			break;
		}
		array[i] = 0;
	}
}

SMSType ParseBody(char *number, char *body, char size) {
	if (strcmp("SUBSCRIBE", body) == 0) {
		if (FindNumber(numbers, number, phoneNumberCounter) > -1) {
			return ALREADY_SUBSCRIBED;
		}
		else if (phoneNumberCounter >= 10) {
			return NUMBERS_FULL;
		}

		return SUBSCRIBED;
	}
	else if (strcmp("UNSUBSCRIBE", body) == 0) {
		if (FindNumber(numbers, number, phoneNumberCounter) == -1) {
			return NOT_SUBSCRIBED;
		}
		return UNSUBSCRIBED;
	}
	else if (strcmp("HELP", body) == 0) {
		return HELP;
	}
	else if (strcmp("STATUS", body) == 0) {
		return STATUS;
	}

	return UNKNOWN_COMMAND;
}

void HandleMemoryFromType(SMSType type, char *number) {
	if (type == SUBSCRIBED) {
		SaveNumberInLocalMemory(numbers, number, &phoneNumberCounter);
		SaveNumber(number);
	}
	else if (type == UNSUBSCRIBED) {
		RemoveNumberFromLocalMemory(numbers, number, &phoneNumberCounter);
		DeleteNumber(number);
	}
}

