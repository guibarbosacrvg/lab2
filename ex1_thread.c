#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>
#define V_SIZE 10000
#define NUM_THREADS 10

typedef struct args {
    int *p;
    long int sum;
    int start;
    int end;
} args;

void *thread_function(void *arg_struct) {
    args *arg = (args *)arg_struct;
    int *p = arg->p;
    for (int i = arg->start; i < arg->end; i++) {
        p[i] *= 2;
        arg->sum += p[i];
    }
    return NULL;
}

int main(int argc, char* argv[]){
    int vec[V_SIZE];
    
    for (int i = 0; i < V_SIZE; i++) {
        vec[i] = 5;
    }

    pthread_t threads[NUM_THREADS];
    args arg_struct[NUM_THREADS];
    int t = 0;
    long int sum = 0;
    for(t = 0; t < NUM_THREADS; t++){
        printf("In main: creating thread %d\n", t);
        arg_struct[t].p = vec;
        arg_struct[t].start = V_SIZE / NUM_THREADS * t;
        arg_struct[t].end = V_SIZE / NUM_THREADS * (t + 1);
        pthread_create(&threads[t], NULL, thread_function, (void *)&arg_struct[t]);
    }
    for(t = 0; t < NUM_THREADS; t++){
        sum += arg_struct[t].sum;
        pthread_join(threads[t], NULL);
    }
    printf("Soma: %d\n", sum);
    return 0;
}