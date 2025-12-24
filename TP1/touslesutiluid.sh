#!/bin/bash
# Format du fichier /etc/passwd:
# nom:x:uid:gid:info:home:shell
while IFS=: read nom x uid reste
do
    # nom = 1er champ (nom d'utilisateur)
    # x = 2ème champ (mot de passe, généralement 'x')
    # uid = 3ème champ (User ID)
    # reste = tous les autres champs (ignorés)
    echo "$nom : $uid"
done < /etc/passwd