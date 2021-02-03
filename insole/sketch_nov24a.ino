#include<SD.h>
#include<SPI.h>
//#include <SoftwareSerial.h>
//#define BT_RXD 0
//#define BT_TXD 1
//SoftwareSerial bluetooth(8, 9);

File myFile;
int CS_PIN = 10;
int fname = 0, button = 0;
unsigned long time = 0;
extern volatile unsigned long timer0_millis;
int buttonPushCounter = -1;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

void setup() {
  Serial.begin(9600);
  while (!Serial);
  pinMode(CS_PIN, OUTPUT);
  pinMode(2, INPUT);
  //bluetooth.begin(9600);
}

void loop() {
  time = millis();
  buttonState = digitalRead(2);
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      buttonPushCounter++;
    }
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;
  //Serial.println(String(time) + "," + String(analogRead(A0)) + "," + String(analogRead(A1)));

  switch (buttonPushCounter) {
    case 1:
      initializeSD();
      createFile(String(fname++) + ".txt");
      buttonPushCounter++;
      timer0_millis=0;
      break;
    case 2:
      if (time%20==0){
        writeToFile(String(time) + "," + String(analogRead(A0)) + "," + String(analogRead(A1)));
        delay(1);
      }
      break;
    case 3:
      Serial.println("end");
      myFile.close();
      buttonPushCounter =0;
      break;
  }
}

void initializeSD() {
  Serial.println("Initializing SD card...");
  pinMode(10, OUTPUT);
  if (SD.begin()) {
    Serial.println("SD card is ready to use.");
    delay(1000);
  } else {
    Serial.println("SD card initialization failed");
    return;
  }
}

int createFile(String filename) {
  myFile = SD.open(filename, FILE_WRITE);
  if (myFile) {
    //Serial.println("File created successfully.");
    return 1;
  } else {
    Serial.println("Error while creating file.");
    return 0;
  }
}

int writeToFile(String data) {
  if (myFile) {
    myFile.println(data);
    //Serial.println(data);
    return 1;
  } else {
    Serial.println("Couldn't write to file");
    return 0;
  }
}
