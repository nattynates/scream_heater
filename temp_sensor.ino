//#include "DHT.h"

//#define DHTPIN 2     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.
//#define DHTTYPE DHT11   // DHT 11
int smallSensor = A0;

//DHT dht(DHTPIN, DHTTYPE);

float val = 0;

void setup() {
  Serial.begin(9600);
  //dht.begin();
  pinMode(A0, INPUT);
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  //float t = dht.readTemperature();

  val = analogRead(smallSensor);
  val = val*(5.0/1024.0);
  val = (val - 0.5)*100;
  
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  /*if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;*/

    // Compute heat index in Fahrenheit (the default)
 // float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  //float hic = dht.computeHeatIndex(t, h, false);

 // Serial.print(F("Humidity: "));
 // Serial.print(h);
 //Serial.print(F("%  Blue sensor: "));
 //Serial.print(t);
 // Serial.println(F("°C "));
  Serial.print(F("%  Small sensor: "));
  Serial.print(val);
  Serial.println(F("°C "));
//  Serial.print(f);
//  Serial.print(F("°F  Heat index: "));
//  Serial.print(hic);
//  Serial.print(F("°C "));
//  Serial.print(hif);
//  Serial.println(F("°F"));
}
  


