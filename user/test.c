#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fs.h"

/*
int main() {
    int p[2];
    pipe(p);
    if (fork() == 0) {
        // write(1, "child\n", 6);
        char buf[8];
        while(read(p[0], buf, 7) > 0) {
            fprintf(1, buf);
            memset(buf, 0, 8);
        }
        

    }
    else {
        // wait((int*)0);
        write(p[1], "parent\n", 7);
        
    }
    exit(0);
}*/

int main () {
    struct dirent de; // file structure type
    int fd = open("copy", 0);
    read(fd, &de, sizeof(struct dirent));
    printf("%d;%s", de.inum, de.name);
    exit(0);
}