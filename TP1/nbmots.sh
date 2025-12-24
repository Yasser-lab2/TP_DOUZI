#!/bin/bash

echo "Entrez une suite de mots"
read ligne

# On utilise 'set' pour découper la ligne en paramètres positionnels 
set $ligne

# $# est une variable automatique qui contient le nombre d'arguments 
echo "$# mots ont été saisis"