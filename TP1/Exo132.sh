
#Question 2 : factiter

declare -i x 
declare prd=1

for((x=1;x<=$1;x++))
do
prd=$(( prd*x ))
done
echo $prd