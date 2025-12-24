if [[ $# -lt 1 ]]
then echo sans argument!!!!!! 
else echo $(($1/60)) minutes $(($1%60)) secondes
fi
