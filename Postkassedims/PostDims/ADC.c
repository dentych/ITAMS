/*
* ADC.c
*
* Created: 03-03-2017 11:58:27
*  Author: dty
*/

#define F_CPU 3686400
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void InitADC() {
	ADMUX |= (1<<REFS0); // Sætter ADC'ens spændingsreference til AVCC med extern capacitor på pin AREF.
	ADMUX |= (1<<ADLAR); // Left shifter bits
	ADCSRA |= (1<<ADEN); // Aktiverer ADC'en
	ADCSRA |= (1<<ADPS2); // Sætter prescaler til 32
	ADCSRA |= (1<<ADPS0); // Sætter prescaler til 32
	
	sei(); //Aktiver globale interrupts
	ADCSRA |=1<<ADIE; //ADC interrupt aktiveres
	
	StartADC();
}

void StartADC() {
	ADCSRA |= 1<<ADSC;
}
