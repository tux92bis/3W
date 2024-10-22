#include <Arduino.h>
#include "3W.h"


// put function declarations here:

int get_data() {
  int ldrValue = analogRead(ldrPin); // Lecture de la photorésistance 
  float temperature = dht.readTemperature(); // Lecture de la température
  float humidity = dht.readHumidity(); //Lecture de l'humidité
}
String get_time() {
    DateTime now = rtc.now();  // Obtenir l'heure actuelle depuis le RTC
    String time = String(now.year()) + "-" + String(now.month()) + "-" + String(now.day()) + " " +
                  String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
    return time;
}

void save_data_csv(float temperature, float humidity, int luminosity, String time) {
    File dataFile = SD.open("data.csv", FILE_WRITE);
    if (dataFile) {
        dataFile.print(time);            // Sauvegarder le temps
        dataFile.print(",");
        dataFile.print(temperature);     // Sauvegarder la température
        dataFile.print(",");
        dataFile.print(humidity);        // Sauvegarder l'humidité
        dataFile.print(",");
        dataFile.println(luminosity);    // Sauvegarder la luminosité
        dataFile.close();
    } else {
        Serial.println("Erreur d'ouverture du fichier");
    }
}


void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}
