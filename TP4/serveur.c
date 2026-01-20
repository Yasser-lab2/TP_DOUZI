#include "definitions.h"

int main(void) {
    int res;
    int frequete, freponse;
    key_t clef_requetes, clef_reponses;
    struct msgform msg;

    // 1. Génération des clés (Identique à l'image)
    clef_requetes = ftok(FICHIER1, PROJET);
    if (clef_requetes == -1) {
        perror("Pb ftok requetes"); exit(EXIT_FAILURE);
    }
    
    clef_reponses = ftok(FICHIER2, PROJET);
    if (clef_reponses == -1) {
        perror("Pb ftok reponses"); exit(EXIT_FAILURE);
    }

    // 2. Création des files (Identique à l'image)
    frequete = msgget(clef_requetes, 0700 | IPC_CREAT);
    if (frequete == -1) { perror("msgget freq"); exit(EXIT_FAILURE); }

    freponse = msgget(clef_reponses, 0700 | IPC_CREAT);
    if (freponse == -1) { perror("msgget frep"); exit(EXIT_FAILURE); }

    printf("Serveur prêt (PID=%d). Attente de nombres...\n", getpid());

    // Boucle infinie pour traiter plusieurs clients
    while(1) {
        // Lecture dans la file REQUETES
        // Type 0 = on prend le premier message dispo
        res = msgrcv(frequete, &msg, TAILLE_MSG, 0, 0);
        if (res == -1) { perror("msgrcv"); exit(0); }

        printf("Reçu de PID %ld : %d + %d\n", msg.mtype, msg.nombre1, msg.nombre2);

        // Traitement (Addition)
        msg.somme = msg.nombre1 + msg.nombre2;

        // Envoi dans la file REPONSES
        // Note: msg.mtype contient déjà le PID du client (envoyé par le client)
        // On renvoie donc le message avec ce même type pour que le client le reconnaisse.
        res = msgsnd(freponse, &msg, TAILLE_MSG, 0);
        if (res == -1) { perror("msgsnd"); exit(0); }
    }

    return EXIT_SUCCESS;
}