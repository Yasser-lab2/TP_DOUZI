if [[ $# -lt 1 ]]
then echo erreur pas d\'argument
else
for i in $@
do 

rep=`cat /etc/passwd | grep $i:`
if [[ -z $rep ]]
then echo "utilisateur n'existe pas"
else echo user : $i  rep coneionx: ${rep#*/}
fi

done


fi
