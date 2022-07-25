// fork.c: create a new process

#include "kernel/types.h"
#include "user/user.h"

int main() {
    int pid;

    pid = fork(); // system call

    printf("fork() returned %d\n", pid);

    if (pid == 0) 
        printf("child\n");
    else 
        printf("parent\n");
    

    exit(0);
}