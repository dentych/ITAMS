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
	
	if(read_eeprom_byte(1) == 0xff) {
	
		LCDDispChar('Y');
		uint8_t count = 0;
		write_eeprom_byte(1, count);
	}
	
	LCDDispInteger(read_eeprom_byte(1));
}

void SaveNumber(uint8_t *number) {
	
	LCDDispChar('W');
	
	uint8_t count = read_eeprom_byte(1); //get amount of telephone numbers
	
	LCDDispInteger(count);
	
	write_eeprom_array(2+(count*8), number, 8);
	
	write_eeprom_byte(1, count+1);
}

void ReadNumber(void* address) {
	LCDDispChar('C');
	
	uint8_t receivedNum;
	
	read_eeprom_array(address, receivedNum ,8);
	
	LCDDispString(receivedNum);
	LCDDispChar('E');
}



//void WriteMemory(uint8_t *str, size_t length) {
	//LCDDispChar('W');
	//write_eeprom_array(str, adress, length);
	////eeprom_write_block((const void*)str, (void*)&address, length);
//}
//
//void ReadMemory(uint8_t* storedString, void* address, size_t length) {
	//LCDDispChar('R');
	//read_eeprom_array(storedString, address, length);
	////eeprom_read_block((void*) storedString, (const void*)&address, length);
//}


