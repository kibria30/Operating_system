#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_SLICES 5

sem_t pizza;      // Semaphore to count pizza slices
sem_t deliver;    // Semaphore to ensure one delivery order at a time
pthread_mutex_t mutex; // Mutex to protect num_slices
int num_slices = 0;
int must_study = 1; // Flag to indicate if students need to continue studying

void* student(void* arg) {
    while (must_study) {
        // Try to pick up a piece of pizza
        sem_wait(&pizza);

        // Eat the pizza slice (protected by mutex)
        pthread_mutex_lock(&mutex);
        if (num_slices > 0) {
            num_slices--;
            printf("Student %ld ate a slice. Slices left: %d\n", (long)arg, num_slices);
        }
        pthread_mutex_unlock(&mutex);

        // Simulate study time
        sleep(1);

        // If pizza is out, order a new one
        if (num_slices == 0) {
            sem_post(&deliver);
        }
    }
    return NULL;
}

void* delivery(void* arg) {
    while (1) {
        // Wait until a new pizza order is placed
        sem_wait(&deliver);

        // Simulate pizza preparation and delivery
        printf("Pizza delivery in progress...\n");
        sleep(2); // Simulate the delivery time

        // Refill the pizza slices (protected by mutex)
        pthread_mutex_lock(&mutex);
        num_slices = MAX_SLICES;
        printf("Pizza delivered. Slices available: %d\n", num_slices);
        pthread_mutex_unlock(&mutex);

        // Release the semaphore for the available slices
        for (int i = 0; i < MAX_SLICES; i++) {
            sem_post(&pizza);
        }
    }
    return NULL;
}

int main() {
    pthread_t students[5];
    pthread_t pizza_delivery;

    // Initialize semaphores and mutex
    sem_init(&pizza, 0, 0);
    sem_init(&deliver, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    // Create the delivery thread
    pthread_create(&pizza_delivery, NULL, delivery, NULL);

    // Create the student threads
    for (long i = 0; i < 5; i++) {
        pthread_create(&students[i], NULL, student, (void*)i);
    }

    // Simulate study time
    sleep(10);
    must_study = 0;

    // Wait for all student threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(students[i], NULL);
    }

    // Destroy semaphores and mutex
    sem_destroy(&pizza);
    sem_destroy(&deliver);
    pthread_mutex_destroy(&mutex);

    return 0;
}
