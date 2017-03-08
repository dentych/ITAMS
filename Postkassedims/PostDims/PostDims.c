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
#include "uart.h"
#include "lcd162.h"
#include "smsHandler.h"
#include "memoryHandler.h"
#include "avr/eeprom.h"


int main(void)
{
	SetupMemory();
	
	DDRA = 0x00;
	
	uint8_t helo = PINA;
	
	while (1) {
		if ((PINA & 0b00000001) == 0) {
			uint8_t *number = "22954785";
			SaveNumber(number);
		}
		else if ((PINA & (1<<1)) == 0) {
			uint8_t *number = "41408359";
			SaveNumber(number);
		}
		else if ((PINA & (1<<2)) == 0) {
			uint8_t number[8];
			ReadNumber(2, number);
		}
	}
	
	while (1);
}