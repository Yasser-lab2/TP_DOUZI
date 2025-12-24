for i in $@
do

if [[ -r $i ]]
then 

head -5 $i

read -p "Voulez vous vraiment supprimer ce ficher [n/y] " a

if [[ $a == "y" ]]
then
rm $i
fi
else 
echo $i n\'existe pas 
fi
done
