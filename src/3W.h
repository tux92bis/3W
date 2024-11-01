/*-----Fichier Header-----*/

#pragma once   // Pour éviter d'appeler plusieurs fichier en-tête identique

#include <Arduino.h>

// Définition de Capteurs
typedef struct {
    float temperatureAir;
    float hygrometrie;
    int lumiere;
} Capteurs;


//Définition des macros
#define BOUTON_ROUGE 2   // Port du bouton rouge
#define BOUTON_VERT 3   // Port du bouton vert

#define LED_ROUGE 8   // port de la couleur rouge pour la LED
#define LED_BLEU 10    // port de la couleur bleu pour la LED
#define LED_VERT 9    // port de la couleur vert pour la LED

#define PHOTORESISTANCE A0  

//Utiliser pour basculer entre chaque mode
#define CONFIGURATION 0   
#define STANDARD 1
#define ECONOMIQUE 2
#define MAINTENANCE 3


//-----Déclaration des variables globales------
//Pour le fichier "fonction_main.cpp"
extern int modeActuel;
extern int modePrecedent;
extern volatile bool boutonAppuyeVert;
extern volatile bool boutonAppuyeRouge;
extern unsigned long dureeAppui;

//Pour le fichier "configuration.cpp"
extern int logInterval;
extern int fileMaxSize;
extern int timeout;
extern int lumin;
extern int luminLow;
extern int luminHigh;
extern unsigned long lastActivityTime;


//Déclaration des fonctions du fichier "fonction_main.cpp"
void boutonRougePresser();
void boutonVertPresser();
//void clignoterLED();
void couleurLedMaintenance();
void couleurLedStandard();
void couleurLedConfiguration();
void couleurLedEconomie();


//Déclaration des fonctions du fichier "standart.cpp"
void modeStandard();
int obtenir_donnees();
String obtenir_temps();
void sauvegarder_donnees_csv();
void couleurLedStandard();


//Déclaration des fonctions du fichier "configuration.cpp"
void modeConfiguration();
void saveToEEPROM();
void resetToDefaults();


//Déclaration des fonctions du fichier "maintenance.cpp"
void modeMaintenance();


//Déclaration des fonctions du fichier "economique.cpp"
void modeEconomique();
