#include <stdio.h>      // Pour printf, perror
#include <unistd.h>     // Pour fork, execl, getpid
#include <sys/types.h>  // Pour pid_t
#include <sys/wait.h>   // Pour wait
#include <stdlib.h>     // Pour exit

int main() {
    pid_t pid_ls, pid_ps, pid_fini;
    int status;

    printf("Père : Je vais lancer deux fils en parallèle.\n");

    // --- 1. Création du premier fils pour 'ls -l' ---
    pid_ls = fork();

    if (pid_ls < 0) {
        perror("Erreur fork 1");
        return 1;
    }

    if (pid_ls == 0) {
        // Code du fils ls
        // Note: exec remplace le processus, donc exit(1) n'est atteint qu'en cas d'erreur
        execl("/bin/ls", "ls", "-l", NULL);
        perror("Erreur execl ls");
        exit(1);
    }

    // --- 2. Création du second fils pour 'ps -l' ---
    pid_ps = fork();

    if (pid_ps < 0) {
        perror("Erreur fork 2");
        // On pourrait tuer pid_ls ici pour nettoyer, mais restons simples
        return 1;
    }

    if (pid_ps == 0) {
        // Code du fils ps
        execl("/bin/ps", "ps", "-l", NULL);
        perror("Erreur execl ps");
        exit(1);
    }

    // --- 3. Attente du premier processus terminé ---
    
    // Le père continue ici. Il a deux fils en cours d'exécution.
    // wait() bloque jusqu'à ce que L'UN des fils se termine.
    // Elle retourne le PID du fils qui vient de finir.
    pid_fini = wait(&status);

    printf("\n--------------------------------------------------\n");
    if (pid_fini == pid_ls) {
        printf("Résultat : Le processus 'ls -l' (PID %d) a terminé en PREMIER.\n", pid_fini);
    } else if (pid_fini == pid_ps) {
        printf("Résultat : Le processus 'ps -l' (PID %d) a terminé en PREMIER.\n", pid_fini);
    } else {
        printf("Résultat : Un processus inconnu (%d) a terminé (erreur ?).\n", pid_fini);
    }
    printf("--------------------------------------------------\n");

    // --- 4. Attente du second processus ---
    // Il est important d'attendre le deuxième fils aussi pour éviter qu'il ne devienne "zombie"
    wait(NULL); 
    printf("Père : Le second processus a aussi terminé. Fin du programme.\n");

    return 0;
}