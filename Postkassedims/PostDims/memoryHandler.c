/*
 * memoryHandler.c
 *
 * Created: 06-03-2017 11:01:06
 *  Author: aen
 */ 
#include "memoryHandler.h"

#define write_eeprom_byte(address,value) eeprom_write_byte ((uint8_t*)address,(uint8_t)value)
#define write_eeprom_array(address,value_p,length) eeprom_write_block ((const void *)value_p, (void *)address, length)
#define read_eeprom_byte(address) eeprom_read_byte ((const uint8_t*)address)
#define read_eeprom_array(address,value_p,length) eeprom_read_block ((void *)value_p, (const void *)address, length)

void SetupMemory() {
	if(read_eeprom_byte(1) == 0xFF) {
		uint8_t count = 0;
		write_eeprom_byte(1, count);
	}
}

void SaveNumber(uint8_t *number) {
	uint8_t count = ReadAmountOfNumbersSaved();
	
	write_eeprom_array(2+(count*8), number, 8);
	
	write_eeprom_byte(1, count+1);
}

void ReadNumber(void* address, uint8_t *receivedNum) {
	uint8_t count = ReadAmountOfNumbersSaved();
	read_eeprom_array(address, receivedNum, 8);
}

uint8_t ReadAmountOfNumbersSaved() {
	return read_eeprom_byte(1);
}