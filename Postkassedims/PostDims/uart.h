/**************************************
* "uart.h":                           *
* Header file for Mega32 UART driver. *
* Henning Hargaard, 1/11 2011         *
***************************************/ 

#ifndef UART_H_
#define UART_H_

void InitUART(unsigned long BaudRate, unsigned char DataBit);
unsigned char CharReady();
char ReadChar();
char ReadCharWithTimeout(int timeout);
void SendChar(char Ch);
void SendString(char* String);
void SendInteger(int Number);
void UART_Flush();
/**************************************/

#endif /* UART_H_ */