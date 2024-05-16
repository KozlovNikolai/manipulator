#include <Keyboard.h>

#define BUTTON_DOT 3
#define BUTTON_TIRE 2
#define OUTPORT 4
#define BEEPER 5

// Таблица кодов Морзе. N-ный элемент кода соответствует n-ному символу раскладки.
char* code[] = {
  "*-","-***","*--","--*","-**","*","***-","--**","**","*---",
  "-*-","*-**","--","-*","---","*--*","*-*","***","-","**-",
  "**-*","****","-*-*","---*","----","--*-","-*--","-**-","**-**","**--",
  "*-*-",
  "*----","**---","***--","****-","*****","-****","--***","---**","----*","-----",
  "......","*-*-*-","---***","-*-*-","-*--*-","*----*","*-**-*","-****-","-**-*","**--**","--**--",
  "-***-","********","*--*-*","**-*-","*-*-*-*-","-*-*-*-",
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
  "="," *ERR* ","@"," *END* "," *back* "," *layout* ",
  ""
  };
  
// Латинская раскладка.
char* layoutLatin[] = {
  "A","B","W","G","D","E","V","Z","I","J",
  "K","L","M","N","O","P","R","S","T","U",
  "F","H","C","ö","ch","Q","Y","X","é","ü",
  "ä",
  "1","2","3","4","5","6","7","8","9","0",
  ".",".",":",";","(","\'","\"","-","/","?",",",
  "="," *ERR* ","@"," *END* "," *back* "," *layout* ",
  ""
};
char** CurrentLayout;

unsigned int key, keyflag, MorseSignal, DotMemory, TireMemory, pad, oldMorseSignal, blank, len;
unsigned int temp, index, probel, alfa, backspace;
unsigned int cwspeed = 70;
unsigned int WPM=17;
unsigned long int t, timer, joom, sound;
unsigned int FLAG =0;
char text[9];

void setup(){
  CurrentLayout = layoutLatin;
 // CurrentLayout = layoutCyrillic;
 cwspeed=1176/WPM;
 backspace=1;
 DotMemory=0;
  Keyboard.begin();
 // Serial.begin(9600);
  pinMode(BUTTON_DOT, INPUT_PULLUP);
  pinMode(BUTTON_TIRE, INPUT_PULLUP);
  pinMode(A1, INPUT);
  pinMode(OUTPORT, OUTPUT);
  pinMode(BEEPER, OUTPUT); 
  sound=micros();
}

void PrintSpeed() {
 
  Keyboard.write(176); 
  if(CurrentLayout==layoutCyrillic){Keyboard.print("rjl = ");}else{Keyboard.print("key = ");} Keyboard.print(key);
  if(CurrentLayout==layoutCyrillic){Keyboard.print("? CDV crjhjcnm = ");}else{Keyboard.print(", WPM/speed = ");} Keyboard.print(WPM);Keyboard.print(" ");Keyboard.print(cwspeed);
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
  cwspeed=1176/WPM;
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
    //Serial.print("len = ");Serial.print(len);Serial.print(", i = ");Serial.print(i);Serial.print(", j = ");Serial.print(j);Serial.print(", code[i][j] = ");Serial.println(code[i][j]);
    if ((j != -1) && ((j+1) == len) && (code[i][j]=='\0')) {
      // Символ из таблицы кодов Морзе соответствует введенному символу.
      //  Отправим символ на компьютер.
      alfa=1;
      if (CurrentLayout[i]==" *back* "){Keyboard.write(178);alfa=0;backspace=0;}       //backspace
      if (CurrentLayout[i]=="@"){PrintSpeed(); alfa=0;}                                     //Speed CW
      if (CurrentLayout[i]==" *END* "){Keyboard.write(176);alfa=0;backspace=0;}  //Enter
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
  Keyboard.print("*");
  /*
  Keyboard.print(" [");
  for (i = 0; i < len; i++) {
    //Serial.print(text[i]);
    Keyboard.print(text[i]);
  }
  Keyboard.print(" ]");
  */
  len = 0;
}
//----------------------------------------------------------------------------------------------------------------
void loop (){
//--------------------sound----------

//if ((micros()-100)>sound){digitalWrite(BEEPER,(!digitalRead(BEEPER)));sound=micros();}
//-------------------read key-----------
key=analogRead(A1);
if (key>4) {speedset();} else {keyflag=0;}
//--------------------------------------------------------
if (!digitalRead(BUTTON_DOT) && !digitalRead(BUTTON_TIRE) && MorseSignal==0) {
                                          if (oldMorseSignal==1){timer=cwspeed*3;beepon();digitalWrite(OUTPORT,1);MorseSignal=2;flow();}
                                                            else{timer=cwspeed*1;beepon();digitalWrite(OUTPORT,1);MorseSignal=1;flow();};
                                                            t=millis();}
if (oldMorseSignal==1){DotMemory=0;}
if ((!digitalRead(BUTTON_DOT) or (DotMemory))  && MorseSignal==0) {DotMemory=0; timer=cwspeed*1;beepon();digitalWrite(OUTPORT,1);MorseSignal=1;t=millis();flow();}
if (!digitalRead(BUTTON_TIRE) && MorseSignal==0){timer=cwspeed*3;beepon();digitalWrite(OUTPORT,1);MorseSignal=2;t=millis();flow();}
if (millis()-t>timer){if(digitalRead(OUTPORT)){beepoff();digitalWrite(OUTPORT,0);joom=millis();}}
if ((millis()-t)>(timer+cwspeed)){oldMorseSignal=MorseSignal; MorseSignal=0;}
if (MorseSignal==2 && !digitalRead(BUTTON_DOT)){DotMemory=1;};
if (MorseSignal){blank=1;}
//if (millis()-t>(cwspeed*5) && blank){blank=0;t=millis();probel=1;printM();index=0;}
//Keyboard.print("D joom = ");Keyboard.print(millis()-joom);Keyboard.print("cwspeed*3 = ");Keyboard.print(cwspeed*3);Keyboard.print("blank = ");Keyboard.print(blank);Keyboard.print("MS = ");Keyboard.print(MorseSignal);Keyboard.write(176);
if (((millis()-joom)>((cwspeed*3)/2)) && blank && MorseSignal==0){blank=0;t=millis();probel=1;printM();index=0;}
if (MorseSignal==0 && millis()-joom>cwspeed*7 && probel){
                                                     if (backspace){Keyboard.print(" "); }
                                                     backspace=1;
                                                     probel=0;}
}

