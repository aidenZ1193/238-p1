#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

// ls > y

int
main(int argc, char *argv[])
{
  /* Insert your code here */
  // 1. check if > exists in the argument
  if(argc != 1){
    printf("Usage: ls > filename\n");
    printf("argc = %d, argv = %s\n", argc, argv);
    exit(1);
  }

  // 2. open y as output file
  int fd;
  fd = open("y.txt", O_CREAT | O_WRONLY, 0777);
  if(fd == -1){
      perror("File opened failed.");
      exit(1);
  }
  fclose(stdout);
  // set fd as stdout
  dup(fd);
  char *arg[] = {"ls", NULL}; 
  if(fork() == 0)
    execvp("ls", arg);
  else
    close(fd);
  
  exit(0);
}

