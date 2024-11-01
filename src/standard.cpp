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

#include <SD.h>
#include <SPI.h>

int intervalNormal = 1000;
int intervalEco = 2000; en ms

struct GPSetDate_t {
  float latitude;
  float longitude;
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
};

struct DHT_t {
  float humidity;
  float temperatureC;
  float temperatureF;
  float heatIndexC;
  float heatIndexF;
};

struct Donnee {
  GPSetDate_t GPSetDate;
  int LRD;
  DHT_t DHT;
};

// Fonction pour enregistrer les données dans un fichier CSV
void enregistrerDonnee(const Donnee& data) {
  File dataFile = SD.open("data_log.csv", FILE_WRITE);
  
  if (dataFile) {
    // Écrit les données GPS sous forme de CSV
    dataFile.print(data.GPSetDate.latitude, 6);    // Latitude avec 6 décimales
    dataFile.print(",");
    dataFile.print(data.GPSetDate.longitude, 6);   // Longitude avec 6 décimales
    dataFile.print(",");
    dataFile.print(data.GPSetDate.year);           // Année
    dataFile.print("/");
    dataFile.print(data.GPSetDate.month);          // Mois
    dataFile.print("/");
    dataFile.print(data.GPSetDate.day);            // Jour
    dataFile.print(",");
    if (data.GPSetDate.hour < 10) dataFile.print("0");
    dataFile.print(data.GPSetDate.hour);           // Heure
    dataFile.print(":");
    if (data.GPSetDate.minute < 10) dataFile.print("0");
    dataFile.print(data.GPSetDate.minute);         // Minute
    dataFile.print(":");
    if (data.GPSetDate.second < 10) dataFile.print("0");
    dataFile.print(data.GPSetDate.second);         // Seconde

    // Écrit la valeur LRD
    dataFile.print(",");
    dataFile.print(data.LRD);

    // Écrit les données du capteur DHT sous forme de CSV
    dataFile.print(",");
    dataFile.print(data.DHT.humidity);             // Humidité
    dataFile.print(",");
    dataFile.print(data.DHT.temperatureC);         // Température en Celsius
    dataFile.print(",");
    dataFile.print(data.DHT.temperatureF);         // Température en Fahrenheit
    dataFile.print(",");
    dataFile.print(data.DHT.heatIndexC);           // Indice de chaleur en Celsius
    dataFile.print(",");
    dataFile.println(data.DHT.heatIndexF);         // Indice de chaleur en Fahrenheit

    dataFile.close();                              // Ferme le fichier après écriture
    Serial.println("Données enregistrées.");
  } else {
    Serial.println("Erreur d'écriture dans le fichier data_log.csv");
  }
}


void loop() {

  int interval = modeEco ? intervalEco : intervalNormal;

  // Vérifier si l'intervalle est écoulé
  if (millis() - previousMillis >= interval) {
    previousMillis = millis(); // Mettre à jour le dernier temps

  // Exemple de données GPS et DHT à enregistrer
    GPSetDate_t gpsData = {30.236640, -97.821453, 2023, 11, 1, 14, 30, 25};
    DHT_t dhtData = {55.5, 22.5, 72.5, 24.0, 75.2};
    int LRD = 100; // Exemple de valeur pour LRD

    Donnee data = {gpsData, LRD, dhtData};

    // Appel de la fonction pour enregistrer les données
    enregistrerDonnee(data);
  
}







