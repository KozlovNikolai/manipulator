#include <Keyboard.h>
#include "CyberLib.h"
#define BUTTON_DOT 6
#define BUTTON_TIRE 7
#define OUTPORT 4
#define BEEPER 5

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
  "F","H","C","ch","sh","Q","Y","X","é","ü",
  "ä",
  "1","2","3","4","5","6","7","8","9","0",
  ".",".",":",";","(","\'","\"","-","/","?",",",
  "=","pereboy","@"," *END* "," *back* "," *layout* ",
  "pereboy","pereboy","pereboy","pereboy",
  ""
};
char** CurrentLayout;

unsigned int key, keyflag, MorseSignal, DotMemory, TireMemory, pad, oldMorseSignal, blank, len;
unsigned int temp, index, probel, alfa, backspace;
unsigned long int cwspeed = 70000;
unsigned int WPM=20;
unsigned int CPM;
unsigned long int t, timer, joom, sound;
unsigned int FLAG =0;
char text[11];

void setup(){
  CurrentLayout = layoutLatin;
 // CurrentLayout = layoutCyrillic;
 cwspeed=1176000/WPM;
 backspace=1;
 DotMemory=0;
  Keyboard.begin();
 // Serial.begin(9600);
  pinMode(BUTTON_DOT, INPUT_PULLUP);
  pinMode(BUTTON_TIRE, INPUT_PULLUP);
  pinMode(A1, INPUT);
  pinMode(OUTPORT, OUTPUT);
  pinMode(BEEPER, OUTPUT); 
  D8_Out; //тестовый порт
}

void PrintSpeed() {
 
  Keyboard.write(176); 
  if(CurrentLayout==layoutCyrillic){Keyboard.print("rjl = ");}else{Keyboard.print("key = ");} Keyboard.print(key);
  if(CurrentLayout==layoutCyrillic){Keyboard.print("? CDV crjhjcnm = ");}else{Keyboard.print(", CPM/WPM/speed = ");} Keyboard.print(CPM);Keyboard.print(" "); Keyboard.print(WPM);Keyboard.print(" ");Keyboard.print(cwspeed);
  if(CurrentLayout==layoutCyrillic) {Keyboard.print("? hfcrkflrf = ");}else{Keyboard.print(", Layout = ");} 
  if (CurrentLayout==layoutCyrillic){Keyboard.print("rbhbkkbwf");}else {Keyboard.print("layoutLatin");Keyboard.write(176);};
  Keyboard.write(176); 
  Keyboard.releaseAll();
  }

void speedset(){
  if (key>580 && key<620){if (!keyflag){keyflag=1;WPM=WPM-1;PrintSpeed();
                                                  if (WPM==0){WPM=WPM+1;};
                                      };
                        }
 if (key>780 && key<820){if (!keyflag){keyflag=1;WPM=WPM+1;PrintSpeed();
                                                  if (WPM==1023){WPM=WPM-1;};
                                      };
                        }
  cwspeed=1176000/WPM;
  CPM=WPM*5;
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
      if (CurrentLayout[i]==" *back* "){Keyboard.write(178);alfa=0;backspace=0;}       //backspace
      if (CurrentLayout[i]=="@"){PrintSpeed(); alfa=0;}                                     //Speed CW
      if (CurrentLayout[i]==" *END* "){Keyboard.write(176);alfa=0;backspace=0;}  //Enter
      if (CurrentLayout[i]=="pereboy") {alfa=0; Keyboard.print("[ZP]");}
      if (CurrentLayout[i]==" *layout* "){if (CurrentLayout==layoutLatin){CurrentLayout=layoutCyrillic;
                                                                          Keyboard.press(129);delay(200); //press left shift
                                                                          Keyboard.press(128);delay(300); //press left ctrl
                                                                          Keyboard.releaseAll();}  
                                        else {CurrentLayout=layoutLatin;
                                              Keyboard.press(129);delay(200);  //press left shift
                                              Keyboard.press(128);delay(300);  //press left ctrl
                                              Keyboard.releaseAll();}
                                        alfa=0;backspace=0;
                                        PrintSpeed();}  //Layout
      if (alfa) { Keyboard.print(CurrentLayout[i]); }
      len = 0;
      return;
    }
  }
  // Символ в таблице не найден. Напечатаем нераспознанный символ.
 // Keyboard.print("*");
 
  Keyboard.print(" [");
  for (i = 0; i < len; i++) {
    //Serial.print(text[i]);
    Keyboard.print(text[i]);
  }
  Keyboard.print(" ]");
  
  len = 0;
}
//----------------------------------------------------------------------------------------------------------------
void loop (){
  D8_Inv;
  
//-------------------read key-----------
key=analogRead(A1);
if (key>4) {speedset();} else {keyflag=0;} //если код кнопки больше 4ех, то идем в обработчик клавиатуры
//--------------------опрос манипулятора------------------------------------
if (!digitalRead(BUTTON_DOT) && !digitalRead(BUTTON_TIRE) && MorseSignal==0) { //если нажата точка и тире и текущего сигнала нет, то
                                          if (oldMorseSignal==1){timer=cwspeed*3;beepon();digitalWrite(OUTPORT,1);MorseSignal=2;oldMorseSignal=MorseSignal;flow();}//если последняя была точка, то включаем тире
                                                            else{timer=cwspeed*1;beepon();digitalWrite(OUTPORT,1);MorseSignal=1;oldMorseSignal=MorseSignal;flow();};//если последнее было тире, включаем точку
                                                            t=micros();} //запоминаем время включения сигнала
if (oldMorseSignal==1){DotMemory=0;} //если раньше была точка, то память на точку не используем.
if ((!digitalRead(BUTTON_DOT) or (DotMemory))  && MorseSignal==0){       //если сигнал отсутствует и нажата точка или есть точка в памяти, то
                              DotMemory=0; timer=cwspeed*1;beepon();digitalWrite(OUTPORT,1);MorseSignal=1;oldMorseSignal=MorseSignal;t=micros();flow();} //передаем точку и запоминаем время начала передачи
if (!digitalRead(BUTTON_TIRE) && MorseSignal==0){                     //если сигнал отсутствует и нажато тире, то 
                              timer=cwspeed*3;beepon();digitalWrite(OUTPORT,1);MorseSignal=2;oldMorseSignal=MorseSignal;t=micros();flow();} // передаем тире и запоминаем время начала передачи
if (MorseSignal==2 && !digitalRead(BUTTON_DOT)){DotMemory=1;}; // если нажата точка и в этот момент передается тире, то запоминаем в памяти точку
//------------------------------------------------------
if (micros()-t>timer){ 
                   if(digitalRead(OUTPORT)){beepoff();digitalWrite(OUTPORT,0);joom=micros();}}
if ((micros()-t)>(timer+cwspeed)){/*oldMorseSignal=MorseSignal; */MorseSignal=0;}
if (MorseSignal==2 && !digitalRead(BUTTON_DOT)){DotMemory=1;};
if (MorseSignal){blank=1;}
if (((micros()-joom)>((cwspeed*3)/2)) && blank && MorseSignal==0){blank=0;t=micros();probel=1;printM();index=0;}
if (MorseSignal==0 && micros()-joom>cwspeed*7 && probel){
                                                     if (backspace){Keyboard.print(" "); }
                                                     backspace=1;
                                                     probel=0;}
}

