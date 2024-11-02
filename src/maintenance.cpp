#include "3W.h" // Inclusion du fichier en-tête
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Wire.h>
#include <SD.h>

extern int modeCourant;      // Mode courant défini dans main.cpp
extern Capteurs capteurs;    // Structure des capteurs
extern bool ecritureSD;      // Variable pour gérer l'écriture sur la SD

// Fonction pour passer en mode maintenance
void modeMaintenance() {
    // Création de l'objet LCD
    LiquidCrystal_I2C lcd(0x27, 16, 2);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Mode Maintenance");
    Serial.println("Mode Maintenance actif");

    // Désactiver l'écriture sur la carte SD
    ecritureSD = false;
    Serial.println("Écriture sur la carte SD désactivée. Vous pouvez retirer la carte SD en toute sécurité.");
    lcd.setCursor(0, 1);
    lcd.print("Écriture désactivée");

    // Lire les données du fichier `data.csv` sur la carte SD et les envoyer via le port série
    File dataFile = SD.open("data.csv");
    if (dataFile) {
        Serial.println("Lecture des données enregistrées sur la carte SD :");
        while (dataFile.available()) {
            String line = dataFile.readStringUntil('\n');
            Serial.println(line);  // Envoi de chaque ligne au port série
            delay(500);  // Délai pour une lecture plus lente
        }
        dataFile.close();
    } else {
        Serial.println("Erreur : impossible d'ouvrir le fichier data.csv");
    }

    // Attendre la sortie du mode maintenance
    while (modeCourant == MAINTENANCE) {
        delay(100);  // Éviter une boucle trop rapide
    }

    // Réactiver l'écriture sur la carte SD
    Serial.println("Mode maintenance terminé. Vous pouvez replacer la carte SD.");
    ecritureSD = true;
}