#include <Keyboard.h>
#include "CyberLib.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(8);

#define BUTTON_DOT 6
#define BUTTON_TIRE 7
#define OUTPORT 4
#define BEEPER 5
#define CLK 10
#define DT 16
#define SW 14
#define VERSION "1.0"

// Таблица кодов Морзе. N-ный элемент кода соответствует n-ному символу раскладки.
char* code[] = {
  "*-","-***","*--","--*","-**","*","***-","--**","**","*---",
  "-*-","*-**","--","-*","---","*--*","*-*","***","-","**-",
  "**-*","****","-*-*","---*","----","--*-","-*--","-**-","**-**","**--",
  "*-*-",
  "*----","**---","***--","****-","*****","-****","--***","---**","----*","-----",
  "......","*-*-*-","---***","-*-*-*","-*--*-","*----*","*-**-*","-****-","-**-*","**--**","--**--",
  "-***-","********","*--*-*","**-*-","*-*-*-*-","-*-*-*-",
  "******","*******","*********","**********",
  ""
};
// Кириллическая раскладка.
  char* layoutCyrillic[] = {
  "F","<","D","U","L","T",":","P","B","Q",
  "R","K","V","Y","J","G","H","C","N","E",
  "A","{","W","X","I","O","S","M","\"",">",
  "Z",
  "1","2","3","4","5","6","7","8","9","0",
  ".","/",":",";","(","\'","\"","-","/","&","?",
  "=","gtht,jq","@"," *END* "," *back* "," *layout* ",
  "gtht,jq","gtht,jq","gtht,jq","gtht,jq",
  ""
  };
  
// Латинская раскладка.
char* layoutLatin[] = {
  "A","B","W","G","D","E","V","Z","I","J",
  "K","L","M","N","O","P","R","S","T","U",
  "F","H","C","ch","sh","Q","Y","X","**-**","**--",
  "ya",
  "1","2","3","4","5","6","7","8","9","0",
  ".",".",":",";","(","\'","\"","-","/","?",",",
  "=","pereboy","@"," *END* "," *back* "," *layout* ",
  "pereboy","pereboy","pereboy","pereboy",
  ""
};
char** CurrentLayout;
boolean DT_now, DT_last;
unsigned int key, keyflag, MorseSignal, DotMemory, TireMemory, pad, oldMorseSignal, blank, len;
unsigned int temp, index, probel, alfa, backspace;
unsigned int CPM=85;
unsigned int WPM=CPM/5;
unsigned long int cwspeed = 117600/WPM;
unsigned long int t, timer, joom, sound;
unsigned int FLAG =0;
char text[11];
boolean KB_On=0;
void setup(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setTextWrap(0);
  display.setCursor(0,0);
  PrintSpeed();
  CurrentLayout = layoutLatin;
 cwspeed=5880000/CPM;
 backspace=1;
 DotMemory=0;
  Keyboard.begin();
  Serial.begin(9600);
  D6_In; D6_High;
  D7_In; D7_High;
  pinMode(A1, INPUT);
  D4_Out; D4_Low;
  pinMode(BEEPER, OUTPUT);
  D5_Out; D5_Low;
  pinMode (CLK, INPUT);
  pinMode (DT, INPUT);
  DT_last = digitalRead(CLK);         // читаем начальное положение CLK
}
void PrintSpeed() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.print ("CPM=");
  display.print (CPM);
  display.setCursor(0,16);
  display.print ("WPM=");
  display.print (WPM);
  display.setCursor(0,32);
  if(KB_On){display.print ("WinKey-On");}else{display.print ("WinKey-Off");}
  display.setCursor(0,48);
  display.print ("Ver. = ");
  display.print (VERSION);
  display.display();
  
   /* Serial.print(", CPM = "); Serial.println(CPM);
    Serial.print(", WPM = "); Serial.println(WPM);
    Serial.print(", DOTtimer = "); Serial.println(cwspeed);*/
    
  }
//-------------------------------------------------------------------------------------------------------------
void flow(){
  if (MorseSignal==1) {text[index]='*';text[index+1]='\0';}
  if (MorseSignal==2) {text[index]='-';text[index+1]='\0';}
  index++;
}
//----------------------------------------------------------------------------------------------------------
void beepon(){
  analogWrite(BEEPER,20);
}
void beepoff(){
  analogWrite(BEEPER,0);
}
//------------------------------------------------------------------------------------------------------------
void printM() {
  int i, j;
  temp=1;
while(temp){
if (text[len]=='\0') {temp=0;}
len++;  
} 
  if (len < 1) {
    return;
  }
  for (i = 0; code[i][0] != '\0'; i++) {
    // Сравним введенный символ с символами из таблицы кодов Морзе.
    for (j = 0; (j < len) && (code[i][j] != '\0'); j++) {
                                                        if (code[i][j] != text[j]) {j = -1;break;}
                                                         }
    if ((j != -1) && ((j+1) == len) && (code[i][j]=='\0')) {
      // Символ из таблицы кодов Морзе соответствует введенному символу.
      //  Отправим символ на компьютер.
      alfa=1;
      if (CurrentLayout[i]=="pereboy") {alfa=0; if(KB_On){Keyboard.print("[ZP]");}}
      if (alfa) {if (KB_On){ Keyboard.print(CurrentLayout[i]); }}
      len = 0;
      return;
    }
  }
  // Символ в таблице не найден. Напечатаем нераспознанный символ.
 // Keyboard.print("*");
 if(KB_On){
  Keyboard.print(" [");
  for (i = 0; i < len; i++) {
    //Serial.print(text[i]);
    Keyboard.print(text[i]);
  }
  Keyboard.print("] ");
 }
  len = 0;
}
void encoderTick() {
  DT_now = digitalRead(CLK);          // читаем текущее положение CLK
  if (DT_now != DT_last && DT_now<1) {// если предыдущее и текущее положение CLK разные, значит был поворот
    if (digitalRead(DT) != DT_now) {  // если состояние DT отличается от CLK, значит крутим по часовой стрелке
      CPM --;                     // прибавить счётчик
    } else {                          // если совпадают, значит против часовой
      CPM ++;                     // убавить счётчик
    }
    WPM=CPM/5;
    cwspeed=5880000/CPM;
    PrintSpeed();
  }
  DT_last = DT_now;                   // обновить значение
  if(!digitalRead(SW)){KB_On=!KB_On;PrintSpeed();while(!digitalRead(SW)){}}
}
//----------------------------------------------------------------------------------------------------------------
void loop (){
 encoderTick();
//--------------------опрос манипулятора------------------------------------
if (!D6_Read && !D7_Read && MorseSignal==0) { //если нажата точка и тире и текущего сигнала нет, то
                                          if (oldMorseSignal==1){timer=cwspeed*3;beepon();D4_High;MorseSignal=2;oldMorseSignal=MorseSignal;flow();}//если последняя была точка, то включаем тире
                                                            else{timer=cwspeed*1;beepon();D4_High;MorseSignal=1;oldMorseSignal=MorseSignal;flow();};//если последнее было тире, включаем точку
                                                            t=micros();} //запоминаем время включения сигнала
if (oldMorseSignal==1){DotMemory=0;} //если раньше была точка, то память на точку не используем.
if ((!D6_Read or (DotMemory))  && MorseSignal==0){       //если сигнал отсутствует и нажата точка или есть точка в памяти, то
                              DotMemory=0; timer=cwspeed*1;beepon();D4_High;MorseSignal=1;oldMorseSignal=MorseSignal;t=micros();flow();} //передаем точку и запоминаем время начала передачи
if (!D7_Read && MorseSignal==0){                     //если сигнал отсутствует и нажато тире, то 
                              timer=cwspeed*3;beepon();D4_High;MorseSignal=2;oldMorseSignal=MorseSignal;t=micros();flow();} // передаем тире и запоминаем время начала передачи
if (MorseSignal==2 && !D6_Read){DotMemory=1;}; // если нажата точка и в этот момент передается тире, то запоминаем в памяти точку
//------------------------------------------------------
if (micros()-t>timer){ 
                   if(digitalRead(OUTPORT)){beepoff();D4_Low;joom=micros();}}
if ((micros()-t)>(timer+cwspeed)){MorseSignal=0;}
if (MorseSignal==2 && !D6_Read){DotMemory=1;};
if (MorseSignal){blank=1;}
if (((micros()-joom)>((cwspeed*3)/2)) && blank && MorseSignal==0){blank=0;t=micros();probel=1;printM();index=0;}
if (MorseSignal==0 && micros()-joom>cwspeed*7 && probel){
                                                     if (backspace){if (KB_On){Keyboard.print(" ");} }
                                                     backspace=1;
                                                     probel=0;}
}
