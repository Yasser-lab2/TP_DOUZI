#include <stdio.h>      // Pour printf, perror
#include <unistd.h>     // Pour fork, execl, getpid
#include <sys/types.h>  // Pour pid_t
#include <sys/wait.h>   // Pour wait, WIFEXITED, WEXITSTATUS
#include <stdlib.h>     // Pour exit

int main() {
    pid_t pid;
    int status;

    printf("Je suis le processus père (PID: %d). Je vais créer un fils.\n", getpid());

    // 1. Création du processus fils
    pid = fork();

    if (pid < 0) {
        // Erreur lors du fork
        perror("Erreur lors du fork");
        return 1;
    }

    if (pid == 0) {
        // --- Code du processus FILS ---
        printf("Fils : Je vais exécuter 'ps -l' via execl...\n");

        // 2. Remplacement de l'image du processus par la commande ps
        // execl(chemin_absolu, nom_commande, option, NULL);
        // Note : Le chemin est souvent /bin/ps ou /usr/bin/ps (vérifiez avec 'which ps')
        execl("/bin/ps", "ps", "-l", NULL);

        // Si execl fonctionne, le code ci-dessous n'est JAMAIS exécuté.
        // S'il est exécuté, c'est que execl a échoué (ex: mauvais chemin).
        perror("Erreur lors de execl");
        exit(1);
    } 
    else {
        // --- Code du processus PÈRE ---
        printf("Père : J'attends la fin de mon fils...\n");

        // 3. Attente de la fin du fils et récupération du statut
        wait(&status);

        // Analyse du code de retour
        if (WIFEXITED(status)) {
            // WEXITSTATUS extrait le code de retour exact (celui du return ou exit du fils)
            printf("Père : Le fils a terminé avec le code retour : %d\n", WEXITSTATUS(status));
        } else {
            printf("Père : Le fils ne s'est pas terminé normalement.\n");
        }
    }

    return 0;
}