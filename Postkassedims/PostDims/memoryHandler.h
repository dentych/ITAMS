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
void SetupMemory();
void SaveNumber(uint8_t *number);
void ReadNumber(void* address, uint8_t *receivedNum);
//------------------------------------------------




#endif /* SMSHANDLER_H_ */