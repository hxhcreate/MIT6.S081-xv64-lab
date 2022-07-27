#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char* fmtname(char *path)
{
    static char buf[DIRSIZ+1];
    char *p;

    // Find first character after last slash.
    for(p=path+strlen(path); p >= path && *p != '/'; p--)
        ;
    p++;

    // Return blank-padded name.
    if(strlen(p) >= DIRSIZ)
        return p;
    memmove(buf, p, strlen(p));
    memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
    return buf;
}

void find(char *path, char *filename){
    char buf[512], *p; // file max_length no more than buf[512]
    
    int fd;
    struct dirent de;
    struct stat st;  // file structure type

    // open dir 
    if((fd = open(path, 0)) < 0){
        fprintf(2, "find: cannot open %s\n", path);
        exit(1);
    }

    if(fstat(fd, &st) < 0){  // place file info into *st  -1 failed 0 right
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        exit(1);
    }
    /*
    if (read(fd, &de, sizeof(de)) != sizeof(de)){
        exit(1);
    }*/

    switch(st.type){
        case T_FILE:
            // file
            // in case of the dir and file have the same name!!! maybe into this
            if (strcmp(de.name, filename) == 0){
                printf("%s/%s\n", path, filename);
            }
            break;

        case T_DIR:
            // dir length
            if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
                fprintf(2, "ls: path too long\n");
                break;
            }
            // buf next path
            strcpy(buf, path);
            p = buf + strlen(buf);  // 
            *p++ = '/';
             // if fd is a dir, this will read a sequence of de contain all the file in this dir
            while(read(fd, &de, sizeof(de)) == sizeof(de)){
                if((de.inum == 0) || (strcmp(de.name, ".") == 0) || (strcmp(de.name, "..") == 0)){  // cases to jump out of loop
                    continue;
                }
                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;
                // get file descriptor
                if(stat(buf, &st) < 0){  // buf is file path
                    fprintf(2, "find: cannot stat %s\n", buf);
                    continue;
                }

                if (st.type == T_FILE){
                    if (strcmp(de.name, filename) == 0){
                        printf("%s\n", buf);
                    }
                }else if (st.type == T_DIR){
                    // recursive here
                    find(buf, filename);
                }
            }
            break;
        }
    close(fd);
}

int main(int argc, char *argv[]){
    if (argc != 3){
        fprintf(2, "Please enter a dir and a filename!\n");
        exit(1);
    }else{
        char *path = argv[1];
        char *filename = argv[2];
        find(path, filename);
        exit(0);
    }
}