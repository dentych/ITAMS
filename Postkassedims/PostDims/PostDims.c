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
#include "memoryHandler.h"
#include "avr/eeprom.h"


int main(void)
{
	
	const long baud = 9600;
	const unsigned char dbit = 8;
	
	InitUART(baud, dbit);
	LCDInit();
	LCDClear();
	
	SetupMemory();
	
	DDRA = 0x00;

	uint8_t SRAMstring[8] = "22954785";
	uint8_t SRAMstring2[8] = "88888888";
	uint8_t StoredString[8];
	LCDDispChar('A');

	


	//eeprom_read_block((void*)&StoredString, (const void*)&NonVolatileString, 8);
	//LCDDispString(StoredString);
	
	//ReadMemory(StoredString, &NonVolatileString, 8);

	//LCDDispString(StoredString);
	
	
	LCDDispChar('D');
	
	
	InitSMS('0', '1', "3257");

	//ReplySMS("22954785");
	
	unsigned char receivedData = 0;
	
	int newlines = 0;
	int flag = 0;
	int bla = 0;
	int bla2 = 0;
	int bla3 = 0;
	
	while (1) {
		if ((PINA & 0b00000001) == 0) {
			if (!bla) {
				SaveNumber("22954785");
				//WriteMemory("22954785", NonVolatileString, 8);
				//DeleteAll(50);
				bla = 1;
			}
		} else {
			bla = 0;
		}
		
		if ((PINA & 0b00000010) == 0) {
			if (!bla2) {
			SaveNumber("88888888");
			//WriteMemory(SRAMstring2, NonVolatileString, 8);
			bla2 = 1;
			}
		}else {
			bla2 = 0;
		}
		if ((PINA & 0b00000100) == 0) {
			if (!bla3) {
			ReadNumber(2);
			//WriteMemory(SRAMstring2, NonVolatileString, 8);
			bla3 = 1;
			} else {
			bla3 = 0;
		}	
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