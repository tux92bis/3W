/*
#include "3W.h"
#include <Arduino.h>
//#include <DHT.h>
#include <SD.h>
//#include <Wire.h>
//#include <RTClib.h>

//#define ldrPin A0   // broche pour lire les données de la luminosité
DHT dht(2, DHT22);    // broche + modèle du DHT
RTC_DS3231 rtc;   // modèle du RTC


DonneesCapteur obtenir_donnees() {
  DonneesCapteur data;
  data.luminosite = analogRead(ldrPin);
  data.temperature = dht.readTemperature();
  data.humidite = dht.readHumidity();
  return data;
}


String obtenir_temps() {
  DateTime maintenant = rtc.now();
  String temps = String(maintenant.year()) + "-" + String(maintenant.month()) + "-" + String(maintenant.day()) + " " + String(maintenant.hour()) + ":" + String(maintenant.minute()) + ":" + String(maintenant.second());
  return temps;
}


void sauvegarder_donnees_csv(float temperature, float humidite, int luminosite, String temps) {
    File fichierDonnees = SD.open("donnees.csv", FILE_WRITE);
    if (fichierDonnees) {
        fichierDonnees.print(temps);
        fichierDonnees.print(",");
        fichierDonnees.print(temperature);
        fichierDonnees.print(",");
        fichierDonnees.print(humidite);
        fichierDonnees.print(",");
        fichierDonnees.println(luminosite);
        fichierDonnees.close();
    } else {
        Serial.println("Erreur d'ouverture du fichier");
    }
}
*/


/*
void setup() {
    Serial.begin(9600);
    dht.begin();
    SD.begin(4);
    if (!rtc.begin()) {
        Serial.println("Erreur : le RTC n'est pas trouvé !");
        while (1);
    }
}


void loop() {
    DonneesCapteur data = obtenir_donnees();
    String temps = obtenir_temps();
    sauvegarder_donnees_csv(data.temperature, data.humidite, data.luminosite, temps);
    delay(2000);
}
*/


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


#include "3W.h"
#include <SD.h>
#include <SPI.h>
#include <RTClib.h>


int intervalNormal = 1000;
int intervalEco = 2000;   //en ms

/*
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
*/

// Fonction pour enregistrer les données dans un fichier CSV
void modeStandard() {
  File dataFile = SD.open("data.csv", FILE_WRITE);
  lcd.clear();
  lcd.setCursor(10,1);
  lcd.print("L: ");
  lcd.print(analogRead(A0));
  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.print(dht.readTemperature());
  lcd.setCursor(0, 1);
  lcd.print("H: ");
  lcd.print(dht.readHumidity());
  Serial.println(dht.readTemperature());
  Serial.println(dht.readHumidity());

  
    // Écrit les données GPS sous forme de CSV
    dataFile.print(48.900047);    // Latitude avec 6 décimales
    dataFile.print(",");
    dataFile.print(2.194916);   // Longitude avec 6 décimales
    dataFile.print(",");
    // Convert DateTime to string
    DateTime now = rtc.now();
    char dateString[20];
    sprintf(dateString, "%04d-%02d-%02d %02d:%02d:%02d", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
    dataFile.print(dateString);
    // Écrit la valeur LRD                   // LRD
    dataFile.print(",");
    dataFile.print(analogRead(A0));

    // Écrit les données du capteur DHT sous forme de CSV
   dataFile.print(",");
    dataFile.print(dht.readHumidity());             // Humidité
    dataFile.print(",");
    dataFile.print(dht.readTemperature());         // Température en Celsius
    dataFile.print(",");
    dataFile.close();                            // Ferme le fichier après écriture
   
}



/*
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
*/
