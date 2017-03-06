/*
 * memoryHandler.h
 *
 * Created: 06-03-2017 11:01:24
 *  Author: aen
 */ 
#include <avr/io.h>
#include <stddef.h>
#include <avr/eeprom.h>

#ifndef MEMORYHANDLER_H_
#define MEMORYHANDLER_H_

//  Public:
void WriteMemory(uint8_t *str, void* address, size_t length);
void ReadMemory(uint8_t *storedString, void* address, size_t length);
void SetupMemory();
void SaveNumber(uint8_t *number);
//------------------------------------------------




#endif /* SMSHANDLER_H_ */