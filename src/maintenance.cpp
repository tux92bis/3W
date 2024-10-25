#include "3W.h" // Inclusion du fichier en-tête

extern int modeCourant;  // Mode courant défini dans main.cpp
extern Capteurs capteurs;  // Structure des capteurs

// Fonction pour passer en mode maintenance
void modeMaintenance() {
    lcd.clear();
    lcd.print("Mode Maintenance");
    Serial.println("Mode Maintenance actif");
    
    // Arrêter l'écriture sur la carte SD (on considère que la carte peut être retirée)
    Serial.println("Carte SD peut être retirée en toute sécurité.");

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

    // Une fois que l'on quitte le mode maintenance, on peut remettre la carte SD en sécurité
    Serial.println("Vous pouvez remettre la carte SD en toute sécurité.");
}
