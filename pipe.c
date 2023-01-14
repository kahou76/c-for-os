#include <stdio.h>    //perror
#include <stdlib.h>   //exit
#include <sys/wait.h> //wait
#include <unistd.h>   //fork, pipe

const int BUF_SIZE = 4096;

int main() {
  enum { READ, WRITE };
  pid_t pid;
  int pipeFD[2];

  if (pipe(pipeFD) < 0) {
    perror("Error in creating pipe");
    exit(EXIT_FAILURE);
  }

  pid = fork();
  if (pid < 0) {
    perror("Error during fork");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) // Child
  {
    close(pipeFD[READ]);
    dup2(pipeFD[WRITE], 1); // stdout is now child's read pipe

    //Executes the command ls –l in the child and pipes output to pipe
    execlp("/bin/ls", "ls", "-l", NULL);
    // process is overlayed so does not execut past here..
    printf("Not getting here\n");
  } 
  
  else // Parent
  {
    wait(NULL);
    char buf[BUF_SIZE];
    close(pipeFD[WRITE]);
    int n = read(pipeFD[READ], buf, BUF_SIZE);
    buf[n] = '\0';
    for (int i = 0; i < n; ++i)
      printf("%c ", buf[i]);
    // cout << buf;
    // cout << "Parent exiting" <<endl;
  }
  exit(EXIT_SUCCESS);
}