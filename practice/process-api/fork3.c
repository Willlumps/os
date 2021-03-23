#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main (int argc, char* argv[]) {

  int rc = fork();

  if (rc < 0) {
    // Fork failed; exit
    fprintf(stderr, "fork failed");
    exit(EXIT_FAILURE);

  } else if (rc == 0) {
    printf("Hello\n");
  } else {
    if (wait(NULL) == -1) {
      fprintf(stderr, "Wait failed\n");
      exit(EXIT_FAILURE);
    }
    printf("Goodbye\n");
  }
  return 0;
}
