/*
* ADC.c
*
* Created: 03-03-2017 11:58:27
*  Author: dty
*/

#define F_CPU 3868400
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void InitADC() {
	DDRB = 0xFF;
	DDRD = 0xFF;
	PORTD = 0x00;
	PORTB = 0xFF;
		
	ADMUX |= (1<<REFS0); // Sætter ADC'ens spændingsreference til AVCC med extern capacitor på pin AREF.
	ADMUX |= (1<<ADLAR); // Gør så register ADCH bruges
	ADCSRA |= (1<<ADEN); // Aktiverer ADC'en
	ADCSRA |= (1<<ADPS2); // Sætter prescaler til 32
	ADCSRA |= (1<<ADPS0); // Sætter prescaler til 32
	
	sei(); //Aktiver globale interrupts
	ADCSRA |=1<<ADIE; //ADC interrupt aktiveres
	ADCSRA |= 1<<ADSC; // Start ADC konvertering
	
	while (1) {}
}

ISR(ADC_vect) {
	PORTB &= ~(0b00000001);
	int16_t data = ADCH;
	_delay_ms(50);
	PORTB |= 0b00000001;
	if (data > 30) {
		PORTB &= ~(1<<7);
	} else {
		PORTB |= (1<<7);
	}
	_delay_ms(100);
	
	// Insert reaction to interrupt from sensor.
	
	ADCSRA |= (1<<ADSC);
}
