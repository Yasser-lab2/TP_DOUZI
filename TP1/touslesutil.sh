#!/bin/bash

# Lecture du fichier /etc/passwd ligne par ligne
while IFS=: read nom reste
do
    # IFS=: définit ':' comme séparateur de champs
    # On ne garde que le premier champ (nom d'utilisateur)
    echo "$nom"
done < /etc/passwd