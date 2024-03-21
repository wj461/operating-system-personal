#include <stdio.h>
#include <threads.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <source> <target>\n", argv[0]);
    return 1;
  }

  FILE *fptr_source;
  FILE *fptr_target;

  fptr_source = fopen(argv[1], "r");
  fptr_target = fopen(argv[2], "w");

  if (fptr_source == NULL || fptr_target == NULL) {
    perror("The file could not be opened\n");
    return 1;
  }

  char source[100];
  while (fgets(source, 100, fptr_source) != NULL) {
    fputs(source, fptr_target);
    printf("do\n");
  }

  int err = fclose(fptr_source);
  if (err != 0) {
    perror("The file could not be closed\n");
    return 1;
  }

  err = fclose(fptr_target);
  if (err != 0) {
    perror("The file could not be closed\n");
    return 1;
  }

  return 0;
}