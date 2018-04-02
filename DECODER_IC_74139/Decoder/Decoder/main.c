/*
 * Decoder.c
 *
 * Created: 2018-04-02 오후 12:01:31
 * Author : Dovi
 */ 

/*
 * 74139
 *	PF0 : A0
 *	PF1 : A1
 *	PF2 : 74139's /G (Enable) ->
 *
 * 74373
 *	PORTA : D0 ~ D7
 *	/OE (PIN1) - GND
 *	LE (PIN11) - 74139's Y0 (PIN4)
 */

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

void out(char addr, char data);

int main(void)
{
	int i, j;
    DDRA = 0xff;	// 74373 D0 ~ D7
	DDRF = 0xff;	// 74139
	
	while (1) 
    {
		for(i = 0 ; i < 10 ; i++)
		{
			for(j = 0 ; j < 10 ; j++)
			{
				out(0x01, (i << 4) | j);
				out(0x00, (i << 4) | j);
				_delay_ms(300);	
			}
		}
		
    }
}

void out(char addr, char data)
{
	PORTF = addr;
	PORTA = data;
	PORTF &= 0xff;
	PORTF &= 0xfb;
}