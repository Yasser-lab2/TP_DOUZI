Ajouter()
{
  echo "Donner le  Nom : "
  read nom
  echo "Donner le  Numéro de téléphone : "
  read tel
  echo "$nom,$tel" >>agenda
}

Rechercher()
{
  echo "Nom à rechercher : "
  read nom
  clear
  grep $nom  agenda
}

Supprimer()
{
  echo "Nom à supprimer : "
  read nom
  grep $nom, agenda>/dev/null
if [[ $? -eq 0 ]] 
then
  grep -v $nom,  agenda > temporaire
  cp temporaire  agenda
  rm temporaire
else echo "nom n existe pas !!!"
fi
}

Modifier()
{
    echo "Nom à modifier : "
  read nom
   grep $nom,  agenda> /dev/null
if [[ $? -eq 0 ]] 
  then
    echo "Nouveau nom : "
    read nv_nom
    echo "Nouveau téléphone : "
    read tel
    grep -v $nom,  agenda > temporaire
    echo "$nv_nom,$tel" >> temporaire
    cp temporaire  agenda

rm temporaire
  else
    echo "Ce nom n'existe pas!!!"
  fi
}

Lister()
{
 
  cat  agenda
  read
}


while :
do
    echo "===================================="
    echo ""
  echo "1- Ajouter une fiche"
  echo "2- Rechercher une fiche"
  echo "3- Supprimer une fiche"
  echo "4- Modifier une fiche"
  echo "5- Afficher l'annuaire"
  echo "6- Fin"
  echo "===================================="
  echo ""
  read choix
  clear
  case $choix in
  1) Ajouter;;
  2) Rechercher;;
  3) Supprimer;;
  4) Modifier;;
  5) Lister;;
  6) exit 1;;
  *) echo "Veuillez inserer un choix correct";;
  esac

done
