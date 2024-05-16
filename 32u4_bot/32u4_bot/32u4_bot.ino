#include <Keyboard.h>
//================================================================================================================
// Настройки кнопок.
//================================================================================================================

// Кнопка-точка будет слева.
#define BUTTON_DOT   6
// Кнопка-тире - справа.
#define BUTTON_TIRE  7

int buttons, buttonsPrev; // Здесь будем в виде битовых масок хранить нынешнее и предыдущее состояние клавиш.
#define BUTTON_DOT_MASK   1
#define BUTTON_TIRE_MASK  2

// С помощью этих переменных мы засекаем, когда в последний раз была нажата и отпущена кнопка. Любая. По этому
//  времени мы определяем, завершен ли ввод текущего символа и не пора ли переходить в спящий режим.
unsigned long int timeRelease, timePress;

// Смену состояния кнопки на время менее 0.03с будем считать дребезгом и игнорировать.
#define DEBOUNCING_TIME  30
// В эти переменные будем сохранять время для отфильтровывания дребезга контактов.
unsigned long int timeDotDebouncing;
unsigned long int timeTireDebouncing;

// Максимальная пауза между точками и тире в букве - 0.4 секунды.
//  Если пауза больше - считаем ввод буквы завершенным и переходим к вводу следующей буквы.
#define DELIMITER_TIME  500

//================================================================================================================
// Настройки пьезо-динамика.
//================================================================================================================

#define PIEZO  8
byte piezoData;
unsigned long int piezoShutUpTime;

//================================================================================================================
// Азбука Морзе.
//================================================================================================================

// Этими символами мы будем обозначать точки и тире.
#define MORSE_DOT     '*'
#define MORSE_TIRE    '-'
// Точка или тире пока не введены. 
#define MORSE_EMPTY   0
// Это - для блокировки ввода точек/тире при смене раскладки или выходе из спящего режима.
#define MORSE_LOCKED  '!'

// Максимальная длина символа азбуки Морзе (в точках и тире)
#define MAX_MORSE_SYMBOL_LENGTH  8
// Буфер для записи морзе-символа.
byte morseSymbol[MAX_MORSE_SYMBOL_LENGTH];
unsigned int morseSymbolLen;
byte newMorseSignal; // Новый введенный сигнал - точка или тире.

// Таблица кодов Морзе. N-ный элемент кода соответствует n-ному символу раскладки.
char* code[] = {
  "*-","-***","*--","--*","-**","*","***-","--**","**","*---",
  "-*-","*-**","--","-*","---","*--*","*-*","***","-","**-",
  "**-*","****","-*-*","---*","----","--*-","-*--","-**-","**-**","**--",
  "*-*-",
  "*----","**---","***--","****-","*****","-****","--***","---**","----*","-----",
  "......","*-*-*-","---***","-*-*-","-*--*-","*----*","*-**-*","-****-","-**-*","**--**","--**--",
  "-***-","********","*--*-*","**-*-",
  ""
};

// Латинская раскладка.
char* layoutLatin[] = {
  "a","b","w","g","d","e","v","z","i","j",
  "k","l","m","n","o","p","r","s","t","u",
  "f","h","c","ö","ch","q","y","x","é","ü",
  "ä",
  "1","2","3","4","5","6","7","8","9","0",
  ".",",",":",";","(","\'","\"","-","/","?","!",
  " *DELIMITER* "," *ERR* ","@"," *END* ",
  ""
};

char** currentLayout;
char** newLayout;

//================================================================================================================
// Режимы работы.
//================================================================================================================

#define TYPING_MODE  0
int mode;

//================================================================================================================

void setup() {
   Keyboard.begin();
  Serial.begin(9600);
  // И кнопки, и светодиод у нас работают с инвертированной логикой: кнопка нажата = LOW, отпущена = HIGH,
  //  светодиод горит на полную яркость = LOW, погашен = HIGH. Погасим светодиоды:

  pinMode(PIEZO, OUTPUT);
  digitalWrite(PIEZO, LOW);

  pinMode(BUTTON_DOT, INPUT);
  pinMode(BUTTON_TIRE, INPUT);
  buttons = 0;
  buttonsPrev = 0;
  
  mode = TYPING_MODE;

  morseSymbolLen = 0;

  currentLayout = layoutLatin;
  newLayout = 0;
  newMorseSignal = MORSE_EMPTY;
}

//================================================================================================================
// Работа с пьезо-динамиком
void doPiezo(unsigned long int currentTime) {
  if (currentTime >= piezoShutUpTime) {
    if (piezoShutUpTime > 0) {
      piezoShutUpTime = 0;
      digitalWrite(PIEZO, LOW);
    }
    return;
  }
  piezoData = (piezoData == LOW) ? HIGH : LOW;
  digitalWrite(PIEZO, piezoData);
}

void playPiezo(unsigned long int t, unsigned long int currentTime) {
  piezoShutUpTime = currentTime + t;
}

//================================================================================================================
// Считывание состояния кнопки с учетом возможного дребезга контактов.
int getButtonState(int btnPrevState, int BUTTON_PIN, unsigned long int* timeDebouncing, unsigned long int currentTime) {
  int btnState = digitalRead(BUTTON_PIN);
  
  if (btnState == HIGH) {
    if (btnPrevState == LOW) {
      if (*timeDebouncing == 0) {
        // Засечем время, которое кнопка будет нажата - чтобы не спутать дребезг контактов с нажатием.
        *timeDebouncing = currentTime;
        // Пока не воспринимаем нажатие, считая его дребезгом контактов.
        btnState = LOW;
      } else {
        if ((currentTime - *timeDebouncing) < DEBOUNCING_TIME) {
          // Пока не воспринимаем нажатие, считая его дребезгом контактов.
          btnState = LOW;
        } else {
          // Это не дребезг контактов, это реальное нажатие кнопки.
          btnState = HIGH;
          *timeDebouncing = 0;
        }
      }
    } else {
      *timeDebouncing = 0;
    }
  } else {
    if (btnPrevState == HIGH) {
      if (*timeDebouncing == 0) {
        // Засечем время, которое кнопка будет нажата - чтобы не спутать дребезг контактов с нажатием.
        *timeDebouncing = currentTime;
        // Пока не воспринимаем отпускание, считая его дребезгом контактов.
        btnState = HIGH;
      } else {
        if ((currentTime - *timeDebouncing) < DEBOUNCING_TIME) {
          // Пока не воспринимаем отпускание, считая его дребезгом контактов.
          btnState = HIGH;
        } else {
          // Это не дребезг контактов, это реальное отпукание кнопки.
          btnState = LOW;
          *timeDebouncing = 0;
        }
      }
    } else {
      *timeDebouncing = 0;
    }
  }
  
  return btnState;
}

//================================================================================================================
// Отправим на компьютер введенный символ.
void sendMorseSymbol() {
  int i, j;
  if (morseSymbolLen < 1) {
    return;
  }
  playPiezo(50, millis());
  for (i = 0; code[i][0] != '\0'; i++) {
    // Сравним введенный символ с символами из таблицы кодов Морзе.
    for (j = 0; (j < morseSymbolLen) && (code[i][j] != '\0'); j++) {
      if (code[i][j] != morseSymbol[j]) {
        j = -1;
        break;
      }
    }
    if ((j != -1) && (j == morseSymbolLen) && (code[i][j]=='\0')) {
      // Символ из таблицы кодов Морзе соответствует введенному символу.
      //  Отправим символ на компьютер.
      Serial.print(currentLayout[i]);
      morseSymbolLen = 0;
      return;
    }
  }
  // Символ в таблице не найден. Напечатаем нераспознанный символ.
  Serial.print(" [");
  for (i = 0; i < morseSymbolLen; i++) {
    Serial.print(morseSymbol[i]);
  }
  Serial.print("] ");
  morseSymbolLen = 0;
}

//================================================================================================================
// Режим печати

void typingLoop() {
  unsigned long int t, dt; // Эти пременные будем использовать для замеров времени.
  int btnDotState, btnTireState;  // В эти переменные считаем состояния кнопок. В принципе, их можно было бы сразу
                                  //  занести в переменную buttons, но так код будет понятнее.

//  analogWrite(PIEZO, 0);

  t = millis();
  // Не забываем, что у нас логика инвертирована, и нажатая кнопка - это LOW.
  btnDotState = getButtonState((buttonsPrev & BUTTON_DOT_MASK) ? LOW : HIGH, BUTTON_DOT, &timeDotDebouncing, t);
  btnTireState = getButtonState((buttonsPrev & BUTTON_TIRE_MASK) ? LOW : HIGH, BUTTON_TIRE, &timeTireDebouncing, t);
  buttons = ((btnDotState == LOW) ? BUTTON_DOT_MASK : 0) | ((btnTireState == LOW) ? BUTTON_TIRE_MASK : 0);
  Serial.print(buttons);
  Serial.print(" - ");
  Serial.println(buttonsPrev);
  if (buttons == 0) {
                     // Обе кнопки отпущены, можно добавить введенную точку, тире или переключить раскладку.
                      // Если пауза дольше DELIMITER_TIME - отправим символ.
                      if (buttonsPrev != 0) {Serial.println("buttonsPrev != 0");
                                             timeRelease = t;
                                             buttonsPrev = 0;
                                             }
                        switch (newMorseSignal) {
                                                                        case MORSE_DOT:
                                                                         case MORSE_TIRE:
                                                                        morseSymbol[morseSymbolLen++] = newMorseSignal;
                                                                        break; // MORSE_DOT, MORSE_TIRE
                                                                         }
                      newMorseSignal = MORSE_EMPTY;
                      dt = t - timeRelease;
    
    //sendMorseSymbol();
    Serial.print(t);
    Serial.print(" - ");
    Serial.print(timeRelease);
    Serial.print(" = ");
    Serial.println(dt);
                      if ((morseSymbolLen > 0) && (dt > DELIMITER_TIME)) {
                                                                          sendMorseSymbol();
                                                                           } 
                    } else 
                                                                 //===================================================================
                                                                switch (buttons) {
                                                                                   case BUTTON_DOT_MASK:
                                                                                    if (newMorseSignal == MORSE_EMPTY) {
                                                                                                                        // Нажата "точка".
                                                                                                                        newMorseSignal = MORSE_DOT;
                                                                                                                        timePress = t;
                                                                                                                        }
                                                                                    break; // BUTTON_DOT_MASK
    
                                                                                    case BUTTON_TIRE_MASK:
                                                                                    if (newMorseSignal == MORSE_EMPTY) {
                                                                                                                        // Нажато "тире".
                                                                                                                        newMorseSignal = MORSE_TIRE;
                                                                                                                        timePress = t;
                                                                                                                         }
                                                                                    break; // BUTTON_DOT_MASK
                                                                                  }
                                                                 //==================================================================
  //buttonsPrev = buttons;
  delay(10);                                         
                    }                                               
//================================================================================================================
void doAction () {
  Keyboard.print("Test.");
  delay(2000);
}

// Главный цикл.
void loop() {
  switch(mode) {
    case TYPING_MODE:
      typingLoop();
      delay(300);
      break;
  }
}



