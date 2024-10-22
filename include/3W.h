#pragma once

#define CONFIGURATION 0
#define STANDARD 1
#define ECONOMIQUE 2
#define MAINTENANCE 3

const int buttonPin1 = 2;
const int buttonPin2 = 3;
const int ledPinR = 9;
const int ledPinG = 10;
const int ledPinB = 11;

int buttonState1 = 0;
int buttonState2 = 0;
unsigned long lastButtonPress1 = 0;
unsigned long lastButtonPress2 = 0;
int currentMode = STANDARD;
int sdCardInserted = 0;
int dataAvailable = 0;

typedef struct {
    int pressionAtmo;
    int temperatureAir;
    int hygrometrie;
} Capteurs;

void modeConfiguration();
void modeStandard();
void modeEconomique();
void modeMaintenance();