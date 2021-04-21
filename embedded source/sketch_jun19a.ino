#include <Keyboard.h>

const byte Pin_A = 8;
const byte Pin_B = 9;
const byte Pin_Return = 10;
const byte Pin_Backspace = 11;

const byte interruptPin = 2;
boolean state = true;

void setup() {  
  Serial.begin(9600);
  Keyboard.begin();
  pinMode(Pin_A, INPUT_PULLUP); 
  pinMode(Pin_B, INPUT_PULLUP);
  pinMode(Pin_Return, INPUT_PULLUP);
  pinMode(Pin_Backspace, INPUT_PULLUP);

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), exchange, FALLING);  
}

void loop() {
  if(state==false){
    if(digitalRead(Pin_A) == LOW){
      Keyboard.press('a');
      delay(100);
      Keyboard.releaseAll();
      delay(200);  
    }
    if(digitalRead(Pin_B) == LOW){
      Keyboard.press('b');
      delay(100);
      Keyboard.releaseAll();
      delay(200);  
    }
    if(digitalRead(Pin_Return) == LOW){
      Keyboard.press(KEY_RETURN);
      delay(100);
      Keyboard.releaseAll();
      delay(200);  
    }
    if(digitalRead(Pin_Backspace) == LOW){
      Keyboard.press(KEY_BACKSPACE);
      delay(100);
      Keyboard.releaseAll();
      delay(200);  
    }   
  }
}
void exchange() {
 state=!state;
}
