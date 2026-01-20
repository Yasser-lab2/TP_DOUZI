#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

int turn = 0; // 0 for child (odd), 1 for parent (even)
int cpid;

void handler(int sig) {
    // Signal handler - just wake up the process
}

int main(){
    signal(SIGUSR1, handler);
    
    int pid = fork();
    if(pid < 0){
        perror("Fork failed");
        exit(0);
    }
    
    if(pid == 0){
        // Child process - print odd numbers
        cpid = getpid();
        for(int i = 1; i <= 100; i += 2){
            printf("%d ", i);
            fflush(stdout);
            kill(getppid(), SIGUSR1); // Signal parent
            pause(); // Wait for parent signal
        }
    }
    else{
        cpid = pid;
        // sleep(10); // Let child start first
        for(int i = 2; i <= 100; i += 2){
            pause(); // Wait for child signal
            printf("%d ", i);
            fflush(stdout);
            kill(pid, SIGUSR1); // Signal child
        }
        wait(NULL);
    }
    printf("\n");
    return 0;
}