#include "kernel/types.h"
#include "user/user.h"

int main() {
    int pds[2];
    int pid;

    pipe(pds);

    if (fork() == 0) {
        char buf[2];
        pid = getpid();
        if (read(pds[0], buf, 1) != 1) {
            fprintf(2, "failed to read in child\n");
            exit(1);
        }
        // close(pds[0]);
        fprintf(1, "%d: received ping\n", pid);

        if (write(pds[1], buf, 1) != 1) {
            fprintf(2, "failed to write in child\n");
            exit(1);
        }
        // close(pds[1]);
        exit(0);
    }
    else {
        pid = getpid();
        char buf[2];
        if(write(pds[1], "a", 1) != 1) {
            fprintf(2, "failed to write in parent\n");
            exit(1);
        }
        // close(pds[1]);
        wait(0);

        if (read(pds[0], buf, 1) != 1) {
            fprintf(2, "failed to read in parent\n");
            exit(1);
        }
        fprintf(1, "%d: received pong\n", pid);
        // close(pds[0]);
        exit(0);

    }


}