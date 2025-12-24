# #!/bin/bash

# # Pour chaque fichier passé en argument
# for f in "$@"; do
#     echo "---------------------------"
#     echo "Fichier : $f"
#     echo "---------------------------"

#     # Afficher les 5 premières lignes
#     head -5 "$f"

#     # Demander confirmation
#     echo -n "Voulez-vous détruire ce fichier ? (o/n) : "
#     read rep

#     if [[ "$rep" = "o" || "$rep" = "O" ]]; then
#         rm "$f"
#         echo "-> Fichier supprimé."
#     else
#         echo "-> Fichier NON supprimé."
#     fi

#     echo
# done





#! /bin/bash

#Parcourir les fichiers passés en arguments
for i
do
  #Tester si le fichier existe
  if [[ -e $i ]] 
  then 
    { read un; read deux; read trois; read quatre; read cinq; } < "$i"
    ##Afficher les cinques premiers lignes
    echo "==Contenu de $i (5 premiers lignes)=="
    echo  $un
    echo $deux
    echo $trois
    echo $quatre
    echo $cinq
    ##Supprimer le fichier avec confirmation
    rm -i $i
    
  else
    echo "$i n'existe pas."
  fi
done