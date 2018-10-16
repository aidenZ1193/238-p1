#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


/*
    ex: ls |grep "main" |wc

*/

int
main(void)
{
  /* Insert your code here */
  // pipe(int[] pipefd), return 0 when success
  // pipefd[0] = read, pipefd[1] = write

  int fd_1[2], fd_2[2];
  // save stdout to restore in the future
  int stdout_cp;
  stdout_cp = dup(1);
  pipe(fd_1);
  pipe(fd_2);
  printf("ls| grep 'main'| wc\n");
  if(fork() == 0){
    // in child process
    // close stdout and run ls in fork
    close(1);
    // dup fd write to stdin
    dup(fd_1[1]);
    close(fd_1[0]);
    //close(fd_1[1]);
    char *arg[] = {"ls", 0};
    execvp(arg[0], arg);
  }else{
    //wait(0);
    //printf("finished ls\n");
    // fork again
    if(fork() == 0){
      // close stdin, read from pipe
      close(0);
      dup(fd_1[0]);
      //close(fd_1[0]);
      close(fd_1[1]);
      //read(fd_1[0], )

      // close stdout, write to pipe2
      close(1);
      dup(fd_2[1]);
      //close(fd_2[0]);
      close(fd_2[0]);
      char *arg[] = {"grep", "main", 0};
      execvp(arg[0], arg);
    }else{
      //wait(0);
      //printf("finished grep\n");
      close(fd_1[0]);
      close(fd_1[1]);
      // close stdin, read from pipe2
      close(0);
      dup(fd_2[0]);
      close(fd_2[1]);
      //close(fd_2[1]);
      // restore stdout to terminal
      dup2(stdout_cp, 1);
      close(stdout_cp);
      char *arg[] = {"wc", 0};
      execvp(arg[0], arg);
    }
    
  }
  //wait(0);
  //printf("finished wc\n");
  
  exit(0);
}

