/*
 * ADC.c
 *
 * Created: 03-03-2017 11:58:27
 *  Author: dty
 */ 

#define F_CPU 3868400
#include <avr/io.h>
#include <util/delay.h>

void InitADC() {
	ADMUX = 0b01000000;
	ADMUX |= (1<<ADLAR);
	
	// Enable ADC and set prescaler to 32.
	ADCSRA = 0b10000101;
}

int16_t ReadADC() {
	ADCSRA |= (1<<ADSC);
	
	PORTB &= ~(1<<6);
	WaitForConversionFinish();
	PORTB |= (1<<6);
	
	return ADCH;
}

void WaitForConversionFinish() {
	while ((ADCSRA & (1<<ADSC)) != 0)
	{
	}
}

void TestADC() {
	DDRB = 0xFF;
	DDRD = 0xFF;
	PORTD = 0xFF;
	PORTB = 0xFF;

	InitADC();

	while (1)
	{
		PORTB &= ~(0b00000001);
		int16_t data = ReadADC();
		_delay_ms(50);
		PORTB |= 0b00000001;
		if (data > 128) {
			PORTB &= ~(1<<7);
		} else {
			PORTB |= (1<<7);
		}
		_delay_ms(100);
	}
}
