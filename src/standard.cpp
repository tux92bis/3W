#include <Arduino.h>
#include "3W.h"


int obtenir_donnees() {
  int valeurLDR = analogRead(ldrPin); // Lecture de la photorésistance 
  float temperature = dht.readTemperature(); // Lecture de la température
  float humidite = dht.readHumidity(); // Lecture de l'humidité
}

String obtenir_temps() {
  DateTime maintenant = rtc.now();  // Obtenir l'heure actuelle depuis le RTC
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
