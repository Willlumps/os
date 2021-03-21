#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>



// Write a program that calls fork() accessing a variable
// in both the child and the parent process
int main (int argc, char* argv[]) {

  int fd = open("/tmp/testFile", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
  int rc = fork();
  write(fd, "what\n", 5);

  if (rc < 0) {
    fprintf(stderr, "fork failed");

  } else if (rc == 0) { // Child process
    printf("The child fd is %d\n", fd);
    write(fd, "cwrite\n", 7);

  } else { // Parent
    printf("The parent fd is %d\n", fd);
    write(fd, "pwrite\n", 7);

    // Wait for child process so we can print out the contents of testFile
    if (wait(NULL) == -1) {
      fprintf(stderr, "Wait failed\n");
      exit(EXIT_FAILURE);
    }


    FILE *fp = fopen("/tmp/testFile", "r");
    if (fp == NULL) {
      fprintf(stderr, "Open failed\n");
      exit(EXIT_FAILURE);
    }
    printf("Test file contents:\n");
    char buf[100];
    while (fgets(buf, 100, fp) != NULL) {
      printf("%s", buf);
    }

    fclose(fp);
  }

  close(fd);
  return 0;
}
