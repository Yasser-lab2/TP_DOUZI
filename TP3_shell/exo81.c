#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    printf("--- Exécution CONCURRENTE (who & ps & ls -l) ---\n");

    // Lancement de 'who'
    if (fork() == 0) {
        execlp("who", "who", NULL);
        perror("Erreur who");
        exit(1);
    }
    // Le père n'attend pas ici, il continue immédiatement

    // Lancement de 'ps'
    if (fork() == 0) {
        execlp("ps", "ps", NULL);
        perror("Erreur ps");
        exit(1);
    }
    // Le père n'attend toujours pas

    // Lancement de 'ls -l'
    if (fork() == 0) {
        execlp("ls", "ls", "-l", NULL);
        perror("Erreur ls");
        exit(1);
    }

    // Nettoyage : Le père attend la fin de tous ses fils
    // pour éviter les processus zombies.
    // Note : L'ordre de terminaison est imprévisible.
    while(wait(NULL) > 0); 
    
    printf("--- Fin de tous les processus ---\n");
    return 0;
}