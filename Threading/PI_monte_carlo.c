#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TOTAL_POINTS 1000000
#define NUM_THREADS 100

int points_in_circle = 0;

void *monte_carlo(void *arg) {
    int points_per_thread = TOTAL_POINTS / NUM_THREADS;
    int i;
    double x, y;

    for (i = 0; i < points_per_thread; i++) {
        x = (double)rand() / RAND_MAX * 2 - 1;
        y = (double)rand() / RAND_MAX * 2 - 1;
        
        if (x*x + y*y <= 1) {
            points_in_circle++;
        }
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int i;

    srand(time(NULL));

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, monte_carlo, NULL);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    double pi_estimate = 4.0 * points_in_circle / TOTAL_POINTS;
    printf("Estimated value of pi: %lf\n", pi_estimate);

    return 0;
}
