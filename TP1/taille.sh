#!/bin/bash
# On utilise ls -l qui affiche ces infos. 
# On passe $1 (le nom du fichier) à la commande ls.
ls -la "$1"  | cut -d " " -f 1,5