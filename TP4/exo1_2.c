#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Fonction de gestion du signal (Handler) */
void fin_fils(int sig) {
    // wait(NULL) récupère le fils mort.
    // Comme le signal SIGCHLD garantit que le fils a terminé,
    // cet appel ne bloque pas le père, il nettoie juste le zombie.
    wait(NULL);
    
    // Note : On évite généralement printf dans un handler (pas async-safe),
    // mais pour l'exercice, cela permet de visualiser l'action :
    printf("\n[Père] Signal reçu : Mon fils est mort, je l'ai nettoyé.\n");
}

/*0*/ 
int main(int argc, char *argv[]) 
{ 
    /*1*/ 
    // On associe le signal SIGCHLD à notre fonction fin_fils
    signal(SIGCHLD, fin_fils);

    if (!fork()) 
    { 
        /*2*/ 
        printf("[Fils] Je travaille...\n");
        for (int i = 0 ; i < 10 ; i++); //simule un petit calcul 
        
        /*3*/ 
        printf("[Fils] J'ai fini !\n");
        exit(1) ; 
        /*4*/ 
    } 
    
    /*5*/ 
    printf("[Père] Je boucle à l'infini...\n");
    while(1); //Simule un calcul infini 
    /*6*/ 
}