#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <sys/wait.h>

// Fork() -> exec() /bin/ls
int main (int argc, char* argv[]) {

  int rc = fork();

  if (rc < 0) {
    // Fork failed; exit
    fprintf(stderr, "fork failed");
    exit(EXIT_FAILURE);

  } else if (rc == 0) {
    printf("I am the child, hear me roar!!!\n");
  } else {
    // Wait returns the pid of the terminated/finished child process
    // Otherwise -1 is returned on failure
    if (wait(NULL) == -1) {
      fprintf(stderr, "Wait failed\n");
      exit(EXIT_FAILURE);
    }
    printf("it me, parent\n");
  }
  return 0;
}
