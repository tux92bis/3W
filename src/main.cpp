 #include "3W.h" // Inclus notre fichier en-tête
#include <SD.h>

bool ecritureSD = true; // Contrôle l'écriture sur la carte SD

void save_data_csv(Capteurs capteurs, String time) {
    if (ecritureSD) {
        File dataFile = SD.open("data.csv", FILE_WRITE);
        if (dataFile) {
            dataFile.print(time);
            dataFile.print(",");
            dataFile.print(capteurs.temperatureAir);
            dataFile.print(",");
            dataFile.print(capteurs.hygrometrie);
            dataFile.print(",");
            dataFile.println(capteurs.lumiere);
            dataFile.close();
        } else {
            Serial.println(F("Erreur d'ouverture du fichier"));
        }
    }
}

// In a source file (e.g., main.cpp)
DHT dht(6, DHT22); // Definition and initialization of the DHT object
/*-----structure des données pour le capteur-----*/
// (à mettre dans le fichier "standard")
/*
typedef struct {
    float temperatureAir;
    float hygrometrie;
    int lumiere;
} Capteurs;
*/

// Fonction pour faire clignoter la LED selon le mode
/*-----(à mettre dans le fichier à part)-----*/
/*
void clignoterLED() {
    static unsigned long dernierTemps = 0;
    static bool etatLED = LOW;
    unsigned long intervalle = 0;

    switch (modeActuel) {
        case CONFIGURATION:
            intervalle = 100;  // Clignotement rapide
            break;

        case STANDARD:
            intervalle = 500;  // Clignotement moyen
            break;

        case ECONOMIQUE:
            intervalle = 1000; // Clignotement lent
            break;

        case MAINTENANCE:
            intervalle = 200;  // Clignotement intermédiaire
            break;
    }

    if (millis() - dernierTemps >= intervalle) {
        dernierTemps = millis();
        etatLED = !etatLED;
        digitalWrite(LED_PIN, etatLED);
    }
}
*/

void setup() {
    Serial.begin(9600);
    
    // Initialisation du port des boutons pour capter des entrées
    pinMode(BOUTON_ROUGE, INPUT_PULLUP);
    pinMode(BOUTON_VERT, INPUT);

    // Initialisation de la led
    //pinMode(LED_PIN, OUTPUT);
  	pinMode(LED_ROUGE, OUTPUT);
 	  pinMode(LED_VERT, OUTPUT);
  	pinMode(LED_BLEU, OUTPUT);

    // Initialisation des interruptions
    attachInterrupt(digitalPinToInterrupt(BOUTON_ROUGE), boutonRougePresser, RISING);
    attachInterrupt(digitalPinToInterrupt(BOUTON_VERT), boutonVertPresser, RISING);

    //initModules();  // Initialise tous les modules comme DHT, LCD, etc.
    couleurLedStandard(); // Démarre en mode standard

    /*-----Initialisation des capteurs et modules (DHT, Écran LCD, GPS, Horloge, LED RVB, SD card)-----*/
    /*
  	dht.begin(); // Initialisation du capteur DHT22
    lcd.begin(16, 2); // Initialisation de l'écran LCD 16x2
    gps.begin(9600); // Initialisation du GPS
    rtc.begin(); // Initialisation de l'horloge RTC
    ledRVB.init(); // Initialisation de la LED RVB
    */
    
  	/*
    if (!SD.begin(4)) { 
        // Initialisation de la carte SD (CS sur pin 4)
        lcd.clear();
        lcd.print("Erreur init SD");
    }
    */

    // Si bouton rouge appuyer au démarrage
    if (boutonAppuyeRouge) {    
        modeActuel = CONFIGURATION;   // On démarre la machine en mode configuration  
        boutonAppuyeRouge = false; // Rénitialisation de l'état du bouton
        }
}

void loop() {
    
  	if (modeActuel == STANDARD) {
        
        // Si le bouton rouge à été presser pendant le mode standard
        if (boutonAppuyeRouge) {
            dureeAppui = millis();

            while (digitalRead(BOUTON_ROUGE) == HIGH) {
                // Rien ne se passe tant que le bouton est presser
            }

            dureeAppui = millis() - dureeAppui;   // Pour mesurer le temps d'appui

            // Si le bouton est appuyé pendant 5 secondes ou plus
            if (dureeAppui >= 5000) { 
                modeActuel = MAINTENANCE;   // Passage en mode maintenance

                // Pour retourner en mode standard lorsque l'on quitte le mode maintenance qui à été acceder depuis le mode standard
                modePrecedent = STANDARD;  
              
              	Serial.println(F("Mode maintenance enclencher"));
            }
            
            boutonAppuyeRouge = false; // Rénitialisation de l'état du bouton
        }
        // Si le bouton vert à été presser pendant le mode standard
        if (boutonAppuyeVert) {
            dureeAppui = millis();

            while (digitalRead(BOUTON_VERT) == HIGH) {
                // Rien ne se passe tant que le bouton est presser
            }

            dureeAppui = millis() - dureeAppui;   // Pour mesurer le temps d'appui

            // Si le bouton est appuyé pendant 5 secondes ou plus
            if (dureeAppui >= 1000) { 
                modeActuel = ECONOMIQUE;   // Passage en mode economique
              
              	Serial.println(F("Mode economique enclencher"));
            }
            
            boutonAppuyeRouge = false; // Rénitialisation de l'état du bouton
        }
    }

    
    if (modeActuel == MAINTENANCE) {

        // Si le bouton rouge à été presser pendant le mode maintenance
        if (boutonAppuyeRouge) {
            dureeAppui = millis();

            while (digitalRead(BOUTON_ROUGE) == HIGH) {
                // Rien ne se passe tant que le bouton est presser
            }

            dureeAppui = millis() - dureeAppui;   // Pour mesurer le temps d'appui

            // Si le bouton est appuyé pendant 5 secondes ou plus
            if (dureeAppui >= 1000) { 
                modeActuel = modePrecedent;   // Pour retourner dans le mode precedent car on quitte le mode maintenance  
                Serial.println("Mode precedent enclencher");
            }
        }
    }
    

    if (modeActuel == ECONOMIQUE) {

        // Si le bouton rouge à été presser pendant le mode economique
        if (boutonAppuyeRouge) {
            dureeAppui = millis();

            while (digitalRead(BOUTON_ROUGE) == HIGH) {
                // Rien ne se passe tant que le bouton est presser
            }

            dureeAppui = millis() - dureeAppui;   // Pour mesurer le temps d'appui

            // Si le bouton est appuyé pendant 5 secondes ou plus
            if (dureeAppui >= 1000) { 
                modeActuel = MAINTENANCE;   // Passage en mode maintenance 

                // Pour retourner en mode economique lorsque l'on quitte le mode maintenance qui à été acceder depuis le mode economique
                modePrecedent = ECONOMIQUE;
              
              	Serial.println("Mode maintenance enclencher");
            }
        }

        // Si le bouton vert à été presser pendant le mode economique
        if (boutonAppuyeVert) {
            dureeAppui = millis();

            while (digitalRead(BOUTON_VERT) == HIGH) {
                // Rien ne se passe tant que le bouton est presser
            }

            dureeAppui = millis() - dureeAppui;   // Pour mesurer le temps d'appui

            // Si le bouton est appuyé pendant 5 secondes ou plus
            if (dureeAppui >= 1000) { 
                modeActuel = STANDARD;   // Passage en mode standard

                // Pour retourner en mode standard lorsque l'on quitte le mode maintenance qui à été acceder depuis le mode standard
                modePrecedent = STANDARD;
              
              	Serial.println("Mode standard enclencher");
            }
        }
    }
    

    // Lecture des capteurs
    /*
  	capteurs = get_data();
    String time = get_time();

    // Sauvegarde des données
    save_data_csv(capteurs, time);

    // Faire clignoter la LED en fonction du mode
    clignoterLED();
	*/
  	
    // execution du mode actuel
    if (modeActuel == CONFIGURATION) {
        couleurLedConfiguration();
        modeConfiguration();
    }

    if (modeActuel == ECONOMIQUE) {
        //couleurLedEconomique();
        //modeEconomique();
    }

    if (modeActuel == MAINTENANCE) {
        couleurLedMaintenance();
        //modeMaintenance();
    }

    if (modeActuel == STANDARD) {
        couleurLedStandard();
        //modeStandard();
    }

  	//couleurLedMaintenance();  // couleur orange
  	//couleurLedStandard();  // vert
  	//couleurLedConfiguration();  // couleur jaune
  	//couleurLedEconomie();  // couleur bleu
    
  	//delay(1000); // Attente d'une seconde avant la prochaine lecture
}
