#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    int pid1;

    pid1 = fork();

    if (pid1 == 0)
    {
        printf("le fils : pid %d, ppid %d, uid %d, euid %d, guid %d, eguid %d \n", getpid(), getppid(), getuid(), geteuid(), getgid(), getegid());
    }
    else{
        wait(NULL);
        printf("le pere : pid %d, ppid %d, uid %d, euid %d, guid %d, eguid %d \n", getpid(), getppid(), getuid(), geteuid(), getgid(), getegid());
    }

    return 0;
}