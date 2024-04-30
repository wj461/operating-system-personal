#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define PAGE_SIZE 4096

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <number>\n", argv[0]);
    return 1;
  }

  unsigned int address = atoi(argv[1]);
  unsigned int page_num = address / PAGE_SIZE;
  unsigned int offset = address % PAGE_SIZE;

  printf("The address %u contains:\npage number = %u, offset = %u ", address,
         page_num, offset);
}