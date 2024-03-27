
#include <bits/types/struct_timeval.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHARED_MEMORY_NAME "/shared_memory"

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

  int shm_fd;

  shm_fd = shm_open(SHARED_MEMORY_NAME, O_CREAT | O_RDWR, 0666);
  if (shm_fd == -1) {
    perror("shm_open");
    return 1;
  }

  struct timeval tv_end;
  struct timeval tv_begin;
  pid_t p = fork();

  if (p < 0) {
    perror("fork");
    return 1;
  } else if (p == 0) {
    gettimeofday(&tv_begin, NULL);
    if (write(shm_fd, &tv_begin, sizeof(tv_begin)) == -1) {
      perror("write");
      return 1;
    }

    char *file = "/usr/bin/bash";
    char *const args[] = {"/usr/bin/bash", "-c", command, NULL};

    execve(file, args, NULL);

  } else {
    wait(NULL);
    if (lseek(shm_fd, 0, SEEK_SET) == -1) {
      perror("lseek");
      exit(EXIT_FAILURE);
    }

    ssize_t bytes_read = read(shm_fd, &tv_begin, sizeof(tv_begin));
    if (bytes_read == -1) {
      perror("read");
      exit(EXIT_FAILURE);
    }

    gettimeofday(&tv_end, NULL);
    printf("time:%d us \n", tv_end.tv_usec - tv_begin.tv_usec);
  }

  if (close(shm_fd) == -1) {
    perror("close");
    return 1;
  }

  if (shm_unlink(SHARED_MEMORY_NAME) == -1) {
    perror("shm_unlink");
    return 1;
  }
}
