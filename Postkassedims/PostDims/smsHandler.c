/*
* smsHandler.c
*
* Created: 01-03-2017 11:16:07
*  Author: aen
*/

#define F_CPU 3868400
#include <util/delay.h>
#include <string.h>
#include "smsHandler.h"
#include "uart.h"
#include "lcd162.h"

const char CR = 13;
const char LF = 10;
const char MAX_SIZE = 100;

void SendSMS(char *number, SMSType type) {
	SendString("AT+CMGS=");
	SendString(number);
	SendChar('\r');
	while (ReadCharWithTimeout(5000) != '>') {
	}
	if (type == SUBSCRIBED) {
		SendString("You subscribed to mail notifications!");
	} 
	else if (type == UNSUBSCRIBED) {
		SendString("You unsubscribed from mail notifications...");
	}
	else if (type == UNKNOWN_COMMAND) {
		SendString("Command not understood. Please send SUBSCRIBE or UNSUBSCRIBE");
	}
	else if (type == NEW_MAIL) {
		SendString("New mail just arrived!");
	}
	SendChar(0x1A);
	
	WaitforResponse();
}

void ReadSMS(char index, char *header, char *body) {	
	SendString("AT+CMGR=");
	SendChar(index);
	SendString("\r");
	
	ReadChar();
	ReadChar();
	
	char received = 0;
	char previous = 0;
	
	// Read header
	for (int i = 0; i < MAX_SIZE; i++) {
		received = ReadChar();
		if (received != CR && received != LF) {
			header[i] = received;
		}
		if (previous == CR && received == LF) {
			break;
		}
		previous = received;
	}
	
	// Read body
	received = 0;
	previous = 0;
	for (int i = 0; i < MAX_SIZE; i++) {
		received = ReadChar();
		if (received != CR && received != LF) {
			body[i] = received;
		}
		if (previous == CR && received == LF) {
			break;
		}
		previous = received;
	}
	
	WaitforResponse();
}

void ReplySMS(char* number, char *body, char bodySize) {
	char received = 0;
	
	if (strcmp("SUBSCRIBE", body) == 0) {
		SendSMS(number, SUBSCRIBED);
	}
	else if (strcmp("UNSUBSCRIBE", body) == 0) {
		SendSMS(number, UNSUBSCRIBED);
	}
	else {
		SendSMS(number, UNKNOWN_COMMAND);
	}
}

void DeleteSMS(int index) {
	
	SendString("AT+CMGD=");
	SendInteger(index);
	SendString("\r");
	
	WaitforResponse();
}

void WaitforResponse() {
	
	char * errorMsg = "ERROR";
	int pointer = 0;
	char received;
	char previous;
	
	while ((received = ReadChar()) != 0)
	{
		if (previous == 'O' && received == 'K')
		{
			ReadChar();
			ReadChar();
			break;
			} else {
			previous = received;
		}
		
		if (received == errorMsg[pointer]) {
			pointer++;
			} else {
			pointer = 0;
		}
		
		if (pointer >= 5) {
			ReadChar();
			ReadChar();
			break;
		}
	}
	
	_delay_ms(150);
}

void WritePin(char* pin) {
	
	SendString("AT+CPIN=");
	SendString(pin);
	SendChar('\r');
	WaitforResponse();
}

void SetEcho(char echo) {
	SendString("ATE");
	SendChar(echo);
	SendChar('\r');
	
	WaitforResponse();
}

void SetTextMode(char mode){
	
	SendString("AT+CMGF=");
	SendChar(mode);
	SendChar('\r');
	
	WaitforResponse();
}

void DeleteAll(int spaces) {
	for (int i = 0; i < spaces; i++) {
		DeleteSMS(i);
	}
}

void ConfigSMS() {
	
	SendString("AT+CNMI=3,1\r");
	
	WaitforResponse();
	
}

void InitSMS(char echo, char mode, char* pin) {
	SetEcho(echo);
	SetTextMode(mode);
	WritePin(pin);
	ConfigSMS();
}

void ExtractNumber(char *header, char *number) {
	char counter = 0;
	while (header[counter] != ',') {
		counter++;
	}
	counter = counter + 2;
	if (header[counter] == '+') {
		counter = counter + 3;
	}
	for (int i = 0; i < 8; i++, counter++) {
		number[i] = header[counter];
	}
}