#include <EEPROM.h>
#include <Arduino.h>
#include "3W.h"
#include <LiquidCrystal.h>  /* Pour l'écran LCD */
#include <Wire.h>           /* Pour l'horloge RTC */
#include <RTClib.h>         /* Pour la bibliothèque RTC */
#include <LED_RVB.h>        /* Bibliothèque pour gérer la LED RVB */

extern LiquidCrystal lcd;  /* L'écran LCD
extern LED_RVB ledRVB;     /* LED RVB pour les indicateurs de mode */
extern RTC_DS1307 rtc;     /* RTC pour gérer l'horloge */

// Variables des paramètres de configuration
int logInterval = 10;      // Intervalle de mesure (en minutes)
int fileMaxSize = 4096;    // Taille maximale du fichier de log (en octets)
int timeout = 30;          // Timeout des capteurs (en secondes)
int lumin = 1;             // Activation du capteur de luminosité
int luminLow = 255;        // Seuil bas pour la luminosité
int luminHigh = 768;       // Seuil haut pour la luminosité
unsigned long lastActivityTime = 0; // Pour surveiller l'inactivité

// Sauvegarde des paramètres dans l'EEPROM
void saveToEEPROM() {
    EEPROM.put(0, logInterval);
    EEPROM.put(4, fileMaxSize);
    EEPROM.put(8, timeout);
    EEPROM.put(12, lumin);
    EEPROM.put(16, luminLow);
    EEPROM.put(20, luminHigh);
}

// Réinitialiser les paramètres par défaut
void resetToDefaults() {
    logInterval = 10;
    fileMaxSize = 4096;
    timeout = 30;
    lumin = 1;
    luminLow = 255;
    luminHigh = 768;
    saveToEEPROM();
    Serial.println("Paramètres réinitialisés aux valeurs par défaut.");
}

// Fonction de configuration
void modeConfig() {
    lcd.clear();
    lcd.print("Mode Config actif");
    ledRVB.setColor(255, 255, 0);  // LED jaune continue pour le mode configuration
    Serial.println("=== Mode Configuration ===");
    Serial.println("Commandes disponibles : ");
    Serial.println("LOG_INTERVAL=x (en minutes)");
    Serial.println("FILE_MAX_SIZE=x (en octets)");
    Serial.println("TIMEOUT=x  (en secondes)");
    Serial.println("LUMIN=x  (activation 1/0)");
    Serial.println("LUMIN_LOW=x (seuil bas de luminosité)");
    Serial.println("LUMIN_HIGH=x (seuil haut de luminosité)");
    Serial.println("RESET (réinitialise les valeurs par défaut)");
    Serial.println("VERSION (affiche la version du programme)");
    Serial.println("CLOCK (configurer l'heure)");
    Serial.println("DATE (configurer la date)");
    lastActivityTime = millis();  // Réinitialiser le compteur d'inactivité

    while (true) {
        if (Serial.available()) {
            String input = Serial.readStringUntil('\n');  // Lecture de la commande entrée
            input.trim();  // Enlever les espaces superflus

            // Commande LOG_INTERVAL
            if (input.startsWith("LOG_INTERVAL=")) {
                logInterval = input.substring(input.indexOf('=') + 1).toInt();
                Serial.print("Nouvel intervalle de mesure : ");
                Serial.println(logInterval);
            }
            // Commande FILE_MAX_SIZE
            else if (input.startsWith("FILE_MAX_SIZE=")) {
                fileMaxSize = input.substring(input.indexOf('=') + 1).toInt();
                Serial.print("Nouvelle taille maximale du fichier : ");
                Serial.println(fileMaxSize);
            }
            // Commande TIMEOUT
            else if (input.startsWith("TIMEOUT=")) {
                timeout = input.substring(input.indexOf('=') + 1).toInt();
                Serial.print("Nouveau timeout pour les capteurs : ");
                Serial.println(timeout);
            }
            // Commande LUMIN
            else if (input.startsWith("LUMIN=")) {
                lumin = input.substring(input.indexOf('=') + 1).toInt();
                Serial.print("Activation du capteur de luminosité : ");
                Serial.println(lumin);
            }
            // Commande LUMIN_LOW
            else if (input.startsWith("LUMIN_LOW=")) {
                luminLow = input.substring(input.indexOf('=') + 1).toInt();
                Serial.print("Nouveau seuil bas de luminosité : ");
                Serial.println(luminLow);
            }
            // Commande LUMIN_HIGH
            else if (input.startsWith("LUMIN_HIGH=")) {
                luminHigh = input.substring(input.indexOf('=') + 1).toInt();
                Serial.print("Nouveau seuil haut de luminosité : ");
                Serial.println(luminHigh);
            }
            // Commande RESET
            else if (input.equalsIgnoreCase("RESET")) {
                resetToDefaults();
            }
            // Commande VERSION
            else if (input.equalsIgnoreCase("VERSION")) {
                Serial.println("Version 1.0.0 - Lot #12345");
            }
            // Commande CLOCK pour régler l'heure
            else if (input.startsWith("CLOCK=")) {
                String timeStr = input.substring(input.indexOf('=') + 1);
                int hour = timeStr.substring(0, 2).toInt();
                int minute = timeStr.substring(3, 5).toInt();
                int second = timeStr.substring(6, 8).toInt();
                DateTime now = rtc.now();
                rtc.adjust(DateTime(now.year(), now.month(), now.day(), hour, minute, second));
                Serial.println("Heure réglée.");
            }
            // Commande DATE pour régler la date
            else if (input.startsWith("DATE=")) {
                String dateStr = input.substring(input.indexOf('=') + 1);
                int year = dateStr.substring(0, 4).toInt();
                int month = dateStr.substring(5, 7).toInt();
                int day = dateStr.substring(8, 10).toInt();
                DateTime now = rtc.now();
                rtc.adjust(DateTime(year, month, day, now.hour(), now.minute(), now.second()));
                Serial.println("Date réglée.");
            }
            // Si la commande n'est pas reconnue
            else {
                Serial.println("Commande non reconnue.");
            }

            // Sauvegarder les nouveaux paramètres
            saveToEEPROM();
            lastActivityTime = millis();  // Réinitialiser le compteur d'inactivité après chaque commande
        }

        // Vérifier si 30 minutes d'inactivité sont écoulées
        if (millis() - lastActivityTime >= 1800000) {  // 30 minutes = 1800000 ms
            Serial.println("Inactivité détectée. Retour au mode standard.");
            ledRVB.setColor(0, 255, 0);  // LED verte pour indiquer le mode standard
            break;  // Sortir du mode configuration
        }
    }
}
