if [[ !( $# -eq 3)]]
then echo le nombre d\'argument n\'est pas correct
elif [[ !( -r $1 && -r $2 ) ]]
then echo l\'un des deux n\'existe pas ou pas accessible a la lecture
elif [[ !(-w $3 ) ]]
then echo $3 n\'existe pas ou n\'est pas accessible a l\'ecriture
elif [[ !(-w `dirname $3` ) ]]
then echo repertoire de destination inaccessible
else 
cat $1>$3
cat $2>>$3

if(($? != 0)) 
then echo copie echoue
fi
fi
