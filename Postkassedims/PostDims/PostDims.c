/*
* PostDims.c
*
* Created: 16-Feb-17 15:00:24
*  Author: Andreas
*/


#include <avr/io.h>
#define F_CPU 3868400
#include <util/delay.h>
#include "uart.h"
#include "lcd162.h"
#include "smsHandler.h"

int main(void)
{
	const long baud = 9600;
	const unsigned char dbit = 8;
	
	InitUART(baud, dbit);
	LCDInit();
	LCDClear();
	
	DDRA = 0x00;
	
	
	//SendString("ATE0\r"); // fjerner echo
	//SendString("AT+CGMI\r"); //AT+CGMI - Hvem er manufacturer?
	
	unsigned char receivedData = 0;
	
	int newlines = 0;
	int flag = 0;
	int bla = 0;
	
	while (1) {
		if ((PINA & 0b00000001) == 0) {
			if (!bla) {
				DeleteSMS(1);
				bla = 1;
			}
		} else {
			bla = 0;
		}
		if (CharReady()) {
			receivedData = ReadChar();
			//if (receivedData != '\r' && receivedData != '\n' && newlines >4) {
				//LCDDispChar(receivedData);
			//} else {
				//newlines++;
				//if(newlines > 8 && flag == 0) {
					//LCDGotoXY(0,1);
					//flag = 1;
				//}
			//}
			
			if(receivedData == '+')
			{
				ReadSMS();
			}
		}
	}
	
	LCDDispChar('U');
	while (1);
}