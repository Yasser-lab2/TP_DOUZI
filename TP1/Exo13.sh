#Question 1 : tirage_flash

declare -i x
for ((x=1;x<=6;x++))
do 
echo $((RANDOM%49 +1))
done






