/*
* memoryHandler.c
*
* Created: 06-03-2017 11:01:06
*  Author: aen
*/
#include <avr/eeprom.h>
#include "memoryHandler.h"
#include "localMemoryHandler.h"

#define write_eeprom_byte(address,value) eeprom_write_byte((uint8_t*)address,(uint8_t)value)
#define write_eeprom_array(address,value_p,length) eeprom_write_block((const void *) value_p, (void *) address, length)
#define read_eeprom_byte(address) eeprom_read_byte((const uint8_t*)address)
#define read_eeprom_array(address,value_p,length) eeprom_read_block((void *) value_p, (const void *) address, length)
#define update_eeprom_array(address,value_p,length) eeprom_update_block((const void *) value_p, (void *) address, length)

uint8_t ReadAmountOfNumbersSaved();
uint8_t CalculateNextAddress(uint8_t index);
uint8_t CalculateAddress(uint8_t index);
int compareArrays(uint8_t *array1, uint8_t *array2, int n);
void DeleteAndMove(uint8_t indexNumberToDelete, uint8_t amountOfNumbers);

void SetupMemory() {
	uint8_t count = ReadAmountOfNumbersSaved();
	
	if(count == 0xFF) {
		count = 0;
		write_eeprom_byte(1, count);
	}
}

void SaveNumber(uint8_t *number) {
	uint8_t count = ReadAmountOfNumbersSaved();
	uint8_t address = CalculateNextAddress(count);
	write_eeprom_array(address, number, 8);
	
	write_eeprom_byte(1, count+1);
}

void ReadNumber(uint8_t count, uint8_t *receivedNum) {
	uint8_t address = CalculateAddress(count);
	read_eeprom_array(address, receivedNum, 8);
	receivedNum[8] = 0;
}

void DeleteNumber(uint8_t *numberToDelete) {
	uint8_t count = ReadAmountOfNumbersSaved();
	
	if (count < 1) {
		return;
	}
	
	for (uint8_t i = 1; i <= count; i++) {
		uint8_t number[8];
		ReadNumber(i, number);
		if (compareArrays(number, numberToDelete, 8)) {
			DeleteAndMove(i, count);
			write_eeprom_byte(1, count-1);
			break;
		}
	}
}

uint8_t ReadAmountOfNumbersSaved() {
	return read_eeprom_byte(1);
}

uint8_t CalculateNextAddress(uint8_t index) {
	return (2+(index*8));
}

uint8_t CalculateAddress(uint8_t index) {
	return (2+((index-1)*8));
}

int compareArrays(uint8_t *array1, uint8_t *array2, int n) {
	for (int i = 0; i < n; i++) {
		if (array1[i] != array2[i]) {
			return 0;
		}
	}
	return 1;
}

void DeleteAndMove(uint8_t indexNumberToDelete, uint8_t amountOfNumbers) {
	uint8_t number[8];
	uint8_t addressOfLastNumber = CalculateAddress(amountOfNumbers);
	uint8_t addressOfNumberToDelete = CalculateAddress(indexNumberToDelete);
	read_eeprom_array(addressOfLastNumber, number, 8);
	update_eeprom_array(addressOfNumberToDelete, number, 8);
	uint8_t array[8] = {0xFF};
	update_eeprom_array(addressOfLastNumber, array, 8);
}

void LoadAllNumbersFromEEPROM(phonenumber *numbers, char *phoneNumberCounter) {
	char numbersSaved = ReadAmountOfNumbersSaved();
	
	for (int i = 1; (i <= numbersSaved) && (i <= 10); i++) {
		char number[9];
		ReadNumber(i, number);
		number[8] = 0;
		SaveNumberInLocalMemory(numbers, number, phoneNumberCounter);
	}
}