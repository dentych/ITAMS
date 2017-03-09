/*
 * memoryHandler.h
 *
 * Created: 06-03-2017 11:01:24
 *  Author: aen
 */ 
#ifndef MEMORYHANDLER_H_
#define MEMORYHANDLER_H_

#include "phonenumber.h"

//  Public:
void SetupMemory();
void SaveNumber(uint8_t *number);
void ReadNumber(uint8_t count, uint8_t *receivedNum);
void DeleteNumber(uint8_t *numberToDelete);
void LoadAllNumbersFromEEPROM(phonenumber *numbers, char *phoneNumberCounter);
//------------------------------------------------

#endif /* SMSHANDLER_H_ */