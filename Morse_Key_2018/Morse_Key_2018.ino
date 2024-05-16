//Morse Key With Display

#define DOT 2
#define DASH 3
#define BUZZ 5

#include "TM1637.h"
#define CLK 8
#define DIO 9
#define BUZZ 5
#define DOT 3
#define DASH 2

TM1637 disp(CLK, DIO);

int Disp;
int b;
int f;
int a;

void setup() {
  pinMode(3, INPUT);
  pinMode(2, INPUT);
  digitalWrite( 3 , HIGH );
  digitalWrite( 2 , HIGH );

  disp.set(5);
  disp.init(D4056A);


}
void loop() {

  int A = analogRead(A5);
  Disp = map(A, 0, 1023, 200, 30);
  disp.display(Disp);
  a = map(A, 0, 1023, 18, 60);


  int B = analogRead(A3);
  b = map(B, 0, 1023, 3, 3.9);

  int F = analogRead(A1);
  f = map(F, 0, 1023, 1200, 600);


  if (digitalRead(DOT) == 0) {
    tone (BUZZ, f);
    delay(a);
    noTone(BUZZ);
    delay(a);
  }
  if (digitalRead(DASH) == 0) {
    tone (BUZZ, f);
    delay(a * b);
    noTone(BUZZ);
    delay(a);
  }
}

