// exec.c: replace a process with an executable file

#include "kernel/types.h"
#include "user/user.h"

int main() {
    char* argv[] = {"echo", "this", "is", "echo", 0};
    exec("echo", argv);  // have its own return

// failed then exec the following
    printf("exec failed!\n");

    exit(0);
}