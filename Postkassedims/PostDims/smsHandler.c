/*
* smsHandler.c
*
* Created: 01-03-2017 11:16:07
*  Author: aen
*/

#include "smsHandler.h"
#define F_CPU 3868400
#include <util/delay.h>

void ReadSMS()
{
	while (ReadChar() != ',')
	{
	}
	
	char received = 0;

	while ((received = ReadChar()) != '\r')
	{
		LCDDispChar(received); //write number to lcd
	}
	
	SendString("AT+CMGR=");
	SendInteger(received);
	SendString("\r");
	
	while (ReadChar() != '+')
	{
	}
	
	int commaCount = 0;
	while (commaCount < 1)
	{
		while (ReadChar() != ',')
		{
		}
		commaCount++;
	}
	received = ReadChar();
	received = ReadChar();
	
	if(received == '+')
	{
		ReadChar();
		ReadChar();
	}
	
	char number[8] = "";

	for(int i = 0; i <8; i++)
	{
		number[i] = ReadChar();
		//LCDDispChar(number[i]); //write received to lcd
	}
	
	WaitforResponse();
	
	ReplySMS(number);
}

void ReplySMS(char* number) {
	//+CMGR: "REC UNREAD","+4522954785",,"17/03/01,14:38:36+04"
	char received = 0;
	
	//LCDDispString(number);
	
	SendString("AT+CMGS=");
	SendString(number);
	SendChar('\r');
	
	while ((received = ReadCharWithTimeout(5000)) != '>') {
		if (received != '\r' && received != '\n') {
			LCDDispChar(received);
		}
	}
	
	LCDDispChar(received);
	
	SendString("Hello!");
	SendChar(0x1A);
	LCDDispChar('A');
	
	// HAX
	
	char * errorMsg = "ERROR";
	int pointer = 0;
	char previous;
	
	while ((received = ReadChar()) != 0)
	{
		if (received != '\r' && received != '\n') {
			LCDDispChar(received);
		}
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
	
	// END HAX
	
	
	LCDDispChar('B');
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
	LCDDispChar('D');
}