#!/bin/bash
# Fonction basename personnalisée
function mon_basename() {
    # Vérification qu'un argument a été passé
    if [[ $# -eq 0 ]]; then
        echo "Usage: basename chemin"
        return 1
    fi
    
    chemin="$1"
    
    # Méthode 1: Utilisation du modificateur ## (suppression la plus longue à gauche)
    # On supprime tout jusqu'au dernier '/' inclus
    resultat="${chemin##*/}"
    
    echo "$resultat"
}

# Fonction basename avec gestion du suffixe
function mon_basename_suffixe() {
    # Vérification du nombre d'arguments
    if [[ $# -eq 0 ]]; then
        echo "Usage: basename chemin [suffixe]"
        return 1
    fi
    
    chemin="$1"
    suffixe="$2"
    
    # Étape 1: Extraire le nom de base (dernier élément du chemin)
    resultat="${chemin##*/}"
    
    # Étape 2: Si un suffixe est fourni, le supprimer
    if [[ -n "$suffixe" ]]; then
        # Utilisation du modificateur % (suppression la plus courte à droite)
        resultat="${resultat%$suffixe}"
    fi
    
    echo "$resultat"
}

# mon_basename $*
mon_basename_suffixe $*