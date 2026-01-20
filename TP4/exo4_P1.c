#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> // [cite: 202]
#include <unistd.h>

// Fonction pour le thread des minuscules
void *ecrire_minuscules(void *arg) {
    for (char c = 'a'; c <= 'z'; c++) {
        printf("%c ", c);
        fflush(stdout); // Force l'affichage immédiat
        usleep(1000);   // Légère pause pour accentuer l'entrelacement
    }
    pthread_exit(NULL); // [cite: 228]
}

// Fonction pour le thread des majuscules
void *ecrire_majuscules(void *arg) {
    for (char c = 'A'; c <= 'Z'; c++) {
        printf("%c ", c);
        fflush(stdout);
        usleep(1000);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t th1, th2;

    // Création des threads [cite: 207]
    if (pthread_create(&th1, NULL, ecrire_minuscules, NULL) != 0) {
        perror("Erreur création thread 1");
        return 1;
    }
    if (pthread_create(&th2, NULL, ecrire_majuscules, NULL) != 0) {
        perror("Erreur création thread 2");
        return 1;
    }

    // Attente de la fin des threads [cite: 221]
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    printf("\nFin du programme.\n");
    return 0;
}