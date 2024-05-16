String morse_codes[] = {".-",    "-...",  "-.-.",  "-..",   ".",     "..-.",   "--.",    "....",   "..",    ".---", 
                        "-.-",   ".-..",  "--",    "-.",    "---",   ".--.",   ".-.",    "...",    "-",     "..-", 
                        "...-",  ".--",   "-..-",  "-.--",  "--..",  ".----",  "..---",  "...--",  "....-", ".....", 
                        "-....", "--...", "---..", "----.", "-----", "......", ".-.-.-", "--..--", "..--.."};
char* symbols[] = {     "A",     "B",     "C",     "D",     "E",     "F",      "G",      "H",      "I",     "J", 
                        "K",     "L",     "M",     "N",     "O",     "P",      "R",      "S",      "T",     "U", 
                        "V",     "W",     "X",     "Y",     "Z",     "1",      "2",      "3",      "4",     "5", 
                        "6",     "7",     "8",     "9",     "0",     ".",      ",",      "!",      "?",     " "};
byte i = 0;
byte j = 0;
unsigned long timer_backlight = 0;
unsigned long timer1_backlight = 0;
unsigned long timer = 0;
unsigned long cycle_time = 0;
unsigned long timer1 = 0;
String symbol = "";
byte command = 0;
const uint64_t pipe = 0xE8E8F0F0E1LL; 

boolean buttonWasUp = false;
boolean buttonIsUp = true; 
boolean symbol_end = false;
boolean wrong_symbol = false;
boolean Button_switch = true;
boolean transmitter = true;
boolean screen = true;

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2); //адрес другого дисплея 0x27. 16,2 - количество столбцов и строк
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(9,10); 

//функция включения дисплея
void turn_on() {
  lcd.display();
  lcd.backlight();
             }

//функция выключения дисплея
void turn_off() {
  lcd.noDisplay();
  lcd.noBacklight();
             }

//функция передатчика
void transmitter_() {
  buttonIsUp = digitalRead(3);
  if (!buttonIsUp){
    timer = millis();
    delay(20);
    buttonIsUp = digitalRead(3);
  }
    while (!buttonIsUp) { 
      tone(2, 550);
      buttonIsUp = digitalRead(3);
      buttonWasUp = true;
    }
    if (buttonWasUp) {
      cycle_time = 0;
      symbol_end = false;
      timer1 = millis() - timer;
      if (timer1 >= 150) {
        symbol = symbol + "-";
      }
      if (timer1 < 150) {
        symbol = symbol + ".";
      }
      buttonWasUp = false;
    }
    if (!buttonWasUp) {
      cycle_time += 1;
      if(cycle_time == 30000 && !symbol_end){
      for (int p=0; p <= 40; p++){
        if (symbol == morse_codes[p]){
        Serial.println(symbol);
        byte command = p;  
        radio.write( &command, sizeof(command) );
        symbol_end  = true;
        cycle_time = 0;
        wrong_symbol = false;
                                     }
        else{
          wrong_symbol = true;
        }
                                  }
      symbol = "";
                             } 
       if(cycle_time == 60000 && wrong_symbol){
        byte command = 40;  
        radio.write( &command, sizeof(command) );       
                                                    }                                    
                      }
    noTone(2);
}

//функция приёмника
void receiver_() {
   //перевод строки
  if (i > 15) {
    i = 0;
    j = j + 1;
    if (j > 1) {
    j = 0;
  }
    lcd.setCursor(i, j);
    lcd.print("                ");
  }
   //приём данных
  if ( radio.available() ){
    timer = millis();
    radio.read(&command,sizeof(command));
    Serial.println(command);
    turn_on();
    lcd.setCursor(i, j);
    lcd.print(symbols[command]);
    i++;
                          }
    timer1 = millis() - timer;

    //выключение подсветки
     if (timer1 > 60000 && screen){
      turn_off();
      screen = false;
    }

  }               

void setup() {
  //инициализация пинов кнопок и динамика
  pinMode(2, OUTPUT);//выход для динамика
  pinMode(4, INPUT_PULLUP);//кнопка смены режима работы
  pinMode(3, INPUT_PULLUP);//кнопка набора символов
  pinMode(8, OUTPUT);//дополнительный GND пин
  digitalWrite(8, LOW);
  pinMode(7, OUTPUT);//дополнительный GND пин
  digitalWrite(7, LOW);
  pinMode(6, OUTPUT);//дополнительный GND пин
  digitalWrite(6, LOW);
  //инициализация радио
  radio.begin();
  radio.enableAckPayload();
  radio.openWritingPipe(pipe);
  radio.openReadingPipe(1,pipe); 
  //инициализация последовательного порта
  Serial.begin(9600);
  //инициализация дисплея
  lcd.init();
  lcd.cursor(); 
  delay(2000);
}

void loop() {
  Button_switch = digitalRead(4);
  //Выбор режима работы
  if (!Button_switch){
    delay(100);
    Button_switch = digitalRead(4);
    if (!Button_switch){
      transmitter = !transmitter;
    if (transmitter) {
      if (!screen) {
        turn_on();
        screen = true;
        timer = millis();
        transmitter = !transmitter;
      }
      else{
        radio.stopListening();
        turn_off();
      }
                     }
    if (!transmitter) { 
      radio.startListening(); 
      turn_on();
                     }
                       }
                     }
  
  //режим передатчика                   
  if (transmitter){
    transmitter_();
  }
  
  //режим приёмника
  if (!transmitter){
    receiver_();
  }                  
            }
