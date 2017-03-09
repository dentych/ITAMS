/*
 * localMemoryHandler.h
 *
 * Created: 09-03-2017 13:25:12
 *  Author: dty
 */ 


#ifndef LOCALMEMORYHANDLER_H_
#define LOCALMEMORYHANDLER_H_

#include "phonenumber.h"

signed char FindNumber(phonenumber *numbers, char *number, char phoneNumberCount);
int RemoveNumberFromLocalMemory(phonenumber *numbers, char *number, char *phoneNumberCounter);
int SaveNumberInLocalMemory(phonenumber *numbers, char *number, char *phoneNumberCounter);

#endif /* LOCALMEMORYHANDLER_H_ */