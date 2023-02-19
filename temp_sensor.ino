#include "DHT.h"

#define DHTPIN 2     
#define DHTTYPE DHT11   // DHT 11
int smallSensor = A0;

DHT dht(DHTPIN, DHTTYPE);

float val = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(A0, INPUT);
}

void loop() {
  delay(2000);

  float t = dht.readTemperature();

  val = analogRead(smallSensor);
  val = val*(5.0/1024.0);
  val = (val - 0.5)*100;

 Serial.print(F("%  Blue sensor: "));
 Serial.print(t);
 Serial.println(F("°C "));
 Serial.print(F("%  Small sensor: "));
 Serial.print(val);
 Serial.println(F("°C "));
}
  


