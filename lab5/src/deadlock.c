#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void do_one_thing();
void do_another_thing();
pthread_mutex_t mut1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mut2 = PTHREAD_MUTEX_INITIALIZER;

int main() {
  pthread_t thread1, thread2;

  if (pthread_create(&thread1, NULL, (void *)do_one_thing,NULL) != 0) {
    perror("pthread_create");
    exit(1);
  }

  if (pthread_create(&thread2, NULL, (void *)do_another_thing,NULL) != 0) {
    perror("pthread_create");
    exit(1);
  }

  if (pthread_join(thread1, NULL) != 0) {
    perror("pthread_join");
    exit(1);
  }

  if (pthread_join(thread2, NULL) != 0) {
    perror("pthread_join");
    exit(1);
  }

  return 0;
}

void do_one_thing() {
    pthread_mutex_lock(&mut1);
    printf("doing one thing\n");
    for (int k = 0; k < 500000; k++);
    printf("Mut1 in\n");
    pthread_mutex_lock(&mut2);
    pthread_mutex_unlock(&mut2);
    pthread_mutex_unlock(&mut1);
    printf("Mut1 out\n");
}

void do_another_thing() {
    pthread_mutex_lock(&mut2);
    printf("doing another thing\n");
    for (int k = 0; k < 500000; k++);
    printf("Mut2 in\n");
    pthread_mutex_lock(&mut1);
    pthread_mutex_unlock(&mut1);
    pthread_mutex_unlock(&mut2);
    printf("Mut2 out\n");
  }
