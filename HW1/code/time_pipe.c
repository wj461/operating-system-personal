
#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#define MSGSIZE 16

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <command>\n", argv[0]);
    return 1;
  }

  char command_temp[100] = "";
  char command[100] = "";
  for (int i = 1; i < argc; i++) {
    sprintf(command_temp, "%s ", argv[i]);
    strcat(command, command_temp);
  }

  struct timeval tv_begin, tv_end;
  char inbuf[MSGSIZE];
  int pipe_data[2], pid, nbytes;
  if (pipe(pipe_data) < 0)
    return 1;
  pid_t p = fork();

  if (p < 0) {
    perror("fork fail");
    return 1;
  } else if (p == 0) {
    gettimeofday(&tv_begin, NULL);
    write(pipe_data[1], &tv_begin, sizeof(tv_begin));

    char *file = "/usr/bin/bash";
    char *const args[] = {"/usr/bin/bash", "-c", command, NULL};

    execve(file, args, NULL);

  } else {
    wait(NULL);

    gettimeofday(&tv_end, NULL);
    read(pipe_data[0], &tv_begin, MSGSIZE);
    printf("time:%d us \n", tv_end.tv_usec - tv_begin.tv_usec);
  }
}