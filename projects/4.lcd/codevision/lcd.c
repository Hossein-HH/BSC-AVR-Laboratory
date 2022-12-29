#include <alcd.h>
#include <delay.h>
#include <mega32a.h>
#include <stdio.h>

void main(void) {

  unsigned char i, j, tekrar;
  unsigned char cathode_seg[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66,
                                   0x6d, 0x7d, 0x07, 0x7f, 0x6f};

  char number[16];

  PORTA = 0x00;
  PORTB = 0x00;
  PORTC = 0x00;
  PORTD = 0x00;

  DDRA = 0xFF;
  DDRB = 0xFF;
  DDRC = 0xFF;
  DDRD = 0xFF;

  lcd_init(16);

  while (1) {
    for (i = 0; i <= 9; i++) {
      for (j = 0; j < 10; j++) {
        lcd_gotoxy(2, 0);
        sprintf(number, "Number = %d", (i * 10) + j);
        lcd_puts(number);
        delay_ms(10);

        PORTD = (i * 10) + j;
        delay_ms(10);

        for (tekrar = 0; tekrar < 25; tekrar++) {
          PORTC = 1;
          PORTA = cathode_seg[j];
          delay_ms(10);

          PORTC = 2;
          PORTA = cathode_seg[i];
          delay_ms(10);
        }
      }
    }
  }
}