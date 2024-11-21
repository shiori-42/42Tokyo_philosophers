#include "philo.h"

void *print_message(void *thread_id) {
    int id = *(int *)thread_id;
    printf("Thread %d is running\n", id);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[2];
    int thread_ids[2] = {0, 1};

    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, print_message, (void *)&thread_ids[i]);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
