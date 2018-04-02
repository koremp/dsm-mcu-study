/*
 * 0312_KEYPAD.c
 *
 * Created: 2018-03-12 오전 10:53:57
 * Author : dsm2016
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

unsigned char fnd[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f};
unsigned char led[9] = {0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff};

unsigned char key_value;

void data_write(unsigned char port, unsigned char data)
{
	/* WR Tick -> Data */
	DDRE = 0xff;
	PORTC = (port | 0x08);
	PORTE = data;	/* Data Set */
	PORTC = (PORTC | 0x04);
}

unsigned char data_read(unsigned char port)
{
	unsigned char in;
	DDRE = 0x00;
	PORTC = (port | 0x04);
	PORTC = (PORTC | 0x08);
	in = PINE;
	return (in);
}

unsigned char key(void)
{
	unsigned char a;
	unsigned char row = 0xef;
	unsigned char key_buf;
	
	for(a = 0 ; a < 4 ; a++)
	{
		data_write(0x02, row);
		_delay_us(20);
		key_buf = data_read(0x02);
		
		switch(key_buf)
		{
			case 0xd7 : key_buf = 0x00;	break;
			case 0xee : key_buf = 0x01;	break;
			case 0xde : key_buf = 0x02;	break;
			case 0xbe :	key_buf = 0x03;	break;
			case 0xed : key_buf = 0x04; break;
			case 0xdd : key_buf = 0x05; break;
			case 0xbd :	key_buf = 0x06; break;
			case 0xeb : key_buf = 0x07; break;
			case 0xdb : key_buf = 0x08; break;
			case 0xbb : key_buf = 0x09;	break;
			default : 	key_buf = 0x0f;
		}
		
		if(key_buf != 0x0f)
			return (key_buf);
		
		row = (row << 1) | 0x01;
	}	
	
	return (key_buf);
}

void key_scan(void)
{
	key_value = key();
	
	if(key_value != 0x0f)
	{
		while(key() != 0x0f);
	}
}

int main(void)
{
	int i;
	
	DDRC = 0xff;
		
	PORTC = 0x0c;
	_delay_us(50);
	PORTC |= 0x80;
	PORTC &= 0x7f;	//9255 Reset
	
	//PORTC = 0b00001111;
	//PORTC = 0x0b;
	//PORTE = 0x80;
	//PORTC = 0x0f;
	
	data_write(0x03, 0x81);

	while(1)
	{		
		key_scan();
		
		if(key_value != 0x0f)
		{
			data_write(0x00, 0x01);
			data_write(0x00, key_value);
			data_write(0x01, fnd[key_value]);
		}
	}	
}
	
