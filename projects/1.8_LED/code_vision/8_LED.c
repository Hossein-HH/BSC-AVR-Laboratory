#include <mega32a.h>
#include <stdio.h>
#include <delay.h>
#include <math.h>

int i = 0;

void main(void)
{
DDRA = 0xFF;

    while (1)
    {             
        for (i = 0;i < 4;i++) {

            PORTA = pow(2,i) + pow(2,7-i);     
            delay_ms(100);
            PORTA = 0x00;
            delay_ms(100);  
        
        };
 
    }
}
 