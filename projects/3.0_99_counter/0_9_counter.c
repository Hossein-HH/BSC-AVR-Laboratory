#include <delay.h>
#include <mega32a.h>
#include <stdio.h>

void main() {

  int seg[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

  int i = 0;
  DDRA = 0xFF;
  PORTA = 0x00;

  while (1) {
    for (i = 0; i <= 9; i++) {

      PORTA = seg[i];

      delay_ms(500);
    };
  };
}