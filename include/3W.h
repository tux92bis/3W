#pragma once   // Pour éviter d'appeler plusieurs fichier en-tête

/*-----Définition des macros-----*/
#define BOUTON_ROUGE 2   // Port du bouton rouge
#define BOUTON_VERT 3   // Port du bouton vert
#define CAPTEUR 4   // Port du capteur
#define PHOTORESISTANCE A0   // Port de la photorésistance

// Utiliser pour basculer entra chaque mode
#define CONFIGURATION 0   
#define STANDARD 1
#define ECONOMIQUE 2
#define MAINTENANCE 3


typedef struct {
    int pressionAtmo;
    int temperatureAir;
    int hygrometrie;
    int lumiere;
} Capteurs;

void modeConfiguration();
void modeStandard();
void modeEconomique();
void modeMaintenance();
