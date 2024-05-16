#include <Keyboard.h>
#include <Wire.h>
#include "CyberLib.h"
#include <ASOLED.h>
#include <EEPROM.h>

#define BUTTON_DOT D7_Read
#define BUTTON_TIRE D6_Read
#define OUTPORT 4
#define BEEPER 5
#define CLK 10
#define DT 16
#define SW 14
#define VERSION "2.1"

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
boolean DT_now, DT_last;
unsigned int key, keyflag, MorseSignal, DotMemory, TireMemory, pad, oldMorseSignal, blank, len;
unsigned int temp, index, probel, alfa, backspace;
unsigned int CPM;
unsigned int WPM;
unsigned long int cwspeed = 117600 / WPM;
unsigned long int t, timer, joom, sound;
unsigned int FLAG = 0;
char text[11];
boolean KB_On = 0;
void setup() {
  LD.init();
  LD.clearDisplay();
  LD.setNormalDisplay();
  LD.SetNormalOrientation();
  LD.setBrightness(255);
  CPM=EEPROMReadInt(0);
  WPM = CPM / 5;
  PrintSpeed();
  cwspeed = 5880000 / CPM;
  backspace = 1;
  DotMemory = 0;
  Keyboard.begin();
  // Serial.begin(9600);
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
//----------------------------------------------------------------------------------------------------
int EEPROMReadInt(int p_address)
        {
        byte lowByte = EEPROM.read(p_address);
        byte highByte = EEPROM.read(p_address + 1);

        return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
        }
void EEPROMWriteInt(int p_address, int p_value)
       {
        byte lowByte = ((p_value >> 0) & 0xFF);
        byte highByte = ((p_value >> 8) & 0xFF);

        EEPROM.write(p_address, lowByte);
        EEPROM.write(p_address + 1, highByte);
        }
 //-------------------------------------------------------------------------------------------------------------
void PrintSpeed() {
  LD.clearDisplay();
  LD.printString_12x16 ("CPM=", 0, 0);  LD.printNumber((long)CPM);
  LD.printString_12x16 ("WPM=", 0, 2); LD.printNumber((long)WPM);
  if (KB_On) {
    LD.printString_12x16("WinKey-On", 0, 4);
  }
  else {
    LD.printString_12x16("WinKey-Off", 0, 4);
  }
  LD.printString_12x16 ("Ver. = ", 0, 6); LD.printString(VERSION);
}
//-------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------
void beepon() {
  //analogWrite(BEEPER, 20);
  digitalWrite(BEEPER,1);
}
void beepoff() {
  //analogWrite(BEEPER, 0);
  digitalWrite(BEEPER,0);
}
//------------------------------------------------------------------------------------------------------------
void printM() {
  int i, j;
  temp = 1;
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
        if (KB_On) {
          Keyboard.print("[ZP]");
        }
      }
      if (alfa) {
        if (KB_On) {
          Keyboard.print(layoutLatin[i]);
        }
      }
      len = 0;
      return;
    }
  }
  // Символ в таблице не найден. Напечатаем нераспознанный символ.
  // Keyboard.print("*");
  if (KB_On) {
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
  long timer1;
  DT_now = digitalRead(CLK);          // читаем текущее положение CLK
  if (DT_now != DT_last && DT_now < 1) { // если предыдущее и текущее положение CLK разные, значит был поворот
    if (digitalRead(DT) != DT_now) {  // если состояние DT отличается от CLK, значит крутим по часовой стрелке
      CPM ++;                     // прибавить счётчик
    } else {                          // если совпадают, значит против часовой
      CPM --;                     // убавить счётчик
    }
    WPM = CPM / 5;
    cwspeed = 5880000 / CPM;
    LD.printNumber((long)CPM,48,0);LD.printString_12x16(" ");
    LD.printNumber((long)WPM,48,2);LD.printString_12x16(" ");
  }
  DT_last = DT_now;                   // обновить значение
  if (!digitalRead(SW)){timer1=millis();
    while (!digitalRead(SW)) {}
    if (millis()-timer1>1000){EEPROMWriteInt(0, CPM);LD.clearDisplay();LD.printString_12x16("CPM Saved",0,2);delay(1000);PrintSpeed();}
    if (millis()-timer1>100){
                             KB_On = !KB_On;
                             if(KB_On){LD.printString_12x16("On ", 84, 4);}
                             else {LD.printString_12x16("Off", 84, 4);}
                             }
  }
}
//----------------------------------------------------------------------------------------------------------------
void loop () {
  encoderTick();
  //--------------------опрос манипулятора------------------------------------
  if (!BUTTON_DOT && !BUTTON_TIRE && MorseSignal == 0) { //если нажата точка и тире и текущего сигнала нет, то
    if (oldMorseSignal == 1) {
      timer = cwspeed * 3;  //если последняя была точка, то включаем тире
      beepon();
      D4_High;
      MorseSignal = 2;
      oldMorseSignal = MorseSignal;
      flow();
    }
    else {
      timer = cwspeed * 1;
      beepon();
      D4_High;
      MorseSignal = 1;
      oldMorseSignal = MorseSignal;
      flow();
    };//если последнее было тире, включаем точку
    t = micros();
  } //запоминаем время включения сигнала
  if (oldMorseSignal == 1) {
    DotMemory = 0; //если раньше была точка, то память на точку не используем.
  }
  if ((!BUTTON_DOT or (DotMemory))  && MorseSignal == 0) {    //если сигнал отсутствует и нажата точка или есть точка в памяти, то
    DotMemory = 0; timer = cwspeed * 1; beepon(); D4_High; MorseSignal = 1; oldMorseSignal = MorseSignal; t = micros(); flow();
  } //передаем точку и запоминаем время начала передачи
  if (!BUTTON_TIRE && MorseSignal == 0) {                  //если сигнал отсутствует и нажато тире, то
    timer = cwspeed * 3; beepon(); D4_High; MorseSignal = 2; oldMorseSignal = MorseSignal; t = micros(); flow();
  } // передаем тире и запоминаем время начала передачи
  if (MorseSignal == 2 && !BUTTON_DOT) {
    DotMemory = 1;
  }; // если нажата точка и в этот момент передается тире, то запоминаем в памяти точку
  //------------------------------------------------------
  if (micros() - t > timer) {
    if (digitalRead(OUTPORT)) {
      beepoff();
      D4_Low;
      joom = micros();
    }
  }
  if ((micros() - t) > (timer + cwspeed)) {
    MorseSignal = 0;
  }
  if (MorseSignal == 2 && !BUTTON_DOT) {
    DotMemory = 1;
  };
  if (MorseSignal) {
    blank = 1;
  }
  if (((micros() - joom) > ((cwspeed * 3) / 2)) && blank && MorseSignal == 0) {
    blank = 0;
    t = micros();
    probel = 1;
    printM();
    index = 0;
  }
  if (MorseSignal == 0 && micros() - joom > cwspeed * 7 && probel) {
    if (backspace) {
      if (KB_On) {
        Keyboard.print(" ");
      }
    }
    backspace = 1;
    probel = 0;
  }
}
