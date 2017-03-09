/*
* localMemoryHandler.c
*
* Created: 09-03-2017 13:25:01
*  Author: dty
*/

#include <stdio.h>
#include <string.h>
#include "localMemoryHandler.h"

signed char FindNumber(phonenumber *numbers, char *number, char phoneNumberCount) {
	char index = -1;
	for (char i = 0; i < phoneNumberCount; i++) {
		if (strcmp(number, numbers[i].number) == 0) {
			index = i;
			break;
		}
	}

	return index;
}

int RemoveNumberFromLocalMemory(phonenumber *numbers, char *number, char *phoneNumberCounter) {
	char index = FindNumber(numbers, number, phoneNumberCounter);
	
	if (index < 0) {
		return 1;
	}

	for (int i = 0; i < 9; i++) {
		numbers[index].number[i] = numbers[(*phoneNumberCounter)-1].number[i];
	}
	(*phoneNumberCounter)--;

	return 0;
}

int SaveNumberInLocalMemory(phonenumber *numbers, char *number, char *phoneNumberCounter) {
	for (int i = 0; i < 9; i++) {
		numbers[(*phoneNumberCounter)].number[i] = number[i];
	}
	(*phoneNumberCounter)++;
}