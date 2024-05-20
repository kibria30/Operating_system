#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

sem_t chopsticks[NUM_PHILOSOPHERS];

void* philosopher(void* num) {
    int id = *(int*)num;

    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1); // Simulating thinking
        
        // Pick up chopsticks
        printf("Philosopher %d is hungry and tries to pick up chopstick %d and %d.\n", id, id, (id + 1) % NUM_PHILOSOPHERS);

        if (id % 2 == 0) {
            sem_wait(&chopsticks[id]);
            sem_wait(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);
        } else {
            sem_wait(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);
            sem_wait(&chopsticks[id]);
        }

        // Eating
        printf("Philosopher %d is eating.\n", id);
        sleep(1); // Simulating eating

        // Put down chopsticks
        sem_post(&chopsticks[id]);
        sem_post(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d has finished eating and puts down chopstick %d and %d.\n", id, id, (id + 1) % NUM_PHILOSOPHERS);
    }
    return NULL;
}

int main() {
    int i;
    int ids[NUM_PHILOSOPHERS];
    pthread_t philosophers[NUM_PHILOSOPHERS];

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&chopsticks[i], 0, 1);
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&chopsticks[i]);
    }

    return 0;
}