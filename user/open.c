// open.c: create a file, write to it.

#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main()
{
    int fd = open("output.txt", O_WRONLY | O_CREATE);
    if (write(fd, "ooo\n", 4) != 4)
    {
        fprintf(2, "cat: write error\n");
        exit(1);
    }

    exit(0);
}