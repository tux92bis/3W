//#include "3W.h"   // Inclus notre fichier en-tête

/*-----Définition des macros-----*/
// (à mettre dans le fichier "3W")
#define BOUTON_ROUGE 2   // Port du bouton rouge
#define BOUTON_VERT 3   // Port du bouton vert
//#define PHOTORESISTANCE A0   // Port de la photorésistance
//#define LED_PIN 7   // Port de la LED
#define LED_ROUGE 7   // port de la couleur rouge pour la LED
#define LED_BLEU 6    // port de la couleur bleu pour la LED
#define LED_VERT 5    // port de la couleur vert pour la LED



/*-----Utiliser pour basculer entre chaque mode-----*/
// (à mettre dans le fichier "3W")
#define CONFIGURATION 0   
#define STANDARD 1
#define ECONOMIQUE 2
#define MAINTENANCE 3


/*-----structure des données pour le capteur-----*/
// (à mettre dans le fichier "standard")
/*
typedef struct {
    float temperatureAir;
    float hygrometrie;
    int lumiere;
} Capteurs;
*/


/*-----Déclaration des variables globales-----*/
// (à mettre dans le fichier "3W")

//Capteurs capteurs;
int modeActuel = STANDARD;   // Pour savoir à quel mode on se trouve actuellement
int modePrecedent = STANDARD;   // Pour connaître le mode précedent (utile si on est en mode maintenance)
volatile bool boutonAppuyeVert = false;   // Pour connaître l'état du bouton vert
volatile bool boutonAppuyeRouge = false;   // Pour connaître l'état du bouton rouge
unsigned long dureeAppui = 0;   // Pour mesurer le temps d'appuie



/*-----Prototypes des fonctions-----*/
/*-----(à mettre dans le fichier "3W")-----*/
//void modeConfiguration();
//void modeStandard();
//void modeEconomique();
//void modeMaintenance();
//Capteurs lireCapteurs();
//String lireHeure();
//void sauvegarderCSV(Capteurs capteurs, String time);
void boutonRougePresser();
void boutonVertPresser();
//void clignoterLED();
void couleurLedMaintenance();
void couleurLedStandard();
void couleurLedConfiguration();
void couleurLedEconomie();
  

/*On test les couleurs*/
/*-----(à mettre dans les fichier respectifs)-----*/
void couleurLedMaintenance() {
  // Pour afficher une couleur orange à la led
  analogWrite(LED_ROUGE, 255);   
  analogWrite(LED_VERT, 50);
  analogWrite(LED_BLEU, 0);
}

void couleurLedStandard() {
  // Pour afficher une couleur vert à la led
  analogWrite(LED_ROUGE, 0);   
  analogWrite(LED_VERT, 255);
  analogWrite(LED_BLEU, 0);
}

void couleurLedConfiguration() {
  // Pour afficher une couleur jaune à la led
  analogWrite(LED_ROUGE, 255);   
  analogWrite(LED_VERT, 255);
  analogWrite(LED_BLEU, 0);
}

void couleurLedEconomique() {
  // Pour afficher une couleur bleu à la led
  analogWrite(LED_ROUGE, 0);   
  analogWrite(LED_VERT, 0);
  analogWrite(LED_BLEU, 255);
}


/*-----Fonction pour obtenir les lectures des capteurs-----*/
/*-----(à mettre dans le fichier "standard")-----*/
/*
Capteurs get_data() {
    Capteurs data;
    data.lumiere = analogRead(PHOTORESISTANCE); // Lecture de la photorésistance
    data.temperatureAir = dht.readTemperature(); // Lecture de la température
    data.hygrometrie = dht.readHumidity(); // Lecture de l'humidité
    return data;
}
*/


/*-----Fonction pour obtenir l'heure actuelle-----*/ 
/*-----(à mettre dans le fichier "standard")-----*/
/*
String get_time() {
    DateTime now = rtc.now();  // Obtenir l'heure actuelle depuis le RTC

    String time = String(now.year()) + "-" + String(now.month()) + "-" + String(now.day()) + " " +
                  String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());

    return time;
}
*/


/*-----Fonction pour sauvegarder les données dans un fichier CSV-----*/ 
/*-----(à mettre dans le fichier "standard")-----*/
/*
void save_data_csv(Capteurs capteurs, String time) {
    File dataFile = SD.open("data.csv", FILE_WRITE);

    if (dataFile) {
        dataFile.print(time);            // Sauvegarder le temps
        dataFile.print(",");
        dataFile.print(capteurs.temperatureAir);     // Sauvegarder la température
        dataFile.print(",");
        dataFile.print(capteurs.hygrometrie);        // Sauvegarder l'humidité
        dataFile.print(",");
        dataFile.println(capteurs.lumiere);    // Sauvegarder la luminosité
        dataFile.close();
    } 
    
    else {
        Serial.println("Erreur d'ouverture du fichier");
    }
}
*/


/*-----Fonctions pour les différents modes-----*/
/*-----(à mettre dans leurs fichier respectifs)-----*/
/*
void modeConfig() {
    lcd.clear();
    lcd.print("Mode Config actif");
    // Logique pour le mode configuration
}


void modeStandard() {
    lcd.clear();
    lcd.print("Mode Standard actif");
    // Logique pour le mode standard
}

void modeEconomique() {
    lcd.clear();
    lcd.print("Mode Eco actif");
    // Logique pour le mode économique
}

void modeMaintenance() {
    lcd.clear();
    lcd.print("Mode Maint actif");
    // Logique pour le mode maintenance
}
*/

// Fonction d'interruption pour gérer l'appui sur le bouton
/*-----(à mettre dans le fichier à part)-----*/
void boutonRougePresser() {
    boutonAppuyeRouge = true;
  	Serial.println("Interruption bouton rouge !");
}

void boutonVertPresser() {
    boutonAppuyeVert = true;
  	Serial.println("Interruption bouton vert !");
}


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
            if (dureeAppui >= 1000) { 
                modeActuel = MAINTENANCE;   // Passage en mode maintenance

                // Pour retourner en mode standard lorsque l'on quitte le mode maintenance qui à été acceder depuis le mode standard
                modePrecedent = STANDARD;  
              
              	Serial.println("Mode maintenance enclencher");
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
              
              	Serial.println("Mode economique enclencher");
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
        //modeConfiguration();
    }

    if (modeActuel == ECONOMIQUE) {
        couleurLedEconomique();
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
