#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <unistd.h>

#define N_FARMER_NUMBER 10
#define S_FARMER_NUMBER 5

pthread_mutex_t mutex_biridge;
pthread_mutex_t mutex_north_count;
pthread_mutex_t mutex_south_count;
int north_pass_count = 0;
int south_pass_count = 0;

// north
void *north_runner(void *param) {
  sleep(random() % 5);

  // wait(mutex_north_count);
  pthread_mutex_lock(&mutex_north_count);
  north_pass_count++;
  if (north_pass_count == 1) {
    // wait(mutex_biridge)
    pthread_mutex_lock(&mutex_biridge);
  }
  // single(mutex_north_count);
  pthread_mutex_unlock(&mutex_north_count);

  /* pass north bridge */
  printf("north_runner\n");
  sleep(random() % 5);

  // wait(mutex_north_count);
  pthread_mutex_lock(&mutex_north_count);
  north_pass_count--;
  if (north_pass_count == 0) {
    // single(mutex_biridge)
    pthread_mutex_unlock(&mutex_biridge);
  }
  // single(mutex_north_count);
  pthread_mutex_unlock(&mutex_north_count);
}

void *south_runner(void *param) {
  sleep(random() % 5);
  // south
  // wait(mutex_south_count);
  pthread_mutex_lock(&mutex_south_count);
  south_pass_count++;
  if (south_pass_count == 1) {
    // wait(mutex_biridge)
    pthread_mutex_lock(&mutex_biridge);
  }
  // single(mutex_south_count);
  pthread_mutex_unlock(&mutex_south_count);

  /* pass south bridge */
  printf("south_runner\n");
  sleep(random() % 5);

  // wait(mutex_south_count);
  pthread_mutex_lock(&mutex_south_count);
  south_pass_count--;
  if (south_pass_count == 0) {
    // single(mutex_biridge)
    pthread_mutex_unlock(&mutex_biridge);
  }
  // single(mutex_south_count);
  pthread_mutex_unlock(&mutex_south_count);
}

int main(int argc, char *argv[]) {
  int error = 0;
  pthread_t threads[N_FARMER_NUMBER + S_FARMER_NUMBER];

  for (int i = 0; i < N_FARMER_NUMBER; i++) {
    error = pthread_create(&threads[i], NULL, north_runner, NULL);
    if (error != 0) {
      perror("Error creating thread");
      return 1;
    }
  }

  for (int i = N_FARMER_NUMBER; i < N_FARMER_NUMBER + S_FARMER_NUMBER; i++) {
    error = pthread_create(&threads[i], NULL, south_runner, NULL);
    if (error != 0) {
      perror("Error creating thread");
      return 1;
    }
  }

  for (int i = 0; i < N_FARMER_NUMBER + S_FARMER_NUMBER; i++) {
    pthread_join(threads[i], NULL);
  }
}