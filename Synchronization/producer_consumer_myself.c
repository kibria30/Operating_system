#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>

#define NUM_CONSUMERS 3
#define NUM_PRODUCERS 4
#define BUFFER_SIZE 5
//this program is designed to have equal or more producers than consumers
//if consumers are more than producers some consumer will wait indefinitely

int buffer[BUFFER_SIZE];
int back = 0, front = 0;
sem_t empty;
sem_t full;
sem_t mutex;

void print_buffer(){
    printf("Buffer now: ");
    if (back == front) {
        printf("Buffer is empty\n");
    } else {
        int i = front;
        do {
            printf("%d ", buffer[i]);
            i = (i + 1) % BUFFER_SIZE;
        } while (i != back);
        printf("\n");
    }
}

void *producer(void *args){
    int produced_no = *(int *)args + 1;
    int produced_item = rand() % 100;

    sem_wait(&empty);
    sem_wait(&mutex);
    printf("%d is produced by %dth producer\n", produced_item, produced_no);
    buffer[back] = produced_item;
    back = (back + 1) % BUFFER_SIZE;
    print_buffer();
    sem_post(&mutex);
    sem_post(&full);

    usleep(2000000);
    return NULL;
}

void *consumer(void *args){
    int consumer_no = *(int *)args + 1;

    sem_wait(&full);
    sem_wait(&mutex);
    int consumed_item = buffer[front];
    front = (front + 1) % BUFFER_SIZE;
    printf("%d is consumed by %dth consumer\n", consumed_item, consumer_no);
    print_buffer();
    sem_post(&mutex);
    sem_post(&empty);
    
    usleep(2000000);
    return NULL;
}

int main(){
    pthread_t producer_threads[NUM_PRODUCERS];
    pthread_t consumer_threads[NUM_CONSUMERS];

    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);
    srand(time(NULL));

    int *producer_args[NUM_PRODUCERS], *consumer_args[NUM_CONSUMERS];
    for(int i=0; i<NUM_PRODUCERS; i++){
        producer_args[i] = malloc(sizeof(int));
        *producer_args[i] = i;
        pthread_create(&producer_threads[i], NULL, producer, producer_args[i]);
    }

    for(int i=0; i<NUM_CONSUMERS; i++){
        consumer_args[i] = malloc(sizeof(int));
        *consumer_args[i] = i;
        pthread_create(&consumer_threads[i], NULL, consumer, consumer_args[i]);
    }

    for(int i=0; i<NUM_PRODUCERS; i++){
        pthread_join(producer_threads[i], NULL);
    }
    
    for(int i=0; i<NUM_CONSUMERS; i++){
        pthread_join(consumer_threads[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}