// Pseudo code simplifié pour Arduino, présentant l'architecture du projet
/*
#include <Arduino.h>



// Déclarations et Définitions
#define BOUTON_ROUGE 2
#define BOUTON_VERT 3
#define LED_PIN 7
#define CONFIGURATION 0
#define STANDARD 1
#define ECONOMIQUE 2
#define MAINTENANCE 3

int modeCourant = STANDARD;
volatile bool boutonAppuyeVERT = false;
volatile bool boutonAppuyeROUGE = false;
Capteurs capteurs;

// Prototypes
void modeConfig();
void modeStandard();
void modeEco();
void modeMaint();
void clignoterLED();
void onButtonPress();

// Initialisation
void setup() {
    // Initialisation des ports et des modules
    Serial.begin(9600);
    pinMode(BOUTON_ROUGE, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(BOUTON_ROUGE), onButtonPress, FALLING);
    initModules();  // Initialise tous les modules comme DHT, LCD, etc.
    modeStandard(); // Démarre en mode standard
}

// Boucle principale
void loop() {
    // Gestion du bouton pour changer de mode
    if (boutonAppuye) {
        boutonAppuye = false;
        changerMode();
    }
    // Lecture des capteurs et sauvegarde des données
    capteurs = lireCapteurs();
    sauvegarderCSV(capteurs, lireHeure());
    // Gestion du clignotement LED
    clignoterLED();
    delay(1000); // Pause d'une seconde
}

// Fonctions associées aux différents modes
void modeConfig() { afficherSurLCD("Mode Config"); }
void modeStandard() { afficherSurLCD("Mode Standard"); }
void modeEco() { afficherSurLCD("Mode Eco"); }
void modeMaint() { afficherSurLCD("Mode Maint"); }

// Fonction pour clignoter la LED selon le mode actuel
void clignoterLED() {
    unsigned long intervalle;
    switch (modeCourant) {
        case CONFIGURATION: intervalle = 100; break;
        case STANDARD: intervalle = 500; break;
        case ECONOMIQUE: intervalle = 1000; break;
        case MAINTENANCE: intervalle = 200; break;
    }
    // Logique pour changer l'état de la LED toutes les "intervalle" millisecondes
}

// Fonction d'interruption pour appui sur le bouton
void onButtonPress() { boutonAppuye = true; }

// Fonction pour changer de mode
void changerMode(bool ) {
    modeCourant = (modeCourant + 1) % 4;
    switch (modeCourant) {
        case CONFIGURATION: modeConfig(); break;
        case STANDARD: modeStandard(); break;
        case ECONOMIQUE: modeEco(); break;
        case MAINTENANCE: modeMaint(); break;
    }
}
*/