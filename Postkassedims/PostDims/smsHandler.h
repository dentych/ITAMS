/*
 * smsHandler.h
 *
 * Created: 01-03-2017 11:12:05
 *  Author: aen
 */ 


#ifndef SMSHANDLER_H_
#define SMSHANDLER_H_

//  Public:
void SendSMS(char *str);
void ReadSMS();
void ReplySMS(char* number);
void DeleteSMS(int index);
void DeleteAll(int spaces);
void WaitforResponse();
void WritePin(char* pin);
void SetEcho(char echo);
void SetTextMode(char mode);
void InitSMS(char echo, char mode, char* pin);
//------------------------------------------------

#endif /* SMSHANDLER_H_ */