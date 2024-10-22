#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Adresse de l'écran LCD I2C (souvent 0x27 ou 0x3F selon le modèle)
#define LCD_ADDRESS 0x27

// Définir la taille de l'écran LCD (colonnes, lignes)
LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);

void setup() {
  // Initialiser l'écran LCD
  lcd.begin();
  // Activer le rétroéclairage
  lcd.backlight();

  // Afficher un message
  lcd.setCursor(0, 0); // Positionner le curseur à la première ligne, première colonne
  lcd.print("Hello, Arduino!");

  lcd.setCursor(0, 1); // Deuxième ligne
  lcd.print("I2C LCD Test");
}

void loop() {
  // Le code principal ici (tu peux ajouter des interactions)
}
