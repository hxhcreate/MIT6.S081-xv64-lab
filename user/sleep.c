#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(2, "error params\n");
        exit(1);
    }

    int tick = atoi(argv[0]);

    sleep(tick);

    exit(0);
}