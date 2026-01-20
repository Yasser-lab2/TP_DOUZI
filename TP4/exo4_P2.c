#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Le fichier est une ressource partagée 
FILE *fichier_partage;

void *thread_range_1(void *arg) {
    for (int i = 0; i <= 100000; i++) {
        fprintf(fichier_partage, "%d\n", i);
    }
    pthread_exit(NULL);
}

void *thread_range_2(void *arg) {
    for (int i = 1000000; i <= 1100000; i++) {
        fprintf(fichier_partage, "%d\n", i);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;

    // Ouverture du fichier en mode écriture
    fichier_partage = fopen("resultats.txt", "w");
    if (fichier_partage == NULL) {
        perror("Erreur ouverture fichier");
        return 1;
    }

    // Création des threads
    pthread_create(&t1, NULL, thread_range_1, NULL);
    pthread_create(&t2, NULL, thread_range_2, NULL);

    // Attente
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Fermeture du fichier
    fclose(fichier_partage);
    
    printf("Écriture terminée. Consultez 'resultats.txt'.\n");
    return 0;
}