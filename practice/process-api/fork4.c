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
    char *args[] = {"ls", "-l", NULL};
    char *env[] = {"HOME=/usr/home", "LOGNAME=home", NULL};

    /* execl */
    //execl("/bin/ls", "ls", "-l",  ".", NULL);

    /* execle */
    //execle("/bin/ls", "ls", "-l", NULL, env);

    /* execlp */
    // execlp("ls", "ls", "-l", "..", NULL);
    /* execvp */
    execvp(args[0], args);
  } else {
    if (wait(NULL) == -1) {
      fprintf(stderr, "Wait failed\n");
      exit(EXIT_FAILURE);
    }
  }
  return 0;
}
