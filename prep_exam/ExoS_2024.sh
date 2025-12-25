#!/bin/bash
# Script pour lire les fichiers d'une extension donnée

# Vérifier les arguments
if [[ $# -eq 0 ]]
then
    echo "Extension du fichier à lire :"
    read extension
else
    extension="$1"
fi

# Nettoyer l'extension (enlever le point si présent)
extension="${extension#.}"

declare -i trouve=0

# Parcourir les fichiers avec l'extension donnée
for fichier in *."$extension"
do
    if [[ -f "$fichier" ]]
    then
        if [[ ! -r "$fichier" ]]
        then
            echo "Erreur: $fichier n\'est pas accessible en lecture"
            continue
        fi
        
        trouve=1
        echo "========================================="
        echo "Contenu de : $fichier"
        echo "========================================="
        cat "$fichier"
        
        if (( $? != 0 ))
        then
            echo "Erreur lors de la lecture de $fichier"
        fi
        
        echo ""
    fi
done

if [[ $trouve -eq 0 ]]
then
    echo "Aucun fichier avec l\'extension .$extension trouvé"
fi