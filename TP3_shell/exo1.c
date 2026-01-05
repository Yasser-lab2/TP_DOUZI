#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid1, pid2;

    pid1 = fork();

    if (pid1 < 0) {
        perror("Erreur lors du fork 1");
        exit(1);
    }

    if (pid1 == 0) {
      
        for (int i = 1; i <= 50; i++) {
            printf("%d ", i);
        }
      
        exit(0); 
    } else {
     
        wait(NULL); 
        
        pid2 = fork();

        if (pid2 < 0) {
            perror("Erreur lors du fork 2");
            exit(1);
        }

        if (pid2 == 0) {
          
            for (int i = 51; i <= 100; i++) {
                printf("%d ", i);
            }
            printf("\n"); 
            exit(0);
        } else {
           
            wait(NULL); 
        }
    }

    return 0;
}