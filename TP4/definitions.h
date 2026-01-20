#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Noms des fichiers pour générer les clés (comme dans l'image)
#define FICHIER1 "key_request" 
#define FICHIER2 "key_response"
#define PROJET 1

// Structure adaptée pour l'exercice (Nombres au lieu de String)
struct msgform {
    long mtype;      // Obligatoire
    int nombre1;     // Donnée 1
    int nombre2;     // Donnée 2
    int somme;       // Résultat
};

// Taille utile du message (tout sauf le long mtype)
#define TAILLE_MSG (sizeof(struct msgform) - sizeof(long))

#endif