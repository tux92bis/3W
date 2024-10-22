#pragma once

#define CONFIGURATION 
#define STANDARD 
#define ECONOMIQUE 
#define MAINTENANCE 

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
