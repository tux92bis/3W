#include <Wire.h>
#define ADRESSE_I2C_RTC 0x68

byte toBcd(byte val) { return ((val / 10) << 4) + (val % 10); }

// Indiquez ici l'heure et la date de départ souhaitées
byte seconde = 0;     // 0 à 59
byte minute = 30;     // 0 à 59
byte heure = 10;      // 0 à 23
byte jour = 7;        // 1 à 7 (dimanche)
byte date = 3;        // 1 à 31
byte mois = 11;       // 1 à 12 (novembre)
byte annee = 24;      // 0 à 99 (2024)

void setup() {
  Wire.begin();
  Wire.beginTransmission(ADRESSE_I2C_RTC);
  Wire.write(0); // Pointeur de registre sur 00h
  Wire.write(toBcd(seconde));
  Wire.write(toBcd(minute));
  Wire.write(toBcd(heure));
  Wire.write(toBcd(jour));
  Wire.write(toBcd(date));
  Wire.write(toBcd(mois));
  Wire.write(toBcd(annee));
  Wire.endTransmission();
}

void loop() {
}