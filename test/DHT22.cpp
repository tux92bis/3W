#include <DHT.h>

const int CAPTEUR_TEMP = 2;

float t, h;

DHT dht(CAPTEUR_TEMP, DHT22);

void setup()
{
  Serial.begin(9600);
  dht.begin();
}

void loop()
{
  t = dht.readTemperature();
  h = dht.readHumidity();
}