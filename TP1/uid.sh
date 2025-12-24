#! /bin/bash
old_ifs="$IFS"
IFS="= (" 
set `id`
echo "uid = $2"
IFS="$old_ifs"