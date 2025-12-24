if ((  $#==1 ))
then

cp $1 temporaire
date>$1
cat temporaire >>$1
rm temporaire

else 
echo une erreur de syntaxe 
fi
