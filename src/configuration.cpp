#include "3W.h"
configue(){
  int temps de démarage = millis();
  int temps actuel = millis();
  
  while (temps de démarage - temp actuel ≤ 30 s) { 
  
    // le mode config ici
  
    temps actuel = milllis();
  
    }
}

/* 
Macros à ajouter dans le fichier "3W" :
LED_ROUGE = broche 7
LED_VERT = broche 6
LED_BLEU = broche 5
*/
void couleurLedConfiguration() {
  // Pour afficher une couleur jaune à la led
  analogWrite(LED_ROUGE, 255);   
  analogWrite(LED_VERT, 255);
  analogWrite(LED_BLEU, 0);
}
