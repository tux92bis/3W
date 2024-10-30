/*
#include "3W.h"
#include <Arduino.h>
#include <DHT.h>      // bibliothèque pour le DHT
#include <SD.h>       // bibliothèque pour la carte SD
#include <Wire.h>     // bibliothèque Wire pour le RTC
#include <RTClib.h>   // bibliothèque pour le RTC

int obtenir_donnees() {
  int valeurLDR = analogRead(ldrPin); // Lecture de la photorésistance  // la variable "ldrPin" n'est pas déclarer
  float temperature = dht.readTemperature(); // Lecture de la température   // la variable "dht" n'est pas déclarer
  float humidite = dht.readHumidity(); // Lecture de l'humidité
}

String obtenir_temps() {
  DateTime maintenant = rtc.now();  // Obtenir l'heure actuelle depuis le RTC   // la variable "rtc" n'est pas déclarer
  String temps = String(maintenant.year()) + "-" + String(maintenant.month()) + "-" + String(maintenant.day()) + " " + String(maintenant.hour()) + ":" + String(maintenant.minute()) + ":" + String(maintenant.second());
  return temps;
}

void sauvegarder_donnees_csv(float temperature, float humidite, int luminosite, String temps) {
    File fichierDonnees = SD.open("donnees.csv", FILE_WRITE);
    if (fichierDonnees) {
        fichierDonnees.print(temps);            // Sauvegarder l'heure
        fichierDonnees.print(",");
        fichierDonnees.print(temperature);     // Sauvegarder la température
        fichierDonnees.print(",");
        fichierDonnees.print(humidite);        // Sauvegarder l'humidité
        fichierDonnees.print(",");
        fichierDonnees.println(luminosite);    // Sauvegarder la luminosité
        fichierDonnees.close();
    } else {
        Serial.println("Erreur d'ouverture du fichier");
    }
}
*/
