#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

int main(){
    int fd1[2], fd2[2];
    int count = 0;
    char line[256];
    
    // Create pipes
    if(pipe(fd1) == -1 || pipe(fd2) == -1){
        perror("pipe");
        exit(1);
    }
    
    // First child: ps -aux
    int pid1 = fork();
    if(pid1 == -1){
        perror("fork");
        exit(1);
    }
    
    if(pid1 == 0){
        close(fd1[0]); // Close read end
        dup2(fd1[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(fd1[1]);
        execlp("ps", "ps", "-aux", NULL);
        perror("execlp ps");
        exit(1);
    }
    
    // Second child: grep root
    int pid2 = fork();
    if(pid2 == -1){
        perror("fork");
        exit(1);
    }
    
    if(pid2 == 0){
        close(fd1[1]); // Close write end
        close(fd2[0]); // Close read end
        dup2(fd1[0], STDIN_FILENO); // Redirect stdin from pipe1
        dup2(fd2[1], STDOUT_FILENO); // Redirect stdout to pipe2
        close(fd1[0]);
        close(fd2[1]);
        execlp("grep", "grep", "root", NULL);
        perror("execlp grep");
        exit(1);
    }
    
    // Parent: count lines from grep output
    close(fd1[0]);
    close(fd1[1]);
    close(fd2[1]); // Close write end
    
    FILE *fp = fdopen(fd2[0], "r");
    if(fp == NULL){
        perror("fdopen");
        exit(1);
    }
    
    while(fgets(line, sizeof(line), fp) != NULL){
        count++;
    }
    
    fclose(fp);
    wait(NULL);
    wait(NULL);
    
    printf("%d\n", count);
    
    return 0;
}