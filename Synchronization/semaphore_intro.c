#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_PRINTERS 2

sem_t printerSemaphore;

void *printDocument(void *arg) {
    int docNumber = *((int *)arg);
    
    sem_wait(&printerSemaphore);
    printf("Printing Document %d\n", docNumber);
    sleep(2);    
    sem_post(&printerSemaphore);
    
    return NULL;
}

int main() {
    pthread_t threads[5];
    sem_init(&printerSemaphore, 0, MAX_PRINTERS);
    
    int i;
    for (i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, printDocument, &i);
    }
    
    for (i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
    
    sem_destroy(&printerSemaphore);
    
    return 0;
}
