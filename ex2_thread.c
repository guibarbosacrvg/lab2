#include <pthread.h>
#include <stdio.h>
#define V_SIZE 10000
#define NUM_THREADS 2

struct args {
    int *p;
};

void *thread_function(void *arg_struct) {
    struct args *arg = (struct args *)arg_struct;
    int *p = arg->p;
    for (int i = 0; i < V_SIZE; i++) {
        p[i] *= 2;
        p[i] += 2;
    }
    return NULL;
}

int is_equal(int *p){
    int num = p[0];
    for(int i = 1; i < V_SIZE; i++){
        if(p[i] != num){
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[]){
    int vec[V_SIZE];
    
    for(int i = 0; i < V_SIZE; i++){
        vec[i] = 5;
    }
    
    pthread_t threads[NUM_THREADS];
    struct args arg_struct[NUM_THREADS];

    for(int t = 0; t < NUM_THREADS; t++){
        printf("In main: creating thread %d\n", t);
        arg_struct[t].p = vec;
        pthread_create(&threads[t], NULL, thread_function, (void *)&arg_struct[t]);
    }

    for(int t = 0; t < NUM_THREADS; t++){
        pthread_join(threads[t], NULL);
    }

    for(int i = 0; i < 10; i++){
        printf("%d ", vec[i]);
    }

    if(is_equal(vec)){
        printf("\nTodos os elementos são iguais\n");
    }else{
        printf("\nNem todos os elementos são iguais\n");
    }
    return 0;
}