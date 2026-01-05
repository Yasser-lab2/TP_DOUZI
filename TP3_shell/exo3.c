#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(){
        srand( time( NULL ) );

    int pid1;
    pid1=fork();

    if(pid1==0){
        int c=(rand()%100);
        printf("retour fils : %d\n", c);
        exit(c);
    }
    else{
        int status;
        wait(&status);
        int p = WEXITSTATUS(status);
        printf("le status est %d et le retour est %d\n",status, p);



    }
}