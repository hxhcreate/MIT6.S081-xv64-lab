// copy.c: copy input to output.

#include "kernel/types.h"
#include "user/user.h"

int main()
{
    char buf[64];

    while (1)
    {
        int n = read(0, buf, sizeof buf);
        if (n <= 0)
            break;
        if (write(1, buf, n) == -1) {
            fprintf(2, "cat: write error\n");
            exit(1);
        }
    }

    exit(0);
}