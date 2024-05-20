#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_STUDENTS 5
#define PIZZA_SLICES 5

sem_t pizza;  // Number of available pizza resources; init to 0
sem_t deliver;  // init to 1
sem_t slice_mutex;  // Binary semaphore to protect num_slices
int num_slices = 0;

void* student_thread(void* arg) {
    int id = *(int*)arg;
    printf("Student %d started studying\n", id);

    while (1) {
        sem_wait(&pizza);
        sem_wait(&slice_mutex);
        num_slices--;
        printf("Student %d took a slice. Remaining slices: %d\n", id, num_slices);
        sem_post(&slice_mutex);

        // Study while eating the pizza
        printf("Student %d is studying\n", id);

        if (num_slices == 0) {
            printf("No more pizza left. Placing an order...\n");
            sem_wait(&deliver);
            sem_wait(&slice_mutex);
            num_slices = PIZZA_SLICES;
            sem_post(&slice_mutex);
            sem_post(&pizza);
            for (int i = 0; i < PIZZA_SLICES - 1; i++)
                sem_post(&pizza);
            sem_post(&deliver);
        }
    }

    return NULL;
}

void* delivery_thread(void* arg) {
    while (1) {
        sem_wait(&deliver);
        sem_wait(&slice_mutex);
        num_slices = PIZZA_SLICES;
        sem_post(&slice_mutex);
        sem_post(&pizza);
        for (int i = 0; i < PIZZA_SLICES - 1; i++)
            sem_post(&pizza);
        printf("New pizza arrived with %d slices\n", PIZZA_SLICES);
    }

    return NULL;
}

int main() {
    pthread_t student_threads[NUM_STUDENTS], delivery_thread_id;
    int student_ids[NUM_STUDENTS];

    sem_init(&pizza, 0, 0);
    sem_init(&deliver, 0, 1);
    sem_init(&slice_mutex, 0, 1);  // Binary semaphore

    for (int i = 0; i < NUM_STUDENTS; i++) {
        student_ids[i] = i;
        pthread_create(&student_threads[i], NULL, student_thread, &student_ids[i]);
    }

    pthread_create(&delivery_thread_id, NULL, delivery_thread, NULL);

    for (int i = 0; i < NUM_STUDENTS; i++)
        pthread_join(student_threads[i], NULL);

    pthread_join(delivery_thread_id, NULL);

    sem_destroy(&pizza);
    sem_destroy(&deliver);
    sem_destroy(&slice_mutex);

    return 0;
}