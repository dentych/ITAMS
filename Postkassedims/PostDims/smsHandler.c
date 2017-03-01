/*
* smsHandler.c
*
* Created: 01-03-2017 11:16:07
*  Author: aen
*/

#include "smsHandler.h"

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
	number[0] = ReadChar();

	for(int i = 1; i <8; i++)
	{
		number[i] = ReadChar();
		//LCDDispChar(number[i]); //write received to lcd
	}
	
	char previous;
	while ((received = ReadChar()) != 0)
	{
		if (previous == 'O' && received == 'K')
		{
			ReadChar();
			ReadChar();
			break;
		}
		else
		{
			previous = received;
		}
	}
	
	ReplySMS(number);
}

void ReplySMS(char* number) {
	//+CMGR: "REC UNREAD","+4522954785",,"17/03/01,14:38:36+04"
	char received = 0;
	
	LCDDispString(number);

	SendString("AT+CMGS=");
	SendString(number);
	SendChar(0x0D);
	while ((received = ReadCharWithTimeout(10000)) != 0) {
		if (received != '\r' && received != '\n') {
			LCDDispChar(received);
		}
	}
	LCDDispChar('P');
	SendString("Hello!");
	SendChar(0x1A);
}


void DeleteSMS(int index) {
	
	SendString("AT+CMGD=");
	SendInteger(index);
	SendString("\r");
	LCDDispChar('D');
}