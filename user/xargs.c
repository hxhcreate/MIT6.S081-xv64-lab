#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

void my_copy(char **p1, const char *p2){
    *p1 = malloc(strlen(p2) + 1);
    strcpy(*p1, p2);
}

// start with i
int readLine(char **pars, int i){
    int d = 1024;
    char buf[d];
    int j = 0;
    // read one line
    while (read(0, buf + j, 1)){
        if (buf[j] == '\n'){
            buf[j] = 0;
            break;
        }
        j++;
        if (j == d){
            fprintf(2, "Parameters are too long!\n");
            exit(1);
        }
    }
    
    // no read, then return
    if (j == 0){
        return -1;
    }

    // 按照空格划分
    int k = 0;
    while (k < j){
        if (i > MAXARG){
            fprintf(2, "Too much parameters!\n");
            exit(1);
        }
        // '   abc   sdf'
        while ((k < j) && (buf[k] == ' ')){
            k++;
        }
        //start
        int l = k;
        // reserved char
        while ((k < j) && (buf[k] != ' ')){
            k++;
        }
        // k++
        buf[k++] = 0;
        copy(&pars[i], buf + l);
        i++;
    }

    return i;
}

int main(int argc, char *argv[]){
    if (argc < 2){
        printf("Please enter more parameters!\n");
        exit(1);
    }
    else if (argc - 1 > MAXARG){
        fprintf(2, "Too much parameters!\n");
        exit(1);
    }
    else{
        int i;
        char *pars[MAXARG]; // pointers array
        for (i = 1; i < argc; i++){
            my_copy(&pars[i - 1], argv[i]);  // pass address to malloc and copy memory
        }
        
        int end;
        while ((end = readLine(pars, argc - 1)) != -1){
            pars[end] = 0;
            if (fork() == 0){
                exec(pars[0], pars);
                exit(1);
            }else{
                wait(0);
            }  
        }
        exit(0);
    }
}