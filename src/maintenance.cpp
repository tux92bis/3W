#include "3W.h"

/* 
Macros à ajouter dans le fichier "3W" :
LED_ROUGE = broche 7
LED_VERT = broche 6
LED_BLEU = broche 5
*/
void couleurLedStandard() {
  // Pour afficher une couleur orange à la led
  analogWrite(LED_ROUGE, 255);   
  analogWrite(LED_VERT, 165);
  analogWrite(LED_BLEU, 0);
}
