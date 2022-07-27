#include "kernel/types.h"
#include "user/user.h"

#define PRIME_MAX 35

void childProcess(int* pr);
int main() 
{
    int p[2];
    pipe(p);
    if (fork() == 0) {
        childProcess(p);
    }
    else {
        close(p[0]);
        for (int i = 2; i <= PRIME_MAX; i++) 
            write(p[1], &i, sizeof(int));  //directly write 32-bit (4-byte) ints to the pipes, rather than using formatted ASCII I/O.
        // needed to close pipe cause x64 only allowd 35 file descriptors      
        close(p[1]);
        wait((int*) 0);  // wait child process to complete
    }
    exit(0);
}

void childProcess(int* pl) 
{
    int pr[2];
    int n;

    close(pl[1]); // close left pipe write

    if(read(pl[0], &n, sizeof(int)) != sizeof(int)) {
        fprintf(2, "child read error!\n");
        exit(1);
    }

    pipe(pr);

    if (fork() == 0) {
        childProcess(pr);
    }
    else {
        close(pr[0]);  // right pipe only write
        // write(1, "prime %d\n", n);  not right
        fprintf(1, "prime %d\n", n);
        int prime = n;
        while(read(pl[0], &n, sizeof(int)) == sizeof(int)) {  // if prime then write
            if (n % prime != 0) {
                write(pr[1], &n, sizeof(int));
            }
        }
        close(pr[1]);  // write complete then close pipe
        wait((int*) 0);    
    }
    exit(0);
}