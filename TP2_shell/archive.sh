var=`ls`
for i in $var
do 
if [[ $i != "ARCHIVES" ]]
then
cp $i ARCHIVES
fi
done

