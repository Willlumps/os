#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

// Fork() -> exec() /bin/ls
int main (int argc, char* argv[]) {

  pid_t rc = fork();

  if (rc < 0) {
    // Fork failed; exit
    fprintf(stderr, "fork failed");
    exit(EXIT_FAILURE);

  } else if (rc == 0) {
    pid_t child_return = waitpid(-1, NULL, 0);
    printf("Child wait return %d\n", child_return);
  } else {
    pid_t parent_return = waitpid(rc, NULL, 0);
    printf("Parent wait return %d\n", parent_return);
  }
  return 0;
}
