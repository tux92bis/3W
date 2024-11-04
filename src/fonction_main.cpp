#include "3W.h"

//Définition des variables globales
int modeActuel = STANDARD;   // Pour savoir à quel mode on se trouve actuellement
int modePrecedent = STANDARD;   // Pour connaître le mode précedent (utile si on est en mode maintenance)
volatile bool boutonAppuyeVert = false;   // Pour connaître l'état du bouton vert
volatile bool boutonAppuyeRouge = false;   // Pour connaître l'état du bouton rouge
unsigned long dureeAppui = 0;   // Pour mesurer le temps d'appuie
volatile unsigned long tempsInterruption = 0;   // Pour mesurer le temps d'interruption en milisecondes
const unsigned long delaiRebond = 200; // Délai anti-rebond en millisecondes


//Définition des fonctions
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

void boutonRougePresser() {
  unsigned long tempsActuel = millis();
  
  if ((tempsActuel - tempsInterruption > delaiRebond) && digitalRead(BOUTON_ROUGE) == LOW) {
    boutonAppuyeRouge = true;
    Serial.println(F("Interruption bouton rouge !"));
    tempsInterruption = tempsActuel;
  }

/*
  if ((tempsActuel - TempsInterruption > delaiRebond) && digitalRead(BOUTON_VERT) == LOW) {
      boutonAppuyeRouge = true;
      Serial.println(F("Interruption bouton rouge !"));
      TempsInterruption = tempsActuel; // Met à jour le dernier temps de l'interruption
  }
*/

/*
  // Lorsque bouton rouge presser
  boutonAppuyeRouge = true;
  Serial.println(F("Interruption bouton rouge !"));
*/
}

void boutonVertPresser() {
  unsigned long tempsActuel = millis();
  
  if ((tempsActuel - tempsInterruption > delaiRebond) && digitalRead(BOUTON_VERT) == LOW) {
    boutonAppuyeVert = true;
    Serial.println(F("Interruption bouton vert !"));
    tempsInterruption = tempsActuel;
  }
/*  
  unsigned long tempsActuel = millis();

  if ((tempsActuel - TempsInterruption > delaiRebond) && digitalRead(BOUTON_VERT) == LOW) {
      boutonAppuyeVert = true;
      Serial.println(F("Interruption bouton vert !"));
      TempsInterruption = tempsActuel; // Met à jour le dernier temps de l'interruption
  }
*/

/*
    // Lorsque bouton vert presser
    boutonAppuyeVert = true;
  	Serial.println(F("Interruption bouton vert !"));
    */
}

void affichageStandart(){
  lcd.setCursor(0, 0);
  lcd.print(F("Mode"));
  lcd.setCursor(0, 1);
  lcd.print(F("standart"));


}

void affichageEconomique(){
  lcd.setCursor(0, 0);
  lcd.print(F("Mode"));
  lcd.setCursor(0, 1);
  lcd.print(F("economie"));


}

void affichageConfiguration(){
  lcd.setCursor(0, 0);
  lcd.print(F("Mode"));
  lcd.setCursor(0, 1);
  lcd.print(F("configuration"));


}

void affichageMaintenance(){
  lcd.setCursor(0, 0);
  lcd.print(F("Mode"));
  lcd.setCursor(0, 1);
  lcd.print(F("maintenance"));
}
