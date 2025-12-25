#!/bin/bash
# Script pour compter le nombre total de mots dans les fichiers .txt

# Vérifier si un argument est fourni, sinon utiliser le répertoire courant
if [[ $# -eq 0 ]]
then
    repertoire="."
else
    repertoire="$1"
fi

# Vérifier que le répertoire existe et est accessible
if [[ ! (-e "$repertoire") ]]
then
    echo "Erreur: $repertoire n\'existe pas"
    exit 1
elif [[ ! (-d "$repertoire") ]]
then
    echo "Erreur: $repertoire n\'est pas un répertoire"
    exit 1
elif [[ ! (-r "$repertoire") ]]
then
    echo "Erreur: $repertoire n\'est pas accessible en lecture"
    exit 1
fi

declare -i total_mots=0
declare -i nb_fichiers=0

# Parcourir tous les fichiers .txt du répertoire
for fichier in "$repertoire"/*.txt
do
    # Vérifier que le fichier existe (au cas où aucun .txt n'existe)
    if [[ -f "$fichier" ]]
    then
        # Compter les mots dans le fichier
        declare -i nb_mots=$(wc -w < "$fichier")
        echo "$fichier : $nb_mots mots"
        # Ajouter au total
        ((total_mots += nb_mots))
        ((nb_fichiers++))
    fi
done

if [[ $nb_fichiers -eq 0 ]]
then
    echo "Aucun fichier .txt trouvé dans $repertoire"
else
    echo "------------------------------"
    echo "Nombre de fichiers traités : $nb_fichiers"
    echo "Total de mots : $total_mots"
fi