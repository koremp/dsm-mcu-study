/*
 * LED_FND__0305.c
 *
 * Created: 2018-03-05 오후 12:15:52
 * Author : dsm2016
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

unsigned char fnd[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f};
unsigned char led[9] = {0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff};

void data_write(unsigned char port, unsigned char data)
{
	/* WR Tick -> Data */
	PORTC = (port | 0x08);
	PORTE = data;	/* Data Set */
	PORTC = (PORTC | 0x04);
}

int main(void)
{
	int i;
	
	DDRC = 0xff;
	DDRE = 0xff;
	
	/* Reset Tick */
	PORTC |= 0x80;
	PORTC &= 0x7f;	
	
	PORTC = 0b00001111;
	PORTC = 0x0b;
	PORTE = 0x80;
	PORTC = 0x0f;
	
	while (1)
    {	
		
		data_write(0x00, 0xff);
		/*
		for(i = 0 ; i <= 8 ; i++)
		{
			PORTC = 0x08;
			PORTE = led[i];
			PORTC = (PORTC | 0x04);
			
			PORTC = 0x09;
			PORTE = fnd[i];
			PORTC = (PORTC | 0x04);
			_delay_ms(500);
		}
		*/
    }
}