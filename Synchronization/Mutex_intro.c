#include <stdio.h>
#include <pthread.h>

pthread_mutex_t accountMutex = PTHREAD_MUTEX_INITIALIZER;
int accountBalance = 0;

void *deposit(void *arg) {
    int amount = *((int *)arg);
    pthread_mutex_lock(&accountMutex);
    
    accountBalance += amount;
    printf("Deposited %d dollars. New balance: %d\n", amount, accountBalance);
    
    pthread_mutex_unlock(&accountMutex);
    return NULL;
}

void *withdraw(void *arg) {
    int amount = *((int *)arg);
    pthread_mutex_lock(&accountMutex);
    
    if (accountBalance >= amount) {
        accountBalance -= amount;
        printf("Withdrawn %d dollars. New balance: %d\n", amount, accountBalance);
    } else {
        printf("Insufficient balance for withdrawal.\n");
    }
    
    pthread_mutex_unlock(&accountMutex);
    return NULL;
}

int main() {
    pthread_t threads[2];
    int depositAmount = 100;
    int withdrawAmount = 50;
    
    pthread_create(&threads[0], NULL, deposit, &depositAmount);
    pthread_create(&threads[1], NULL, withdraw, &withdrawAmount);
    
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    
    return 0;
}
