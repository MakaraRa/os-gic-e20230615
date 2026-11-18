#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *worker(void *arg) {
    for (int i = 1; i <= 10; i++) {
        printf("Worker thread: step %d\n", i);
        usleep(200000);
    }

    printf("Worker thread: finished.\n");
    return NULL;
}

int main() {
    pthread_t thread;

    printf("Main: creating worker thread.\n");

    pthread_create(&thread, NULL, worker, NULL);

    printf("Main: exiting without pthread_join().\n");

    return 0;
}
