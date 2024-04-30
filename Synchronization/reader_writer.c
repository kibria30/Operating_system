#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdlib.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

sem_t rw_mutex;
sem_t mutex;
int read_count=0;

void *writer(void *args){
    int writer_no = *(int *)args+1;
    sem_wait(&rw_mutex);
    printf("%dth writer is writing.\n", writer_no);
    sem_post(&rw_mutex);
    usleep(2000000);
    return NULL;
}

void *reader(void *args){
    int reader_no = *(int *)args+1;
    sem_wait(&mutex);
    read_count++;
    if(read_count == 1){
        sem_wait(&rw_mutex);
    }
    printf("%dth reader is reading.\n", reader_no);
    sem_post(&mutex);

    printf("%dth reader finished reading.\n", reader_no);
    sem_wait(&mutex);
    read_count--;
    if(read_count == 0){
        sem_post(&rw_mutex);
    }
    sem_post(&mutex);
    usleep(2000000);
    return NULL;
}

int main(){
    pthread_t reader_threads[NUM_READERS];
    pthread_t writer_threads[NUM_WRITERS];
    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);

    int i, j;
    int *reader_args[NUM_READERS];
    for(i=0; i<NUM_READERS; i++){
        reader_args[i] = malloc(sizeof(int));
        *reader_args[i] = i;
        pthread_create(&reader_threads[i], NULL, reader, reader_args[i]);
    }
    
    int *writer_args[NUM_WRITERS];
    for(j=0; j<NUM_WRITERS; j++){
        writer_args[j] = malloc(sizeof(int));
        *writer_args[j] = j;
        pthread_create(&writer_threads[j], NULL, writer, writer_args[j]);
    }

    for(i=0; i<NUM_READERS; i++){
        pthread_join(reader_threads[i], NULL);
    }
    for(j=0; j<NUM_WRITERS; j++){
        pthread_join(writer_threads[j], NULL);
    }

    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);
    return 0;
}