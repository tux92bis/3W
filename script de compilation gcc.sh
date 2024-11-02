#!/bin/bash

# Définir le microcontrôleur, la fréquence d'horloge et le port série de l'Arduino
MCU="atmega328p"
F_CPU="16000000UL"
PORT="/dev/ttyUSB0"  # Remplacez par le port de votre Arduino
BAUD="115200"

# Nom du fichier binaire final
OUTPUT="firmware"

# Options de compilation
CFLAGS="-mmcu=$MCU -DF_CPU=$F_CPU -Os -Wall"
LDFLAGS="-mmcu=$MCU"

# Étape 1 : Compiler les fichiers .cpp en .o
echo "Compilation des fichiers source..."
for file in src/*.cpp; do
    avr-gcc $CFLAGS -c $file -o "${file%.cpp}.o"
    if [ $? -ne 0 ]; then
        echo "Erreur de compilation de $file"
        exit 1
    fi
done

# Étape 2 : Lier les fichiers objets en un fichier exécutable
echo "Édition de liens..."
avr-gcc $LDFLAGS src/*.o -o "$OUTPUT.elf"
if [ $? -ne 0 ]; then
    echo "Erreur lors de l'édition de liens"
    exit 1
fi

# Étape 3 : Convertir le fichier ELF en un fichier HEX pour le téléversement
echo "Conversion en fichier HEX..."
avr-objcopy -O ihex -R .eeprom "$OUTPUT.elf" "$OUTPUT.hex"
if [ $? -ne 0 ]; then
    echo "Erreur lors de la conversion en HEX"
    exit 1
fi

# Étape 4 : Téléversement du fichier HEX sur l'Arduino
echo "Téléversement sur Arduino..."
avrdude -v -patmega328p -carduino -P$PORT -b$BAUD -D -Uflash:w:$OUTPUT.hex:i
if [ $? -ne 0 ]; then
    echo "Erreur de téléversement"
    exit 1
fi

echo "Compilation et téléversement réussis !"
