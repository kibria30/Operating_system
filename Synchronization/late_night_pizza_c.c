#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<time.h>
#define SLICE 5
sem_t pizza, deliver;
pthread_mutex_t mutex;
int slices=0;

void * deliveryThread(void *param)
{
    while(1)
    {
        sem_wait(&deliver);
        printf("Delivering...\n");
        sleep(2);
        slices=5;
        printf("Delivered...\n");
        for(int i=0; i<SLICE; i++)
        sem_post(&pizza);
    }

}
void *student(void *param)
{
    int id = *(int *)param;
    while(1)
    {
        sem_wait(&pizza);
        pthread_mutex_lock(&mutex);
        printf("Student %d is eating...\n", id);
        slices--;
        if(slices<=0)
        {
            sem_post(&deliver);
            printf("Student %d is ordering pizza...\n", id);
        }
        pthread_mutex_unlock(&mutex);
    }
}
int main()
{
    pthread_t delivery, students[5];
    sem_init(&deliver, 0, 1);
    sem_init(&pizza, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    int idx[5];
    pthread_create(&delivery, NULL, (void*)deliveryThread, NULL);
    for(int i=0; i<5; i++)
    {
        idx[i] = i+1;
        pthread_create(&students[i], NULL, (void*)student, &idx[i]);
    }
    pthread_join(delivery, NULL);
    for(int i=0; i<5; i++)
    pthread_join(students[i], NULL);

    // sem_destroy(&delivery);
    // sem_destroy(&pizza);
    // pthread_mutex_destroy(&mutex);
    return 0;
}