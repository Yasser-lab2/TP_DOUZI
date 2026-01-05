#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{

    int valeur = 9;
    int tab[] = {12, 87, 12, 12, 4, 32, 432, 4, 432, 9, 52, 213};
    int n = 12;

    int pid = fork();

    if (pid == 0)
    {
        for (int i = 0; i < n/2; i++)
        {
            if (tab[i] == valeur)
            {
                exit(i);
            }
        }
        exit(99);
    }
    //pere
    else{

        for (int i = n/2; i < n; i++)
        {
            if (tab[i] == valeur)
            {
                printf("the indice is : %d \n ",i);
            }
        }
        // printf("not found");

    }
    int status;
    wait(&status);

    int code=WEXITSTATUS(status);
    printf("the fils found the index at %d",code);

    return 0;
}