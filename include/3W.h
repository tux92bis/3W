/*-----Fichier Header-----*/

#pragma once // Pour éviter d'appeler plusieurs fichier en-tête identique

#include <Arduino.h>
#include <RTClib.h> /* Pour la bibliothèque RTC */
#include <DHT.h>
#include <Wire.h>
#include <TinyGPSPlus.h>
// #include <LiquidCrystal_I2C.h>

//-----Définition des macros-----
// Pour le fichier "fonction_main.cpp"
#define BOUTON_ROUGE 2 // Port du bouton rouge
#define BOUTON_VERT 3  // Port du bouton vert


#define LED_ROUGE 8 // port de la couleur rouge pour la LED
#define LED_BLEU 10 // port de la couleur bleu pour la LED
#define LED_VERT 9  // port de la couleur vert pour la LED

// Utiliser pour basculer entre chaque mode
// Pour le fichier "main.cpp"
#define CONFIGURATION 0
#define STANDARD 1
#define ECONOMIQUE 2
#define MAINTENANCE 3
#define LDR 
#define PHOTORESISTANCE A0
// In a source file (e.g., main.cpp)
// In the header file (.h)

const char PROGMEM *gpsStream =
"$GPRMC,045103.000,A,3014.1984,N,09749.2872,W,0.67,161.46,030913,,,A*7C\r\n"
"$GPGGA,045104.000,3014.1985,N,09749.2873,W,1,09,1.2,211.6,M,-22.5,M,,0000*62\r\n"
"$GPRMC,045200.000,A,3014.3820,N,09748.9514,W,36.88,65.02,030913,,,A*77\r\n"
"$GPGGA,045201.000,3014.3864,N,09748.9411,W,1,10,1.2,200.8,M,-22.5,M,,0000*6C\r\n"
"$GPRMC,045251.000,A,3014.4275,N,09749.0626,W,0.51,217.94,030913,,,A*7D\r\n"
"$GPGGA,045252.000,3014.4273,N,09749.0628,W,1,09,1.3,206.9,M,-22.5,M,,0000*6F\r\n";


extern DHT dht; // Declaration of the external variable // Definition and initialization of the DHT object // définition port et type de capteur DHT
//-----Déclaration des variables globales------//
// Pour le fichier "fonction_main.cpp"
extern int modeActuel;
extern int modePrecedent;
extern volatile bool boutonAppuyeVert;
extern volatile bool boutonAppuyeRouge;
extern unsigned long dureeAppui;

// Pour le fichier "configuration.cpp"
extern byte logInterval;
extern int fileMaxSize;
extern byte timeout;
extern byte lumin;
extern byte luminLow;
extern int luminHigh;
extern unsigned long lastActivityTime;
extern RTC_DS3231 rtc; // RTC pour gérer l'horloge (utiliser aussi dans le fichier "configuration.cpp")

TinyGPSPlus gps; // TinyGPSPlus pour gérer les données GPS (utiliser aussi dans le fichier "configuration.cpp")
// Pour le fichier "standard.cpp"
extern int intervalNormal;
extern int intervalEco; // en ms

struct GPSetDate_t
{
  float latitude;
  float longitude;
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
};

struct DHT_t
{
  float humidity;
  float temperatureC;
  float heatIndexC;
};

struct Donnee
{
  GPSetDate_t GPSetDate;
  int LRD;
  DHT_t DHT;
};

/*
struct DonneesCapteur {
  int luminosite;
  float temperature;
  float humidite;
};

#define ldrPin A0   // broche pour lire les données de la luminosité
extern DHT dht;    // broche + modèle du DHT
*/

// Pour le fichier "maintenance.cpp"
//  Définition de Capteurs
typedef struct
{
  float temperatureAir;
  float hygrometrie;
  int lumiere;
} Capteurs;

// Déclaration des fonctions du fichier "fonction_main.cpp"
void boutonRougePresser();
void boutonVertPresser();
// void clignoterLED();
void couleurLedMaintenance();
void couleurLedStandard();
void couleurLedConfiguration();
void couleurLedEconomie();

// Déclaration des fonctions du fichier "standart.cpp"
void modeStandard();
void enregistrerDonnee();
/*
//DonneesCapteur obtenir_donnees();
String obtenir_temps();
void sauvegarder_donnees_csv();
void couleurLedStandard();
*/

// Déclaration des fonctions du fichier "configuration.cpp"
void modeConfiguration();
void saveToEEPROM();
void resetToDefaults();

// Déclaration des fonctions du fichier "maintenance.cpp"
void modeMaintenance();

// Déclaration des fonctions du fichier "economique.cpp"
void modeEconomique();
