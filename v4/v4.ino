#include <Keyboard.h>
#include <Wire.h>
//#include "CyberLib.h"
#include <ASOLED.h>
#include <EEPROM.h>

#define ButtDitPIN 7             //manipulyator dit arduino pin
#define ButtDit bitRead(PINE,6)  //manipulyator dit chip pin
#define ButtDahPIN 6             //manipulyator dah arduino pin
#define ButtDah bitRead(PIND,7)  //manipulyator dah chip pin

#define BEEPER 5            //beeper pin
#define CLK bitRead(PINB,6) //encoder CLK chip number
#define CLKPIN 10           //encoder CLK arduino number
#define DT bitRead(PINB,2)  //encoder DT chip number     
#define DTPIN 16            //encoder DT arduino number
#define EncBut bitRead(PINB,3)  //button encoder chip number
#define EncButPIN 14            //button encoder arduino number
#define ReleOn bitSet(PORTB,5)    //rele chip number On
#define ReleOff bitClear(PORTB,5) //rele chip number off
#define RelePIN  9                //rele arduino number
#define OutOn bitSet(PORTD,4)    //output chip number On
#define OutOff bitClear(PORTD,4) //output chip number off
#define OutStatus bitRead(PIND,4) //output status by chip
#define OutPIN  4                //output arduino number
#define BeepOn bitSet(PORTC,6)    //beeper chip number On
#define BeepOff bitClear(PORTC,6) //beeper chip number off
#define BeepPIN  5                //beeper arduino number
#define VERSION "4.0"
#define chMenu 1  //vybor punkta menu
#define chParam 0 //izmenenie parametra v vybrannom punkte menu
#define maxMenu 8 //kolichestvo punktov menu
#define WPM CPM/5 

boolean saveOK = 0;
boolean modeMenu = chParam;
byte menuCount = 1;
byte menuCountLast = 1;
boolean DT_now, DT_last,turnFlag; //encoder temp variables
int maxValue[maxMenu+1] = {0,400,4,2,2,3,400,2,1}; 
int CPM = 100;         //skorost v znakah v minutu
byte modeDev = 1;       //rezhym raboty klyucha - yambik a, yambic b i t.d.
byte modeKeyboard = 2;  //otpravka simvolov na komputer
byte modeRele = 2;      //on off rele
byte modeAutoPause = 1; // rezhym raboty avtopausy
byte coeffTire = 30;    //razmer tire v tochkah
byte reverse = 1;       //revers dit/dah pins
unsigned long int timer, stopFlow; //
unsigned long int sizeDot;             //razmer tochki
unsigned long int sizeTire;            //razmer Tire
boolean TireMemory, DotMemory, DitPause =0; //
//peremennye dlya decodera
byte MorseSignal, LastMorseSignal = 0;
char text[11];
unsigned int index = 0;
boolean TypeChar =0;
// Таблица кодов Морзе. N-ный элемент кода соответствует n-ному символу раскладки.
const char* code[] = {
  "*-", "-***", "*--", "--*", "-**", "*", "***-", "--**", "**", "*---",
  "-*-", "*-**", "--", "-*", "---", "*--*", "*-*", "***", "-", "**-",
  "**-*", "****", "-*-*", "---*", "----", "--*-", "-*--", "-**-", "**-**", "**--",
  "*-*-",
  "*----", "**---", "***--", "****-", "*****", "-****", "--***", "---**", "----*", "-----",
  "......", "*-*-*-", "---***", "-*-*-*", "-*--*-", "*----*", "*-**-*", "-****-", "-**-*", "**--**", "--**--",
  "-***-", "********", "*--*-*", "**-*-", "*-*-*-*-", "-*-*-*-",
  "******", "*******", "*********", "**********",
  ""
};
// Латинская раскладка.
const char* layoutLatin[] = {
  "A", "B", "W", "G", "D", "E", "V", "Z", "I", "J",
  "K", "L", "M", "N", "O", "P", "R", "S", "T", "U",
  "F", "H", "C", "ch", "sh", "Q", "Y", "X", "**-**", "**--",
  "ya",
  "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
  ".", ".", ":", ";", "(", "\'", "\"", "-", "/", "?", ",",
  "=", "pereboy", "@", " *END* ", " *back* ", " *layout* ",
  "pereboy", "pereboy", "pereboy", "pereboy",
  ""
};
int EEPROMReadInt(int p_address){
        byte lowByte = EEPROM.read(p_address);
        byte highByte = EEPROM.read(p_address + 1);

        return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
        }
void EEPROMWriteInt(int p_address, int p_value){
        byte lowByte = ((p_value >> 0) & 0xFF);
        byte highByte = ((p_value >> 8) & 0xFF);

        EEPROM.write(p_address, lowByte);
        EEPROM.write(p_address + 1, highByte);
        }
void doParameter (int temp){
            int tempLast=temp;
            temp = doEncoder(temp);
            if (temp<1){temp=1;}
            if (temp>maxValue[menuCount]){temp=maxValue[menuCount];}
             if (temp!=tempLast){switch (menuCount){case 1:CPM=temp;sizeDot = 5880000 / CPM;sizeTire=(sizeDot*coeffTire)/10;doPrint();break;
                                                    case 2:modeDev=temp;doPrint();break;
                                                    case 3:modeKeyboard=temp;doPrint();break;
                                                    case 4:modeRele=temp;doPrint();break;
                                                    case 5:modeAutoPause=temp;doPrint();break;
                                                    case 6:coeffTire=temp;sizeTire=(sizeDot*coeffTire)/10;doPrint();break;
                                                    case 7:reverse=temp;doPrint();break;
                                                    }
             }
           // return temp;
}
int doEncoder(int temp) {
  DT_now = CLK;
  if (DT_now != DT_last) // если предыдущее и текущее положение CLK разные, значит был поворот
         {if (DT != DT_now )  // если состояние DT отличается от CLK, значит крутим по часовой стрелке
             {if(turnFlag){temp ++;turnFlag=!turnFlag;}else{turnFlag=!turnFlag;}}                    // прибавить счётчик
          else {if(turnFlag){temp --;turnFlag=!turnFlag;}else{turnFlag=!turnFlag;}}                          // если совпадают, значит против часовой - убавить счётчик
         }
  DT_last = DT_now; 
return temp;
} 
int doEncButton(){if (!EncBut){delay(300);
                                        if(!EncBut){return 2;}
                                        else{return 1;}
                                        }
                  else{return 0;}
}
boolean doButtDit(){
  switch (reverse){case 2:return(!ButtDit);break;
                   case 1:return(!ButtDah);break;}
}
boolean doButtDah(){
  switch (reverse){case 2:return(!ButtDah);break;
                   case 1:return(!ButtDit);break;} 
}
void doPrint() {
  switch (menuCount){
    case 1: LD.printString_12x16 ("CPM  WPM  ", 0, 0);LD.printString_12x16 ("          ", 0, 2);LD.printNumber((long)CPM, 0, 2);LD.printNumber((long)WPM, 62, 2);break;
    case 2: LD.printString_12x16 ("2.MODE    ", 0, 0);LD.printString_12x16 ("          ", 0, 2);if(modeDev==1){LD.printString_12x16(" Iambic A ", 0, 2);};
                                                                                                if(modeDev==2){LD.printString_12x16(" Iambic AT", 0, 2);};
                                                                                                if(modeDev==3){LD.printString_12x16(" Iambic B ", 0, 2);};
                                                                                                if(modeDev==4){LD.printString_12x16(" Classic  ", 0, 2);};break;
    case 3: LD.printString_12x16 ("3.Keyboard", 0, 0);LD.printString_12x16 ("          ", 0, 2);if(modeKeyboard==1){LD.printString_12x16(" On       ", 0, 2);};
                                                                                                if(modeKeyboard==2){LD.printString_12x16(" Off      ", 0, 2);};break;
    case 4: LD.printString_12x16 ("4.Rele    ", 0, 0);LD.printString_12x16 ("          ", 0, 2);if(modeRele==1){LD.printString_12x16(" On       ", 0, 2);};
                                                                                                if(modeRele==2){LD.printString_12x16(" Off      ", 0, 2);};break;
    case 5: LD.printString_12x16 ("5AutoPause", 0, 0);LD.printString_12x16 ("          ", 0, 2);if(modeAutoPause==1){LD.printString_12x16("On - Znak ", 0, 2);};
                                                                                                if(modeAutoPause==2){LD.printString_12x16("On - Slovo", 0, 2);};
                                                                                                if(modeAutoPause==3){LD.printString_12x16(" Off      ", 0, 2);};break;
    case 6: LD.printString_12x16 ("6.Tire    ", 0, 0);LD.printString_12x16 (" .        ", 0, 2);LD.printNumber((long)coeffTire/10, 0, 2);LD.printNumber((long)(coeffTire-(coeffTire/10)*10), 20, 2);break;
    case 7: LD.printString_12x16 ("7.Reverse ", 0, 0);LD.printString_12x16 ("          ", 0, 2);if(reverse==1){LD.printString_12x16(" On       ", 0, 2);};
                                                                                                if(reverse==2){LD.printString_12x16(" Off      ", 0, 2);};break;
    case 8: LD.printString_12x16 ("8.SAVE    ", 0, 0);LD.printString_12x16 ("          ", 0, 2);if(saveOK){LD.printString_12x16 ("   OK     ", 0, 2);};break;
  }
}
void doMenu(){
  if (modeMenu==chMenu){
        menuCount = doEncoder(menuCount);
        if (menuCount<1){menuCount=1;}
        if (menuCount>maxMenu){menuCount=maxMenu;}
        if (menuCount!=menuCountLast){doPrint();}
        menuCountLast=menuCount;
  }
  else {
    switch (menuCount){
    case 1: doParameter(CPM); break;
    case 2: doParameter(modeDev); break;
    case 3: doParameter(modeKeyboard); break;
    case 4: doParameter(modeRele); break;
    case 5: doParameter(modeAutoPause); break;
    case 6: doParameter(coeffTire); break;
    case 7: doParameter(reverse); break;
    case 8: break;
  }
  }
  switch(doEncButton()){
    case 1: modeMenu=!modeMenu; if(!modeMenu){LD.printString_12x16 ("^^^       ", 0, 4);}else{LD.printString_12x16 ("          ", 0, 4);} break;
    case 2: if(menuCount==8){
            EEPROMWriteInt(0, CPM);
            EEPROMWriteInt(2, modeDev);
            EEPROMWriteInt(4, modeRele);
            EEPROMWriteInt(6, modeAutoPause);
            EEPROMWriteInt(8, coeffTire);
            EEPROMWriteInt(10, reverse);
            LD.printString_12x16 ("SAVING OK!", 0, 4);delay(1000);LD.printString_12x16 ("          ", 0, 4); break;
    }
  }
}
void doIambicA(){if(doButtDit() && doButtDah() && !MorseSignal){switch(LastMorseSignal){
                                                                  case 1: if(doButtDah() && !DitPause)   {MorseSignal=2;doOutOn();};break;
                                                                  case 2: if(doButtDit() && !DitPause)   {MorseSignal=1;doOutOn();};break;
                                                                  }
                                          }
                 else{if(doButtDit() && !MorseSignal)   {MorseSignal=1;doOutOn();};
                      if(doButtDah() && !MorseSignal)   {MorseSignal=2;doOutOn();}
                     }
}
void doIambicAT(){if(doButtDit() && MorseSignal==2 && OutStatus){DotMemory=1;}
                  if(doButtDit() && doButtDah() && !MorseSignal && !DotMemory){switch(LastMorseSignal){
                                                                                                  case 1: if(doButtDah() && !DitPause)   {MorseSignal=2;doOutOn();};break;
                                                                                                  case 2: if(doButtDit() && !DitPause)   {MorseSignal=1;doOutOn();};break;
                                                                                                  }
                                                                          }
                 else{if(doButtDit() && !MorseSignal && !DotMemory)   {MorseSignal=1;doOutOn();};
                      if(doButtDah() && !MorseSignal && !DotMemory)   {MorseSignal=2;doOutOn();}
                     }
                if(DotMemory && !DitPause && !OutStatus)   {MorseSignal=1;doOutOn();DotMemory=0;}
}
void doIambicB(){if(doButtDit() && MorseSignal==2 && OutStatus){DotMemory=1;}
                 if(doButtDah() && MorseSignal==1 && OutStatus){TireMemory=1;}
                 if(doButtDit() && doButtDah() && !MorseSignal && !DotMemory && !TireMemory){switch(LastMorseSignal){
                                                                                                  case 1: if(doButtDah() && !DitPause)   {MorseSignal=2;doOutOn();};break;
                                                                                                  case 2: if(doButtDit() && !DitPause)   {MorseSignal=1;doOutOn();};break;
                                                                                                  }
                                                                          }
                 else{if(doButtDit() && !MorseSignal && !DotMemory && !TireMemory)   {MorseSignal=1;doOutOn();};
                      if(doButtDah() && !MorseSignal && !DotMemory && !TireMemory)   {MorseSignal=2;doOutOn();}
                     }
                if(DotMemory && !DitPause && !OutStatus)   {MorseSignal=1;doOutOn();DotMemory=0;}
                if(TireMemory && !DitPause && !OutStatus)   {MorseSignal=2;doOutOn();TireMemory=0;}
}
void doClassic(){if(doButtDit() && doButtDah() && !MorseSignal){switch(LastMorseSignal){
                                                                  case 1: if(doButtDit() && !DitPause)   {MorseSignal=1;doOutOn();};break;
                                                                  case 2: if(doButtDah() && !DitPause)   {MorseSignal=2;doOutOn();};break;
                                                                  }
                                          }
                 else{if(doButtDit() && !MorseSignal)   {MorseSignal=1;doOutOn();};
                      if(doButtDah() && !MorseSignal)   {MorseSignal=2;doOutOn();}
                     }
}
void doOutOn(){
  if(modeRele==1){ReleOn;OutOn;BeepOn;timer=micros();flow();}
  else{OutOn;BeepOn;timer=micros();flow();}
}
void doOutOff(){
if (OutStatus){switch(MorseSignal){
                                    case 1: if(micros()-timer>sizeDot){ReleOff;OutOff;BeepOff;DitPause=1;timer=micros();};break;
                                    case 2: if(micros()-timer>sizeTire){ReleOff;OutOff;BeepOff;DitPause=1;timer=micros();};break;
                                   }
              }
else          {
               if(DitPause){if(micros()-timer>sizeDot){DitPause=0;LastMorseSignal=MorseSignal;MorseSignal=0;stopFlow=micros();TypeChar=1;}}
              }
}
void flow() {
  if (MorseSignal == 1) {
    text[index] = '*';
    text[index + 1] = '\0';
  }
  if (MorseSignal == 2) {
    text[index] = '-';
    text[index + 1] = '\0';
  }
  if(index<10){index++;}
}
void printM() {
  int i, j, len =0;
  int temp = 1;
  boolean alfa = 0;
  while (temp) {
    if (text[len] == '\0') {
      temp = 0;
    }
    len++;
  }
  if (len < 1) {
    return;
  }
  for (i = 0; code[i][0] != '\0'; i++) {
    // Сравним введенный символ с символами из таблицы кодов Морзе.
    for (j = 0; (j < len) && (code[i][j] != '\0'); j++) {
      if (code[i][j] != text[j]) {
        j = -1;
        break;
      }
    }
    if ((j != -1) && ((j + 1) == len) && (code[i][j] == '\0')) {
      // Символ из таблицы кодов Морзе соответствует введенному символу.
      //  Отправим символ на компьютер.
      alfa = 1;
      if (layoutLatin[i] == "pereboy") {
        alfa = 0;
        if (modeKeyboard==1) {
          Keyboard.print("[ZP]");
        }
      }
      if (alfa) {
        if (modeKeyboard==1) {
          Keyboard.print(layoutLatin[i]);
        }
      }
      len = 0;
      return;
    }
  }
  // Символ в таблице не найден. Напечатаем нераспознанный символ.
  // Keyboard.print("*");
  if (modeKeyboard==1) {
    Keyboard.print(" [");
    for (i = 0; i < len; i++) {
      Keyboard.print(text[i]);
    }
    Keyboard.print("] ");
  }
  len = 0;
}
void setup() {
 // Serial.begin(9600);
  pinMode(ButtDitPIN, INPUT_PULLUP);
  pinMode(ButtDahPIN, INPUT_PULLUP);
  LD.init();LD.clearDisplay();LD.setNormalDisplay();LD.SetNormalOrientation();LD.setBrightness(255);
  pinMode(CLKPIN, INPUT_PULLUP);
  pinMode(DTPIN, INPUT_PULLUP);
  pinMode(EncButPIN, INPUT_PULLUP);
  pinMode(RelePIN, OUTPUT);
  pinMode(OutPIN, OUTPUT);
  pinMode(BeepPIN, OUTPUT);
  ReleOff;
  OutOff;
  //OutOn;
  BeepOff;
  DT_last = CLK;
  CPM=EEPROMReadInt(0);
  modeDev=EEPROMReadInt(2);
  modeRele=EEPROMReadInt(4);
  modeAutoPause=EEPROMReadInt(6);
  coeffTire=EEPROMReadInt(8);
  reverse=EEPROMReadInt(10);
  sizeDot = 5880000 / CPM;
  sizeTire = (sizeDot*coeffTire)/10;
  doPrint();
  LD.printString_12x16 ("V", 0, 6); LD.printString(VERSION);
  if(!modeMenu){LD.printString_12x16 ("^^^       ", 0, 4);}else{LD.printString_12x16 ("          ", 0, 4);}
}
void loop() {
 doMenu();
 switch(modeDev){
  case 1: doIambicA();break;
  case 2: doIambicAT();break;
  case 3: doIambicB();break;
  case 4: doClassic();break;
 }
 doOutOff();
 if(TypeChar){
   if (((micros() - stopFlow) > ((sizeTire) / 2)) && MorseSignal == 0) {printM();index = 0;TypeChar=0;}
             }
}
