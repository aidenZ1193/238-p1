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
    if((fd2 = open(argv[2], O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO)) == -1){
        fprintf(stderr, "Source File open failed.\n");
        exit(1);
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

