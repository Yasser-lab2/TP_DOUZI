#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    printf("--- Exécution SÉQUENTIELLE (who; ps; ls -l) ---\n");

    // 1. Lancement de 'who' ET attente
    if (fork() == 0) {
        execlp("who", "who", NULL);
        exit(1);
    }
    wait(NULL); // Le père BLOQUE ici jusqu'à la fin de 'who'
    printf("--> 'who' terminé.\n");


    // 2. Lancement de 'ps' ET attente
    if (fork() == 0) {
        execlp("ps", "ps", NULL);
        exit(1);
    }
    wait(NULL); // Le père BLOQUE ici jusqu'à la fin de 'ps'
    printf("--> 'ps' terminé.\n");


    // 3. Lancement de 'ls -l' ET attente
    if (fork() == 0) {
        execlp("ls", "ls", "-l", NULL);
        exit(1);
    }
    wait(NULL); // Le père BLOQUE ici jusqu'à la fin de 'ls'
    printf("--> 'ls -l' terminé.\n");

    return 0;
}