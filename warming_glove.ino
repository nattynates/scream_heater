#include <LiquidCrystal.h>

//Pin values
const int relayPin = 10;
const int switchPin = 9;
const int microphonePin = A0;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

//Constants
const int volumeThreshold1 = 8;
const int volumeThreshold2 = 15;
const int volumeThreshold3 = 28;
const int volumeThreshold4 = 38;
const int volumeThreshold5 = 50;

//Constructors
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//LCD characters
byte powerBar[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

byte emptyShellLeft[8] = {
  0b11111,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b11111
};

byte emptyShellMiddle[8] = {
  0b11111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111
};

byte emptyShellRight[8] = {
  0b11111,
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b11111
};

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(switchPin, INPUT);

  Serial.begin(9600);

  lcd.createChar(0, powerBar);
  lcd.createChar(1, emptyShellLeft);
  lcd.createChar(2, emptyShellMiddle);
  lcd.createChar(3, emptyShellRight);
  lcd.begin(16, 2);
}

void loop() {
  //turn on LCD
  lcd.display();

  //switch is in "|" on mode
  if (digitalRead(switchPin)) {
    float micData = getMicrophoneData();
    Serial.println(micData);

    //Turning on the heat plate
    if (micData > volumeThreshold5) {
      setLCD("MAXIMUM POWER");
      PowerBarEmptyShell();
      lcd.setCursor(7, 1);
      lcd.write(byte(0));
      lcd.setCursor(8, 1);
      lcd.write(byte(0));
      lcd.setCursor(9, 1);
      lcd.write(byte(0));
      lcd.setCursor(10, 1);
      lcd.write(byte(0));
      lcd.setCursor(11, 1);
      lcd.write(byte(0));
      setHeatPlate(true);
    }
        else if (micData > volumeThreshold4) {
      setLCD("MOORREEEEE");
      PowerBarEmptyShell();
      lcd.setCursor(7, 1);
      lcd.write(byte(0));
      lcd.setCursor(8, 1);
      lcd.write(byte(0));
      lcd.setCursor(9, 1);
      lcd.write(byte(0));
      lcd.setCursor(10, 1);
      lcd.write(byte(0));
      setHeatPlate(true);
    }
    else if (micData > volumeThreshold3) {
      setLCD("I HEARD A RUSTLE");
      PowerBarEmptyShell();
      lcd.setCursor(7, 1);
      lcd.write(byte(0));
      lcd.setCursor(8, 1);
      lcd.write(byte(0));
      lcd.setCursor(9, 1);
      lcd.write(byte(0));
      setHeatPlate(true);
    }
    else if (micData > volumeThreshold2) {
      lcd.print("THAT ALL YOU GOT");
      PowerBarEmptyShell();
      lcd.setCursor(7, 1);
      lcd.write(byte(0));
      lcd.setCursor(8, 1);
      lcd.write(byte(0));
      setHeatPlate(true);
    }
    else if (micData > volumeThreshold1) {
      setLCD("SCREAM LOUDER");
      PowerBarEmptyShell();
      lcd.setCursor(7, 1);
      lcd.write(byte(0));
      setHeatPlate(true);
    }
    
    //turning off the heat plate
    else {
      setLCD("scream you wimp");
      PowerBarEmptyShell();
      setHeatPlate(false);
    }
  }
  //Switch is in "O" off mode
  else {
    setHeatPlate(false);
    PowerBarEmptyShell();
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

void PowerBarEmptyShell() {
    lcd.setCursor(0, 1);
    lcd.print("Power: ");
    lcd.setCursor(7, 1);
    lcd.write(byte(1));
    lcd.setCursor(8, 1);
    lcd.write(byte(2));
    lcd.setCursor(9, 1);
    lcd.write(byte(2));
    lcd.setCursor(10, 1);
    lcd.write(byte(2));
    lcd.setCursor(11, 1);
    lcd.write(byte(3));
}
