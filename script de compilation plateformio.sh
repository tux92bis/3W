#!/bin/bash

# Vérifiez si PlatformIO est installé
if ! command -v platformio &> /dev/null; then
    echo "PlatformIO n'est pas installé. Installez-le avec la commande : pip install platformio"
    exit 1
fi

# Nettoyage du projet (optionnel)
echo "Nettoyage des fichiers précédents..."
platformio run --target clean

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
