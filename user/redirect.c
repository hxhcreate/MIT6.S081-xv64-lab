#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"


int main() {
    int pid;

    pid = fork();

    if (pid == 0) {
        close(1);
        open("output.txt", O_WRONLY | O_CREATE);  // return file desciptor 1 for sure cause this is the miniest number not used

        char *argv[] = {"echo", "this", "is", "redirected", "echo", 0};
        exec("echo", argv);
        printf("exec failed!\n");   
        exit(1);
    }
    else {
        wait((int*) 0);  // no need to wait children process to exit
    }

    exit(0);
}