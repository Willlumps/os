#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


// Write a program that calls fork() accessing a variable
// in both the child and the parent process
int x = 100;
int main (int argc, char* argv[]) {

  printf("The starting value of x is %d\n", x);

  int rc = fork();

  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
  } else if (rc == 0) { // Child process
    x = 50;
    printf("The value of x in the child process is %d\n", x);
  } else { // Parent
    x = 75;
    printf("The value of x in the parent process is %d\n", x);
  }
  printf("The final value of x is  %d\n", x);

  return 0;
}
