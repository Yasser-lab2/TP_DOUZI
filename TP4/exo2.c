#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe1[2]; // Tube entre ps et grep
    int pipe2[2]; // Tube entre grep et wc

    // 1. Création du premier tube
    if (pipe(pipe1) == -1) {
        perror("Erreur pipe1");
        exit(1);
    }

    // --- Processus 1 : ps -uax ---
    if (fork() == 0) {
        // Dans le fils 1
        
        // On redirige la sortie standard (stdout) vers l'entrée du tube 1
        dup2(pipe1[1], STDOUT_FILENO);
        
        // On ferme les descripteurs inutiles
        close(pipe1[0]); // On ne lit pas
        close(pipe1[1]); // Déjà dupliqué sur stdout
        
        // Exécution de la commande
        execlp("ps", "ps", "-uax", NULL);
        perror("Erreur exec ps"); // Ne s'exécute qu'en cas d'erreur
        exit(1);
    }

    // 2. Création du deuxième tube
    if (pipe(pipe2) == -1) {
        perror("Erreur pipe2");
        exit(1);
    }

    // --- Processus 2 : grep root ---
    if (fork() == 0) {
        // Dans le fils 2
        
        // Entrée : on lit depuis la sortie du tube 1
        dup2(pipe1[0], STDIN_FILENO);
        // Sortie : on écrit dans l'entrée du tube 2
        dup2(pipe2[1], STDOUT_FILENO);
        
        close(pipe1[0]); close(pipe1[1]);
        close(pipe2[0]); close(pipe2[1]);
        
        execlp("grep", "grep", "root", NULL);
        perror("Erreur exec grep");
        exit(1);
    }

    // IMPORTANT : Le père a fini de créer les processus qui utilisent pipe1.
    // Il doit fermer ses propres accès à pipe1, sinon grep ne recevra jamais le signal EOF (Fin de fichier)
    close(pipe1[0]);
    close(pipe1[1]);

    // --- Processus 3 : wc -l ---
    if (fork() == 0) {
        // Dans le fils 3
        
        // Entrée : on lit depuis la sortie du tube 2
        dup2(pipe2[0], STDIN_FILENO);
        
        // Sortie : on laisse la sortie standard (écran) par défaut
        
        close(pipe2[0]);
        close(pipe2[1]);
        
        execlp("wc", "wc", "-l", NULL);
        perror("Erreur exec wc");
        exit(1);
    }

    // Le père ferme les restes du pipe2
    close(pipe2[0]);
    close(pipe2[1]);

    // Le père attend la fin des 3 processus fils pour éviter les processus zombies
    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}