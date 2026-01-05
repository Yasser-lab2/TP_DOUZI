#include <stdio.h>      
#include <unistd.h>     // Pour fork, execv, getpid
#include <sys/types.h>  
#include <sys/wait.h>   
#include <stdlib.h>     

int main() {
    pid_t pid;
    int status;

    // Préparation du tableau d'arguments (Vecteur)
    // args[0] : nom de la commande
    // args[1] : option
    // args[2] : NULL (obligatoire pour marquer la fin du tableau)
    char *args[] = {"ps", "-l", NULL}; 

    printf("Je suis le processus père (PID: %d).\n", getpid());

    pid = fork(); // Création du fils [cite: 394]

    if (pid < 0) {
        perror("Erreur fork");
        return 1;
    }

    if (pid == 0) {
        // --- Code du processus FILS ---
        printf("Fils : Exécution de 'ps -l' via execv (tableau)...\n");

        // Utilisation de execv :
        // 1er argument : le chemin absolu du fichier binaire (/bin/ps)
        // 2ème argument : le tableau (vecteur) d'arguments préparé plus haut
        execv("/bin/ps", args);

        // Si on arrive ici, c'est que execv a échoué
        perror("Erreur execv");
        exit(1);
    } 
    else {
        // --- Code du processus PÈRE ---
        wait(&status); // Attente de la fin du fils [cite: 632]

        if (WIFEXITED(status)) {
            printf("Père : Le fils a terminé avec le code : %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}