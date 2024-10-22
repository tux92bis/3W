#include "3W.h"   // Inclus notre fichier en-tête

/*-----code des fonctions-----*/

// structure des données pour le capteur
typedef struct {
    int temperatureAir;
    int hygrometrie;
    int lumiere;
} Capteurs;


void setup() {
  Serial.begin(9600);   // Initalisation du moniteur série

  // Initialisation du port du bouton pour capter des entrées
  pinMode(BOUTON_ROUGE, INPUT);
  pinMode(BOUTON_VERT, INPUT);
}

void loop() 
{
  /*A completer : fonction qui appel la fonction de mode approprier en fonction de l'état initial et des fonctions d'interruptions.*/ 
}