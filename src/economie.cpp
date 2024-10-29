#include "3W.h"
#include <Arduino.h>
/* 
Macros à ajouter dans le fichier "3W" :
LED_ROUGE = broche 7
LED_VERT = broche 6
LED_BLEU = broche 5
*/
void couleurLedEconomie() {
  // Pour afficher une couleur bleu à la led
  analogWrite(LED_ROUGE, 0);   
  analogWrite(LED_VERT, 0);
  analogWrite(LED_BLEU, 255);
}
