/*
* smsHandler.c
*
* Created: 01-03-2017 11:16:07
*  Author: aen
*/

#define F_CPU 3868400

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "smsHandler.h"
#include "uart.h"
#include "lcd162.h"

const char CR = 13;
const char LF = 10;
const char CTRL_Z = 26;
const char MAX_SIZE = 100;

void SendSMS(char *number, SMSType type) {
	char tmp[100] = {0};
	char counter = 0;
	SendString("AT+CMGS=");
	SendString(number);
	SendChar(CR);
	while (ReadChar() != '>') {
		
	}
	_delay_ms(200);
	if (type == SUBSCRIBED) {
		SendString("You subscribed to mail notifications!");
	}
	else if (type == ALREADY_SUBSCRIBED) {
		SendString("You are already subscribed");
	}
	else if (type == UNSUBSCRIBED) {
		SendString("You unsubscribed from mail notifications...");
	}
	else if (type == NOT_SUBSCRIBED) {
		SendString("You are not subscribed...");
	}
	else if (type == UNKNOWN_COMMAND) {
		SendString("Command not understood. Please send SUBSCRIBE or UNSUBSCRIBE.\nWrite HELP for further information.");
	}
	else if (type == NEW_MAIL) {
		SendString("New mail just arrived!");
	}
	else if (type == HELP) {
		SendString("SUBSCRIBE: Get notifications.\nUNSUBSCRIBE: Stop getting notifications.\nSTATUS: If there is currently mail.");
	}
	else if (type == STATUS) {
		SendString("Maybe there is mail.");
	}
	else if (type == NUMBERS_FULL) {
		SendString("No more numbers can be subscribed.");
	}
	SendChar(CTRL_Z);
	
	WaitforResponse();
}

void ReadSMS(char index, char *header, char *body) {
	SendString("AT+CMGR=");
	SendChar(index);
	SendString("\r");
	
	ReadChar();
	ReadChar();
	
	// Read header
	ReadLine(header, MAX_SIZE);
	
	// Read body
	ReadLine(body, MAX_SIZE);
	
	WaitforResponse();
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
		}
		else {
			previous = received;
		}
		
		if (received == errorMsg[pointer]) {
			pointer++;
		}
		else {
			pointer = 0;
		}
		
		if (pointer >= 5) {
			ReadChar();
			ReadChar();
			break;
		}
	}
	
	_delay_ms(200);
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
	number[8] = 0;
}

void ReadLine(char *output, char size) {
	char received = 0;
	char previous = 0;
	
	for (int i = 0; i < size; i++) {
		received = ReadChar();
		if (received != CR && received != LF) {
			output[i] = received;
		}
		if (previous == CR && received == LF) {
			break;
		}
		previous = received;
	}
}