#!/bin/bash

tab=($(cut -d: -f1 /etc/passwd))

echo "> Liste des utilisateurs : ${tab[*]}."
echo ""

total=${#tab[*]}
echo "> Nombre total d'utilisateurs enregistrés : $total."
echo""

randm=$((RANDOM % total))
echo "> Utilisateur sélectionné au hasard : ${tab[$randm]}."