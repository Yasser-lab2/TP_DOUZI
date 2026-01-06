#include <stdio.h>      // Pour printf, perror
#include <unistd.h>     // Pour fork, execvp
#include <sys/types.h>  // Pour pid_t
#include <sys/wait.h>   // Pour wait
#include <stdlib.h>     // Pour exit

int main(int argc, char *argv[]) {
    
    // 1. Vérification qu'il y a au moins une commande à lancer
    if (argc < 2) {
        printf("Usage: %s <commande> [arguments...]\n", argv[0]);
        printf("Exemple: %s ls -l\n", argv[0]);
        return 1;
    }

    printf("--- Lancement de la commande : %s ---\n", argv[1]);

    pid_t pid = fork();

    if (pid < 0) {
        perror("Erreur fork");
        return 1;
    }

    if (pid == 0) {
        // --- Processus FILS ---
        
        // Nous utilisons execvp.
        // Paramètre 1 : Le nom de la commande (ex: "ls"). C'est argv[1].
        // Paramètre 2 : Le tableau des arguments complets (nom inclus).
        //               argv est {"./monprog", "ls", "-l", NULL}
        //               &argv[1] pointe vers {"ls", "-l", NULL}
        //               C'est exactement ce qu'attend execvp !
        
        execvp(argv[1], &argv[1]);

        // Si on arrive ici, c'est que la commande n'a pas été trouvée ou a échoué
        perror("Erreur lors de l'exécution de la commande");
        exit(1);
    } 
    else {
        // --- Processus PÈRE ---
        // Le père attend simplement que la commande finisse
        wait(NULL);
        printf("\n--- Commande terminée ---\n");
    }

    return 0;
}