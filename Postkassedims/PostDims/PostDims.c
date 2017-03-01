/*
* PostDims.c
*
* Created: 16-Feb-17 15:00:24
*  Author: Andreas
*/


#include <avr/io.h>
#include "uart.h"
#include "lcd162.h"

int main(void)
{
	const long baud = 9600;
	const unsigned char dbit = 8;
	
	InitUART(baud, dbit);
	LCDInit();
	LCDClear();
	
	SendString("ATE0\r"); // fjerner echo
	SendString("AT+CGMI\r"); //AT+CGMI - Hvem er manufacturer?
	
	unsigned char receivedData = 0;
	
	while ((receivedData = ReadChar()) > 0) {
		if (receivedData != '\r' && receivedData != '\n') {
			LCDDispChar(receivedData);
		} else if(receivedData == 13) {
			LCDGotoXY(0,1);
		}
	}
	
	while (1);
}