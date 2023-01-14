#include <stdio.h>
#include <stdlib.h>   //for exit
#include <sys/wait.h> //for wait
#include <unistd.h>   //for fork, pipe
int main(int argc, char *argv[]) {
  int status;
  int pid = fork();

  
  if (pid < 0) {
    fprintf(stderr, "Error: Fork Failed\n");
    exit(EXIT_FAILURE);

  } else if (pid == 0) {
    // Child
    printf("Child Sleeping: \n");
    sleep(10);

    //Executes the command ls –l in the child and output
    int rc = execlp("/bin/ls", "ls", "-l", (char *)0);
    printf("total: %d\n", rc);
    if (rc == -1) {
      fprintf(stderr, "Error on execl\n");
    }
    // If exec() succeeds, it never returns
    // the line below would only get executed if exec
    // failed
    printf("Child failed\n");
    exit(EXIT_SUCCESS);

    // If exec() succeeds, it never returns
    // the line below would only get executed if exec
    // failed
    printf("Child failed\n");
    exit(EXIT_SUCCESS);


  } else {
    // parent
    printf("Parent Waiting\n");
    wait(&status);
    printf("Parent Sleeping\n");
    sleep(3);
    exit(EXIT_SUCCESS);
  }
}