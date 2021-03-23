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
    close(STDOUT_FILENO);
    // What happens if I call printf now?
    printf("Where will I print to?\n");
    // Nothing here gets printed
  } else {
    // Parent process still has stdout open, and therefore printf will print to the terminal
    printf("Is stdout still open in the parent process?\n");
  }
  return 0;
}
