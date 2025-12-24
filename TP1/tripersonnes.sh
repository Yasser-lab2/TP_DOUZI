#!/bin/bash
# Script tripersonnes
# Crée deux fichiers: garcons (prénoms masculins) et filles (prénoms féminins)
# à partir du fichier personnes

# Initialisation: vider les fichiers de sortie s'ils existent
> garcons
> filles

# Lecture du fichier personnes ligne par ligne
while read prenom genre
do
    # Structure case pour tester le genre
    case "$genre" in
        m)
            # Si genre = m (masculin), ajouter au fichier garcons
            echo "$prenom" >> garcons
            ;;
        f)
            # Si genre = f (féminin), ajouter au fichier filles
            echo "$prenom" >> filles
            ;;
        *)
            # Cas par défaut (si le genre n'est ni m ni f)
            echo "Genre inconnu pour $prenom: $genre" >&2
            ;;
    esac
done < personnes.txt

