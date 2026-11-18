#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 4

void *worker(void *arg) {
    int id = *(int *)arg;

    printf("Thread %d (TID: %lu): sleeping 60 seconds...\n",
           id, (unsigned long)pthread_self());

    sleep(60);

    printf("Thread %d: done.\n", id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];

    printf("PID: %d — observe threads now!\n\n", getpid());
    fflush(stdout);

    for (int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i + 1;

        if (pthread_create(&threads[i], NULL, worker, &ids[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
