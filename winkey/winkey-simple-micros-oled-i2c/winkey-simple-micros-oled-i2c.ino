//#include <Keyboard.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BUTTON_DOT 7
#define BUTTON_TIRE 6
#define OUTPORT 4
#define BEEPER 5

#define OLED_RESET 8

Adafruit_SSD1306 display(OLED_RESET);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

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
//unsigned int tonebeep =500;
unsigned int key, keyflag, MorseSignal, DotMemory, oldMorseSignal, blank, len;
unsigned int temp, index, probel, alfa, backspace, temp1;
unsigned long int cwspeed = 70000;
unsigned int WPM=17;
unsigned int CPM;
unsigned long int t, timer, joom, sound;
unsigned int FLAG =0;
char text[11];
char textdisp[9];

void setup(){
  for (int i=0;i<9;i++){textdisp[i]=' ';}
  textdisp[9]='\0';
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C
  CurrentLayout = layoutLatin;
 // CurrentLayout = layoutCyrillic;
 cwspeed=1176000/WPM;
 backspace=1;
 DotMemory=0;
 temp1=0;
 // Keyboard.begin();
 // Serial.begin(9600);
  pinMode(BUTTON_DOT, INPUT_PULLUP);
  pinMode(BUTTON_TIRE, INPUT_PULLUP);
  pinMode(A1, INPUT);
  pinMode(OUTPORT, OUTPUT);
  pinMode(BEEPER, OUTPUT); 

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextWrap(0);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.display();
}

void PrintDisp(char* simb){
  if (temp1==8){
    for(int i=0;i<8;i++){textdisp[temp1]=textdisp[temp1+1];}
  }
  textdisp[temp1]=*simb;
  if(temp1<8){temp1++;};
  display.setCursor(0,0);
  display.print(textdisp); 
  display.display();
}

void PrintSpeed() {
 
/*  Keyboard.write(176); 
  if(CurrentLayout==layoutCyrillic){Keyboard.print("rjl = ");}else{Keyboard.print("key = ");} Keyboard.print(key);
  if(CurrentLayout==layoutCyrillic){Keyboard.print("? CDV crjhjcnm = ");}else{Keyboard.print(", CPM/WPM/speed = ");} Keyboard.print(CPM);Keyboard.print(" "); Keyboard.print(WPM);Keyboard.print(" ");Keyboard.print(cwspeed);
  if(CurrentLayout==layoutCyrillic) {Keyboard.print("? hfcrkflrf = ");}else{Keyboard.print(", Layout = ");} 
  if (CurrentLayout==layoutCyrillic){Keyboard.print("rbhbkkbwf");}else {Keyboard.print("layoutLatin");Keyboard.write(176);};
  Keyboard.write(176); 
  Keyboard.releaseAll();*/
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
  analogWrite(BEEPER,125);
  //tone(BEEPER,tonebeep);
}
void beepoff(){
  //noTone(BEEPER);
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
    /*  if (CurrentLayout[i]==" *back* "){Keyboard.write(178);alfa=0;backspace=0;}       //backspace
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
                                        */
      if (alfa) { 
        PrintDisp(CurrentLayout[i]);
        }
      len = 0;
      return;
    }
  }
  // Символ в таблице не найден. Напечатаем нераспознанный символ.
PrintDisp("*");
  /*Keyboard.print(" [");
  for (i = 0; i < len; i++) {
    //Serial.print(text[i]);
    Keyboard.print(text[i]);
  }
  Keyboard.print(" ]");*/
  
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
                                                            t=micros();}
if (oldMorseSignal==1){DotMemory=0;}
if ((!digitalRead(BUTTON_DOT) or (DotMemory))  && MorseSignal==0) {DotMemory=0; timer=cwspeed*1;beepon();digitalWrite(OUTPORT,1);MorseSignal=1;t=micros();flow();}
if (!digitalRead(BUTTON_TIRE) && MorseSignal==0){timer=cwspeed*3;beepon();digitalWrite(OUTPORT,1);MorseSignal=2;t=micros();flow();}
if (micros()-t>timer){if(digitalRead(OUTPORT)){beepoff();digitalWrite(OUTPORT,0);joom=micros();}}
if ((micros()-t)>(timer+cwspeed)){oldMorseSignal=MorseSignal; MorseSignal=0;}
if (MorseSignal==2 && !digitalRead(BUTTON_DOT)){DotMemory=1;};
if (MorseSignal){blank=1;}
//if (micros()-t>(cwspeed*5) && blank){blank=0;t=micros();probel=1;printM();index=0;}
//Keyboard.print("D joom = ");Keyboard.print(micros()-joom);Keyboard.print("cwspeed*3 = ");Keyboard.print(cwspeed*3);Keyboard.print("blank = ");Keyboard.print(blank);Keyboard.print("MS = ");Keyboard.print(MorseSignal);Keyboard.write(176);
if (((micros()-joom)>((cwspeed*3)/2)) && blank && MorseSignal==0){blank=0;t=micros();probel=1;printM();index=0;}
if (MorseSignal==0 && micros()-joom>cwspeed*7 && probel){
                                                     if (backspace){PrintDisp(" "); }
                                                     backspace=1;
                                                     probel=0;}
}

