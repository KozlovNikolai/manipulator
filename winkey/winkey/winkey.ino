#include <StackList.h>

#include <Keyboard.h>

#define BUTTON_DOT 2
#define BUTTON_TIRE 3
#define OUTPORT 4
unsigned char inp[8];
unsigned int key, keyflag, index;
unsigned int cwspeed = 200;
unsigned char State = "";
unsigned long int myTIME = 300;
unsigned long int t;

void setup() {
  Serial.begin(9600);
   Keyboard.begin();
  pinMode(BUTTON_DOT, INPUT_PULLUP);
  pinMode(BUTTON_TIRE, INPUT_PULLUP);
  pinMode(A1, INPUT);
  pinMode(OUTPORT, OUTPUT); 
}
void doActionDot () {
  Keyboard.print(".");  
}
void doActionTire () {
  Keyboard.print("-");
}


void speedset(){
 if (key>925 && key<930){if (!keyflag){keyflag=1;cwspeed=cwspeed-1;if (cwspeed==0){cwspeed=cwspeed+1;};};}
 if (key>985 && key<995){if (!keyflag){keyflag=1;cwspeed=cwspeed+1;if (cwspeed==1023){cwspeed=cwspeed-1;};};}
}

void loop() {
key=analogRead(A1);
if (key>4) {speedset();} else {keyflag=0;}

if (!digitalRead(BUTTON_DOT)) {State="*";}
if (!digitalRead(BUTTON_TIRE)) {State="-";}



}
