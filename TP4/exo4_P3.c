#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Variable globale partagée (Data segment) 
long compteur = 0; 
#define N 1000000 // Nombre d'itérations élevé pour provoquer l'erreur

void *incrementer(void *arg) {
    for (int i = 0; i < N; i++) {
        // Section critique non protégée
        compteur++; 
    }
    // Affichage à la fin de l'exécution du thread
    printf("Fin thread %lu : compteur actuel = %ld\n", pthread_self(), compteur);
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;

    printf("Valeur initiale: %ld\n", compteur);
    printf("N attendu: %d par thread (Total théorique: %d)\n", N, 2*N);

    pthread_create(&t1, NULL, incrementer, NULL);
    pthread_create(&t2, NULL, incrementer, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Valeur finale du compteur : %ld\n", compteur);

    if (compteur != 2 * N) {
        printf("ERREUR : Le résultat n'est pas 2*N !\n");
    } else {
        printf("Succès (ou N est trop petit pour voir l'erreur).\n");
    }

    return 0;
}