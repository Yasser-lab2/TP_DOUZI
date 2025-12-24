#Question 3 : factrecur
function fctrec
{
declare -i n
if [[ $1 -eq 0 ]]
    then echo 1 
else 
    ((n=$1-1))
    n=$(fctrec $n)
    echo $(($1*$n))
fi 
}
fctrec $1