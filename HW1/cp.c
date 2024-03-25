#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <source> <target>\n", argv[0]);
    return 1;
  }

  int file_descriptor_source, file_descriptor_target;
  ssize_t bytes_read, bytes_write;
  char buffer[BUFFER_SIZE];

  file_descriptor_source = open(argv[1], O_RDONLY);
  if (file_descriptor_source == -1) {
    perror("Error opening file source");
    return 1;
  }
  file_descriptor_target = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0777);
  if (file_descriptor_target == -1) {
    perror("Error opening file target");
    return 1;
  }

  while ((bytes_read = read(file_descriptor_source, buffer, BUFFER_SIZE)) > 0) {
    bytes_write = write(file_descriptor_target, buffer, bytes_read);
    if (bytes_write != bytes_read) {
      perror("Error writing to file");
      return 1;
    }
  }

  if (bytes_read == -1) {
    perror("Error reading from file");
    return 1;
  }

  if (close(file_descriptor_source) == -1) {
    perror("Error closing source file source");
    return 1;
  }
  if (close(file_descriptor_target) == -1) {
    perror("Error closing target file source");
    return 1;
  }

  return 0;
}