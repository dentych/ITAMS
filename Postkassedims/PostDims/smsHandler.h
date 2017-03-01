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
//------------------------------------------------




#endif /* SMSHANDLER_H_ */