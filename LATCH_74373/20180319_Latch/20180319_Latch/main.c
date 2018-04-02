/*
 * 20180319_Latch.c
 *
 * Created: 2018-03-19 오후 12:10:13
 * Author : dsm2016
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

unsigned char fnd[10] = {0x3f, 0b00001010, 0b01010111, 0x4f, 0b01101010, 0x6d, 0x7d, 0b00101011, 0x7f, 0x6f}; //1,2,4,7

int main(void)
{
    int i, j;
	
	DDRA = 0xff;
	DDRF = 0xff;
	
	while (1) 
    {
		PORTF = 0x01;
		
		for(i = 0 ; i < 10 ; i++)
		{
			for(j = 0 ; j < 10 ; j++)
			{
				PORTA = (j << 4) | i;
				_delay_ms(500);
			}
		}
    }
}

