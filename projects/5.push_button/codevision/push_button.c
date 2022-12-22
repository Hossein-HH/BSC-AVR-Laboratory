#include <alcd.h>
#include <delay.h>
#include <mega32a.h>
#include <stdio.h>

//  #asm
// .equ __lcd_port = 0x1b; // PORTA
//  .equ __lcd_port = 0x18; // PORTB
// .equ __lcd_port = 0x15; // PORTC
// .equ __lcd_port = 0x12; // PORTD
// #endasm

unsigned char seg[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66,
                         0x6d, 0x7d, 0x07, 0x7f, 0x6f};

//! char *decToBinary(int n) {
//   int binaryNum[8];
//   int binaryResult = 0;
//   char *result;

//   int i = 0;
//   int j = 0;
//   int digitCounter = 0;

//   while (n > 0) {
//     binaryNum[i] = n % 2;
//     n = n / 2;
//     i++;
//   }

//   for (j = i - 1; j >= 0; j--)
//     binaryResult = (binaryResult * 10) + binaryNum[j];
//   //   printf("%d", binaryNum[j]);

//   while (binaryResult != 0) {
//     result[7 - digitCounter] = char(binaryResult % 10);
//     binaryResult /= 10;
//     digitCounter++;
//   }

//   while (digitCounter < 8)
//     result[digitCounter++] = '0';

//   return result;
//! }

int decToBinary(int n) {
  int binaryNum[8];
  int binaryResult = 0;

  int x = 0;
  int j = 0;
  //   int digitCounter = 0;

  while (n > 0) {
    binaryNum[x] = n % 2;
    n = n / 2;
    x++;
  }

  for (j = x - 1; j >= 0; j--)
    binaryResult = (binaryResult * 10) + binaryNum[j];
  //   printf("%d", binaryNum[j]);

  return binaryResult;
}

void main(void) {

  int i = 0;
  int j = 0;

  int temp1 = 0;
  int temp2 = 0;

  char decimalNum[16];
  char binaryNum[16];
  int binRes;
  //!   char *binRes;

  PORTA = 0x00;
  DDRA = 0xFF;

  PORTB = 0x00;
  DDRB = 0xFF;

  PORTC = 0x00;
  DDRC = 0x00;

  PORTD = 0x00;
  DDRD = 0xFF;

  lcd_init(16);

  while (1) {

    for (j = 0; j < 50; j++) {
      if (PINC .7 == 1) {
        PORTA = 2;
        PORTD = 0xFF - seg[temp1];
        delay_ms(5);

        PORTA = 1;
        PORTD = 0xFF - seg[temp2];
        delay_ms(5);
      } else {
        PORTA = 0;
      }

      if (PINC .0 == 0 || PINC .1 == 0) {

        if (PINC .0 == 0 && i != 99)
          i++;
        else if (PINC .1 == 0 && i != 0)
          i--;

        lcd_clear();
        lcd_gotoxy(4, 0);

        (i > 9) ? sprintf(decimalNum, "DEC : %d", i)
                : sprintf(decimalNum, "DEC : 0%d", i);

        lcd_puts(decimalNum);
        // lcd_putsf("string");

        lcd_gotoxy(1, 1);
        binRes = decToBinary(i);

        sprintf(binaryNum, "BIN : %d", binRes);

        //! sprintf(binaryNum, "BIN : %d%d%d%d%d%d%d%d", binRes[0], binRes[1],
        //         binRes[2], binRes[3], binRes[4], binRes[5], binRes[6],
        //         binRes[7]);
        lcd_puts(binaryNum);
        delay_ms(50);

        temp1 = i % 10;
        temp2 = i / 10;

        for (j = 0; j < 50; j++) {
          PORTA = 2;
          PORTD = 0xFF - seg[temp1];
          delay_ms(5);

          PORTA = 1;
          PORTD = 0xFF - seg[temp2];
          delay_ms(5);
        }
        if (PINC .7 == 0) {
          PORTA = 0;
          PORTD = i;
          delay_ms(100);
        }
      };
    }
  }
}