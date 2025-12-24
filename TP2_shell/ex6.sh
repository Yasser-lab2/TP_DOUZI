date > temp
cat $1 >> temp
cat temp > $1
rm temp