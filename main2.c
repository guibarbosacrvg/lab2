#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#define V_SIZE 10000

int main (int argc, char *argv[]){
    clock_t begin, end;
    int vec[V_SIZE];
    for(int i = 0; i < V_SIZE; i++){
        vec[i] = 5;
    }
    int sum_total = 0;
    begin = clock();
    for(int i = 0; i < V_SIZE; i++){
        vec[i] *= 2;
        sum_total += vec[i];
    }
    end = clock();
    printf("%d\n", sum_total);
    printf("Time: %f\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return 0;
}
