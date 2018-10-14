#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAX_SIZE 512

int
main(int argc, char *argv[])
{
    // 1. check if arguments correct
    if(argc < 3 || argc > 4){
        printf("Usage: cp238p file1 file2 \nCopies file1 to file2\n");
        exit(1);
    }

    // read from file1 (argv[1] and write to file2 (argv[2]))
    // 2. open file1
    int fd1, fd2;
    if((fd1 = open(argv[1],O_RDONLY)) == -1){
        fprintf(stderr, "Source File open failed.\n");
        exit(1);
    }

    // 3. open file2
    // if file2 is s dir
    struct stat file_stat;
    stat(argv[2], &file_stat);
    // if file is dir:
    if(S_ISDIR(file_stat.st_mode) != 0){
        int len1 = strlen(argv[1]);
        int len2 = strlen(argv[2]);
        // check if argv[2] contain '/'
        if(argv[2][len2-1] == '/'){
            // just add name to the end of argv[2]
            char file2[len2+len1];
            strncpy(file2, argv[2], len2);
            strncpy(file2+len2, argv[1], len1);
            if((fd2 = open(file2, O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO)) == -1){
                fprintf(stderr, "Source File open failed.\n");
                exit(1);
            }
        }else{
            char file2[len2+len1+1];
            strncpy(file2, argv[2], len2);

            strncpy(file2+len2, "/", 1);
            strncpy(file2+len2+1, argv[1], len1);
            if((fd2 = open(file2, O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO)) == -1){
                fprintf(stderr, "Source File open failed.\n");
                exit(1);
            }
        }
    }else{
        // argv[2] not dirs
        if((fd2 = open(argv[2], O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO)) == -1){
            fprintf(stderr, "Source File open failed.\n");
            exit(1);
        }
    }

    char cp_buf[MAX_SIZE] = {};
    unsigned length = 0;
    

    while((length = read(fd1, cp_buf, MAX_SIZE)) > 0){
        write(fd2, cp_buf, length);
    }

    close(fd1);
    close(fd2);

  
  exit(0);
}

