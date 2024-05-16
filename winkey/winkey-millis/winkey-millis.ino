#define BUTTON_DOT 3
#define BUTTON_TIRE 2
#define OUTPORT 4
#define BEEPER 5

unsigned int key, keyflag, MorseSignal, DotMemory, TireMemory, pad, oldMorseSignal;
unsigned int cwspeed = 80;
unsigned long int t;
unsigned int FLAG =0;

void setup(){
  Serial.begin(9600);
  pinMode(BUTTON_DOT, INPUT_PULLUP);
  pinMode(BUTTON_TIRE, INPUT_PULLUP);
  pinMode(A1, INPUT);
  pinMode(OUTPORT, OUTPUT);
  pinMode(BEEPER, OUTPUT); 
}

void speedset(){
 if (key>925 && key<930){if (!keyflag){keyflag=1;cwspeed=cwspeed-1;if (cwspeed==0){cwspeed=cwspeed+1;};};}
 if (key>985 && key<995){if (!keyflag){keyflag=1;cwspeed=cwspeed+1;if (cwspeed==1023){cwspeed=cwspeed-1;};};}
}

void loop (){
key=analogRead(A1);
if (key>4) {speedset();} else {keyflag=0;}
//--------------------------------------------------------
pad=0;
if (!digitalRead(BUTTON_DOT)) {pad=1;}
if (!digitalRead(BUTTON_TIRE)) {pad=2;}
if (!digitalRead(BUTTON_DOT) && !digitalRead(BUTTON_TIRE)) {pad=3;}
//--------------------------------------------------------
if (FLAG) {
          switch (pad){                    
                       case 1: {if (oldMorseSignal==2){DotMemory=1;}
                               break;
                               }
                       case 2: {if (oldMorseSignal==1){TireMemory=1;}
                               break;
                               }
                       break;       
                       }
          }
else      {if (!DotMemory or !TireMemory){
           switch (pad){                    
                       case 1: {FLAG=1;
                               t=millis();
                               analogWrite(BEEPER,128);
                               MorseSignal=1;
                               oldMorseSignal=MorseSignal; 
                               break;
                               }
                       case 2: {FLAG=1;
                               t=millis();
                               analogWrite(BEEPER,128);
                               MorseSignal=2;
                               oldMorseSignal=MorseSignal; 
                               break;
                               }
                       case 3: {FLAG=1;
                               t=millis();
                               analogWrite(BEEPER,128);
                               if (oldMorseSignal==1){MorseSignal=2;}else{MorseSignal=1;}
                               oldMorseSignal=MorseSignal; 
                               break;
                               }
                       break;        
                       }  }
           }
           
//--------------------------------------------------------
if (DotMemory){
               if (MorseSignal==0){FLAG=1;
                                   t=millis();
                                   analogWrite(BEEPER,128);
                                   MorseSignal=1;
                                   oldMorseSignal=MorseSignal;
                                   DotMemory=0;
                                   }
                }
if (TireMemory){
               if (MorseSignal==0){FLAG=1;
                                   t=millis();
                                   analogWrite(BEEPER,128);
                                   MorseSignal=2;
                                   oldMorseSignal=MorseSignal;
                                   TireMemory=0;
                                   }
                }
switch (MorseSignal){
                     case 1:if (millis()>t+(cwspeed*2)){FLAG=0; Serial.print(MorseSignal);  MorseSignal=0; break;} 
                            if (millis()>t+cwspeed)    {analogWrite(BEEPER,0); break;}
                     case 2:if (millis()>t+(cwspeed*4)){FLAG=0;  Serial.print(MorseSignal); MorseSignal=0; break;}    
                            if (millis()>t+(cwspeed*3)){analogWrite(BEEPER,0);  break;}
                     break;             
                     }
//-----------------------------------------------------------

}

