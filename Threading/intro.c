#include <stdio.h>
#include <pthread.h>

void *print_1(void *arg) {
    printf("me\n");
    return NULL;
}

void *print_2(void *arg) {
    double *pi = (double *)arg;
    //double pi = *(double *)arg;
    printf("%lf\n", *pi);
    return NULL;
}

int main() {
    pthread_t tid[10];

    pthread_create(&tid[0], NULL, print_1, NULL);
    double pi = 3.1416;
    pthread_create(&tid[1], NULL, print_2, &pi);

    pthread_join(tid[0], NULL);
    pthread_join(tid[0], NULL);

    return 0;
}
