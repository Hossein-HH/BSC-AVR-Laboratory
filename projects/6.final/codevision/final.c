#include <alcd.h>
#include <delay.h>
#include <math.h>
#include <mega32a.h>
#include <stdio.h>

unsigned char seg[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66,
                         0x6d, 0x7d, 0x07, 0x7f, 0x6f};

void main(void) {

  int position = 7;
  int segNumber = 10;
  int ledNumber = 8;
  int i = 0;

  int seg1 = 0;
  int seg2 = 1;

  PORTA = 0x00;
  DDRA = 0xFF;

  PORTB = 0x00;
  DDRB = 0xFF;

  PORTC = 0x00;
  DDRC = 0x0F;

  PORTD = 0x00;
  DDRD = 0xFF;

  lcd_init(16);

  lcd_clear();
  lcd_gotoxy(position, 0);
  lcd_putsf("H");
  delay_ms(50);

  PORTA = ledNumber;
  delay_ms(5);

  while (1) {
    PINC .0 = 0;
    PINC .0 = 1;
    PORTB = seg[seg1];
    delay_ms(5);

    PINC .1 = 0;
    PINC .1 = 1;
    PORTB = seg[seg2];
    delay_ms(5);

    if (PINC .6 == 0 || PINC .7 == 0) {
      if (PINC .6 == 0) {
        if (position < 15) {
          position++;
          segNumber++;
        }

        if (ledNumber != 1) {
          ledNumber = ledNumber / 2;
        }
      } else if (PINC .7 == 0) {
        if (position > 0) {
          position--;
          segNumber--;
        }

        if (ledNumber != 64) {
          ledNumber = ledNumber * 2;
        }
      }

      // 1 2 4 8 16
      // 0 1 2 3 4

      lcd_clear();
      lcd_gotoxy(position, 0);
      lcd_putsf("H");
      delay_ms(50);

      seg1 = segNumber % 10;
      seg2 = segNumber / 10;

      for (i = 0; i < 25; i++) {
        PINC .0 = 0;
        PINC .0 = 1;
        PORTB = seg[seg1];
        delay_ms(5);

        PINC .1 = 0;
        PINC .1 = 1;
        PORTB = seg[seg2];
        delay_ms(5);
      }

      PORTA = ledNumber;
      delay_ms(5);
    }
  }
}