#include <stdio.h>      // printf, fgets, perror
#include <stdlib.h>     // exit, malloc
#include <unistd.h>     // fork, execvp, chdir
#include <string.h>     // strtok, strcspn, strcmp
#include <sys/types.h>  // pid_t
#include <sys/wait.h>   // wait

#define MAX_CMD_LEN 1024
#define MAX_ARGS 64

int main() {
    char ligne[MAX_CMD_LEN];    // Buffer pour stocker la ligne tapée
    char *args[MAX_ARGS];       // Tableau de pointeurs pour les arguments (argv)
    pid_t pid;
    int status;

    while (1) {
        // 1. Affichage du prompt
        printf("monshell> ");
        fflush(stdout); // Forcer l'affichage immédiat du prompt

        // 2. Lecture de la commande
        // fgets lit toute la ligne, y compris les espaces
        if (fgets(ligne, MAX_CMD_LEN, stdin) == NULL) {
            break; // Sortie sur Ctrl+D (EOF)
        }

        // Nettoyage : fgets inclut le saut de ligne '\n' à la fin, il faut l'enlever
        ligne[strcspn(ligne, "\n")] = 0;

        // Si la ligne est vide (juste Entrée), on recommence la boucle
        if (strlen(ligne) == 0) continue;

        // 3. Découpage de la ligne (Parsing)
        // On utilise strtok pour couper la chaîne via les espaces " "
        int i = 0;
        char *token = strtok(ligne, " ");
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        args[i] = NULL; // Obligatoire : le tableau argv doit finir par NULL

        // Si aucune commande n'a été trouvée après découpage
        if (args[0] == NULL) continue;

        // 4. Gestion de la commande interne "exit"
        if (strcmp(args[0], "exit") == 0) {
            printf("Fermeture de monshell. Au revoir !\n");
            exit(0);
        }

        // 5. Création du processus pour exécuter la commande externe
        pid = fork();

        if (pid < 0) {
            perror("Erreur fork");
        } 
        else if (pid == 0) {
            // --- Processus FILS ---
            // On utilise execvp :
            // 'v' (vector) : car on passe un tableau d'arguments (args)
            // 'p' (path) : car on veut qu'il cherche 'ls' dans le PATH système (/bin/ls...)
            execvp(args[0], args);

            // Si execvp échoue (commande introuvable), on arrive ici
            perror("Commande inconnue ou erreur d'exécution");
            exit(1); // Le fils doit mourir s'il échoue
        } 
        else {
            // --- Processus PÈRE ---
            // Le shell doit attendre que la commande finisse avant de redonner la main
            wait(&status);
        }
    }

    return 0;
}