#include "kernel/types.h"
#include "user/user.h"

// forkexec.c: fork then exec

int main()
{
    int pid, status;

    pid = fork();
    if (pid == 0) // child process
    {
        char *argv[] = {"echo", "THIS", "IS", "ECHO", 0};
        exec("echo", argv);
        printf("exec failed!\n");
        exit(1);
    }
    else // parent process
    {
        printf("parent waiting\n");
        wait(&status);
        printf("the child exited with status %d\n", status);
    }

    exit(0);
}