#!/bin/bash
cmd=$1

# On redirige la sortie standard (1) et d'erreur (2) vers /dev/null
# car on veut juste tester, pas afficher le résultat.
ls "/bin/$cmd" > /dev/null 2>&1

# $? contient le code de retour de la dernière commande (ls)
if [ $? -eq 0 ]; then
    echo "0"  # La commande existe
else
    echo "2" # La commande n'existe pas
fi