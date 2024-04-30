
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#define MAX 100 // Maximum size of the Fibonacci sequence

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

struct args {
  int n;
  long long *fibonacci;
};

void *runner(void *param) {
  pthread_mutex_lock(&lock);
  long long *fib = ((struct args *)param)->fibonacci;
  int n = ((struct args *)param)->n;

  int first = 0;
  int second = 1;
  int next;

  for (int i = 0; i < n; i++) {
    if (i <= 1) {
      next = i;
    } else {
      next = first + second;
      first = second;
      second = next;
    }
    fib[i] = next;
  }

  pthread_cond_signal(&cond);
  pthread_mutex_unlock(&lock);
  pthread_exit(0);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <number>\n", argv[0]);
    return 1;
  }

  int n = atoi(argv[1]);
  long long fibonacci[n];

  struct args thread_args;
  thread_args.n = n;
  thread_args.fibonacci = fibonacci;

  printf("Fibonacci series: %d\n", n);

  int error = 0;
  pthread_t thread;
  error = pthread_create(&thread, NULL, runner, &thread_args);
  if (error != 0) {
    perror("Error creating thread");
    return 1;
  }

  pthread_mutex_lock(&lock);
  pthread_cond_wait(&cond, &lock);
  for (int i = 0; i < n; i++) {
    printf("%ld ", thread_args.fibonacci[i]);
  }
  printf("\n");

  pthread_mutex_unlock(&lock);

  return 0;
}