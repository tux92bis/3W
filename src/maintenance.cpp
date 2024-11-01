#include "3W.h" // Inclusion du fichier en-tête
#include <RTClib.h>
#include <LiquidCrystal.h>
#include <DHT.h>

extern int modeCourant;      // Mode courant défini dans main.cpp
extern Capteurs capteurs;    // Structure des capteurs
extern bool ecritureSD;      // Variable pour gérer l'écriture sur la SD

Capteurs get_data() {
    Capteurs data;
    data.lumiere = analogRead(PHOTORESISTANCE);
    data.temperatureAir = dht.readTemperature();
    data.hygrometrie = dht.readHumidity();
    return data;
}

String get_time() {
    DateTime now = rtc.now();
    String time = String(now.year()) + "-" + String(now.month()) + "-" + String(now.day()) + " " +
                  String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
    return time;
}

// Fonction pour passer en mode maintenance
void modeMaintenance() {
    lcd.clear();
    lcd.print("Mode Maintenance");
    Serial.println("Mode Maintenance actif");

    // Arrêter l'écriture sur la carte SD
	ecritureSD= false;
    Serial.println("Écriture sur la carte SD désactivée. Vous pouvez retirer la carte SD en toute sécurité.");
	lcd.println("Écriture désactivé");

    while (modeCourant == MAINTENANCE) {
        // Lire les données des capteurs
        capteurs = get_data();
        String time = get_time();

        // Envoyer les données des capteurs au port série sous format CSV
        Serial.print(time);
        Serial.print(",");
        Serial.print(capteurs.temperatureAir);
        Serial.print(",");
        Serial.print(capteurs.hygrometrie);
        Serial.print(",");
        Serial.println(capteurs.lumiere);

        delay(1000);  // Attente d'une seconde entre chaque lecture
    }

    // Une fois que l'on quitte le mode maintenance, on peut réactiver l'écriture sur la carte SD
    Serial.println("Mode maintenance terminé. Vous pouvez replacer la carte SD.");
    ecritureSD = true;
}