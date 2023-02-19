#include <LiquidCrystal.h>

//Pin values
const int relayPin = 2;
const int switchPin = 4;
const int microphonePin = A0;

//Constants
const int volumeThreshold1 = 8;
const int volumeThreshold2 = 15;
const int volumeThreshold3 = 23;
const int volumeThreshold4 = 30;
const int volumeThreshold5 = 39;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(switchPin, INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("scream you wimp");

}

void loop() {
  //turn on LCD
  lcd.display();

  float micData = getMicrophoneData();
  Serial.println(micData);

  //Turning on the heat plate
  if (micData > volumeThreshold1) {
    setLCD("SCREAM LOUDER");
    setHeatPlate(true);
  }
  else if (micData > volumeThreshold2) {
    lcd.print("THAT ALL YOU GOT");
    setHeatPlate(true);
  }
  else if (micData > volumeThreshold3) {
    setLCD("I HEARD A RUSTLE")
    setHeatPlate(true);
  }
  //turning off the heat plate
  else {
    setLCD("scream you wimp");
    setHeatPlate(false);
  }

  delay(250);
}

float getMicrophoneData() {
  float mn = 1024;
  float mx = 0;
  for (int i = 0; i < 100; ++i) {
    float val = analogRead(microphonePin);
    mn = min(mn, val);
    mx = max(mx, val);
  }
  float delta = mx - mn;
  return delta;
}

void setLCD(String msg) {
  lcd.clear();
  lcd.print(msg);
}

void setHeatPlate(bool mode) {
  if (mode) {
    digitalWrite(relayPin, HIGH);
  } 
  else {
    digitalWrite(relayPin, LOW);
  }
}
