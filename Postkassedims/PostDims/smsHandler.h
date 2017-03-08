/*
* smsHandler.h
*
* Created: 01-03-2017 11:12:05
*  Author: aen
*/


#ifndef SMSHANDLER_H_
#define SMSHANDLER_H_

//  Public:
enum SMSType {
	SUBSCRIBED,
	UNSUBSCRIBED,
	UNKNOWN_COMMAND,
	NEW_MAIL
};
typedef enum SMSType SMSType;

void SendSMS(char *number, SMSType type);
void ReadSMS(char index, char *header, char *body);
void ReplySMS(char* number, char *body, char bodySize);
void DeleteSMS(int index);
void DeleteAll(int spaces);
void WaitforResponse();
void WritePin(char* pin);
void SetEcho(char echo);
void SetTextMode(char mode);
void InitSMS(char echo, char mode, char* pin);
void ExtractNumber(char *header, char *number);
//------------------------------------------------

#endif /* SMSHANDLER_H_ */