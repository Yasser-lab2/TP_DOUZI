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

    // 2. Récupération des files (Identique à l'image)
    frequete = msgget(clef_requetes, 0700 | IPC_CREAT);
    if (frequete == -1) { perror("msgget freq"); return(EXIT_FAILURE); }

    freponse = msgget(clef_reponses, 0700 | IPC_CREAT);
    if (freponse == -1) { perror("msgget frep"); return(EXIT_FAILURE); }

    // 3. Préparation du message
    msg.mtype = getpid(); // Le type EST le PID (comme demandé)
    
    printf("Entrez deux entiers : ");
    scanf("%d %d", &msg.nombre1, &msg.nombre2);

    // 4. Envoi sur la file REQUETE
    // On utilise TAILLE_MSG au lieu de strlen(msg.mtext)+1
    res = msgsnd(frequete, &msg, TAILLE_MSG, 0);
    if (res == -1) { perror("msgsnd"); exit(0); }

    // 5. Attente sur la file REPONSE
    // On attend un message dont le type est exactement notre PID
    res = msgrcv(freponse, &msg, TAILLE_MSG, getpid(), 0);
    if (res == -1) { perror("msgrcv"); exit(0); }

    printf("Résultat reçu du serveur : %d\n", msg.somme);

    return EXIT_SUCCESS;
}