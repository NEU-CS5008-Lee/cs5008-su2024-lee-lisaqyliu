// name: Qingyang Liu
// email: liu.qingyan@northeastern.edu
// Compile with:
//
// gcc -lpthread hw12.c -o hw12
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 100

// shared variable
int counter = 0;

// mutex for locking
pthread_mutex_t lock;

// thread to be executed - unspecified variable arguments
void* thread1 (void* vargp) {
  // add 1 to counter
  pthread_mutex_lock(&lock);
  counter += 1;
  pthread_mutex_unlock(&lock);
  return NULL;
}

void* thread2 (void* vargp) {
  // add 5 to counter
  // *** YOUR CODE GOES HERE ***
  pthread_mutex_lock(&lock);
  counter += 5;
  pthread_mutex_unlock(&lock);
  return NULL;
}

void* thread3 (void* vargp) {
  // subtract 2 from counter
  // *** YOUR CODE GOES HERE ***
  pthread_mutex_lock(&lock);
  counter -= 2;
  pthread_mutex_unlock(&lock);
  return NULL;
}

void* thread4 (void* vargp) {
  // subtract 10 from counter
  // *** YOUR CODE GOES HERE ***
  pthread_mutex_lock(&lock);
  counter -= 10;
  pthread_mutex_unlock(&lock);
  return NULL;
}

int main() {
  // array to keep Pthread IDs of created threads
  pthread_t tid[NTHREADS*4];
  int i;

  printf("Counter starts at %d\n", counter);
  
  // create and run the thread
  for (i=0; i < NTHREADS; ++i){
    pthread_create(&(tid[i]), NULL, thread1, NULL);
    // *** YOUR CODE GOES HERE ***
    pthread_create(&(tid[i + NTHREADS]), NULL, thread2, NULL);   // Threads for adding 5
    pthread_create(&(tid[i + 2 * NTHREADS]), NULL, thread3, NULL); // Threads for subtracting 2
    pthread_create(&(tid[i + 3 * NTHREADS]), NULL, thread4, NULL); // Threads for subtracting 10
  }

  //wait until all threads are done
  for (i=0; i < NTHREADS*4; ++i){
    pthread_join(tid[i], NULL);
  }

  printf("Counter ends at %d\n", counter);

  // destroy the mutex
  pthread_mutex_destroy(&lock);

  return 0;
}
