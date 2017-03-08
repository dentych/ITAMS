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

int main(void)
{
	SetupMemory();
	
	DDRA = 0x00;
	
	SaveNumber("11111111");
	SaveNumber("11111111");
	SaveNumber("11111111");
	SaveNumber("11111111");
	SaveNumber("11111111");
	SaveNumber("22954785");
	SaveNumber("11111111");
	SaveNumber("11111111");
	SaveNumber("11111111");
	SaveNumber("41408359");
	
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
			ReadNumber(6, number);
			_NOP();
		}
		else if ((PINA & (1<<3)) == 0) {
			DeleteNumber("22954785");
		}
		else if ((PINA & (1<<4)) == 0) {
			uint8_t number[8];
			ReadNumber(2, number);
			_NOP();
		}
	}
	
	while (1);
}