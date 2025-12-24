if (( $# != 2))
then echo le nombre d\'argument n\'est pas correct
elif [[ !( -r $1 ) ]]
then echo $1: n\'existe pas ou pas accessible a la lecture
elif [[ !( -f $1 ) ]]
then echo $1 n\'est pas ordinaire
elif [[ !(-a $2 ) ]]
then echo $2 n\'existe pas
elif [[ !(-w `dirname $2` ) ]]
then echo repertoire de destination inaccessible
else 

cp $1 $2

if(($? != 0)) 
then echo copie echoue
fi
fi
