#include <delay.h>
#include <math.h>
#include <mega32a.h>
#include <stdio.h>


int i;

void main(void) {

  DDRA = 0xFF;

  while (1) {
    for (i = 1; i < 9; i++) {
      PORTA = pow(2, i) - 1;
      delay_ms(200);
      PORTA = 0;
      delay_ms(200);
    }
  }
}
