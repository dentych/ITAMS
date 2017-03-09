/*
* smsHandler.h
*
* Created: 01-03-2017 11:12:05
*  Author: aen
*/


#ifndef SMSHANDLER_H_
#define SMSHANDLER_H_

#include "phonenumber.h"

//  Public:
enum SMSType {
	SUBSCRIBED,
	ALREADY_SUBSCRIBED,
	UNSUBSCRIBED,
	NOT_SUBSCRIBED,
	UNKNOWN_COMMAND,
	NEW_MAIL,
	HELP,
	STATUS,
	NUMBERS_FULL
};
typedef enum SMSType SMSType;

void SendSMS(char *number, SMSType type, char mailCounter);
void ReadSMS(char index, char *header, char *body);
void DeleteSMS(int index);
void DeleteAll(int spaces);
void WaitforResponse();
void WritePin(char* pin);
void SetEcho(char echo);
void SetTextMode(char mode);
void InitSMS(char echo, char mode, char* pin);
void ExtractNumber(char *header, char *number);
void SendSMSToAll(phonenumber *numbers, char phoneNumberCount);
//------------------------------------------------

#endif /* SMSHANDLER_H_ */