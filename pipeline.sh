#!/bin/bash

FICHIER="directions.txt"
DEST="./commande_final.c"

# Vérifier que le fichier existe
if [ ! -f "$FICHIER" ]; then
    echo "Erreur : fichier $FICHIER introuvable"
    exit 1
fi

# Envoyer le contenu du fichier vers l'autre programme
cat "$FICHIER" | $DEST
