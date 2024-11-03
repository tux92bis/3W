#include "3W.h"



//Définition des variables globales
int modeActuel = STANDARD;   // Pour savoir à quel mode on se trouve actuellement
int modePrecedent = STANDARD;   // Pour connaître le mode précedent (utile si on est en mode maintenance)
volatile bool boutonAppuyeVert = false;   // Pour connaître l'état du bouton vert
volatile bool boutonAppuyeRouge = false;   // Pour connaître l'état du bouton rouge
unsigned long dureeAppui = 0;   // Pour mesurer le temps d'appuie


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
    // Lorsque bouton rouge presser
    boutonAppuyeRouge = true;
  	Serial.println(F("Interruption bouton rouge !"));
}

void boutonVertPresser() {
    // Lorsque bouton vert presser
    boutonAppuyeVert = true;
  	Serial.println(F("Interruption bouton vert !"));
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