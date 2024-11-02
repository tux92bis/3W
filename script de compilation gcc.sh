#!/bin/bash

MCU="atmega328p" # Modèle du micocontrolleur
F_CPU="16000000UL" 
PORT="/dev/ttyUSB0" # Port de l'arduino  
BAUD="115200" # Vitesse de téleversement
OUTPUT="firmware" # Nom du fichier binaire final
CFLAGS="-mmcu=$MCU -DF_CPU=$F_CPU -Os -Wall" # Options de compilation
LDFLAGS="-mmcu=$MCU"

echo "Compilation des fichiers source..." # Étape 1 : Compiler les fichiers .cpp en .o
for file in src/*.cpp; do
    avr-gcc $CFLAGS -c $file -o "${file%.cpp}.o"
    if [ $? -ne 0 ]; then
        echo "Erreur de compilation de $file"
        exit 1
    fi
done

echo "Édition de liens..." # Étape 2 : Lier les fichiers objets en un fichier exécutable
avr-gcc $LDFLAGS src/*.o -o "$OUTPUT.elf"
if [ $? -ne 0 ]; then
    echo "Erreur lors de l'édition de liens"
    exit 1
fi

echo "Conversion en fichier HEX..." # Étape 3 : Convertir le fichier ELF en un fichier HEX pour le téléversement
avr-objcopy -O ihex -R .eeprom "$OUTPUT.elf" "$OUTPUT.hex"
if [ $? -ne 0 ]; then
    echo "Erreur lors de la conversion en HEX"
    exit 1
fi

echo "Téléversement sur Arduino..." # Étape 4 : Téléversement du fichier HEX sur l'Arduino
avrdude -v -patmega328p -carduino -P$PORT -b$BAUD -D -Uflash:w:$OUTPUT.hex:i
if [ $? -ne 0 ]; then
    echo "Erreur de téléversement"
    exit 1
fi

echo "Compilation et téléversement réussis !"
