#!/bin/bash

# Compilation du projet
echo "Compilation du projet..."
platformio run --environment uno
if [ $? -ne 0 ]; then
    echo "Erreur de compilation."
    exit 1
fi

# Téléversement du projet
echo "Téléversement sur Arduino Uno..."
platformio run --target upload --environment uno
if [ $? -ne 0 ]; then
    echo "Erreur de téléversement."
    exit 1
fi

echo "Compilation et téléversement réussis !"
