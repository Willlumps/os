#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main (int argc, char* argv[]) {

  int pipefd[2];
  char buf;
  pid_t child_a, child_b;

  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  child_a = fork();

  if (child_a < 0) {
    // Fork failed; exit
    fprintf(stderr, "child_a failed to fork.");
    exit(EXIT_FAILURE);

  } else if (child_a == 0) {
    // Child a stuff
    close(pipefd[0]); // Close unused read
    char str[] = "I am child_a";
    write(pipefd[1], str, strlen(str));
    close(pipefd[1]);
    waitpid(child_b, NULL, 0); // Wait for child b

  } else {
    child_b = fork();

    if (child_b < 0) {
      fprintf(stderr, "child_b failed to fork.");
      exit(EXIT_FAILURE);
    } else if (child_b == 0) {
      // Child b stuff
      close(pipefd[1]); // Close unused write
      while (read(pipefd[0], &buf, 1) > 0) {
        write(STDOUT_FILENO, &buf, 1);
      }
      write(STDOUT_FILENO, "\n", 1);
      close(pipefd[0]);
    }
  }
  return 0;
}
