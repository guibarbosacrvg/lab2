#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <limits.h>

#define V_SIZE 10000
#define NUM_PROC 10


// 
int main (int argc, char *argv[]){
    /* int segmento, id, pid, status;
    char* msg = argv[1];
    char* p;
    segmento = shmget(7000, sizeof (char) * strlen(msg) + 1, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    p = (char *) shmat(segmento,0 ,0);
    strcpy(p, msg);
    printf("%d", segmento); */
    
    int segmento, segmento2, segmento_time, id, pid, status;
    int *p, *p2;
    clock_t *p_time;
    segmento = shmget(IPC_PRIVATE, sizeof(int) * V_SIZE, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    segmento2 = shmget(IPC_PRIVATE, sizeof(int) * NUM_PROC, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    segmento_time = shmget(IPC_PRIVATE, sizeof(clock_t) * 2, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    p_time = (clock_t *) shmat(segmento_time,0 ,0);
    p = (int *) shmat(segmento,0 ,0);
    p2 = (int *) shmat(segmento2,0 ,0);
    for(int i = 0; i < V_SIZE; i++){
        p[i] = 5;
    }
    printf("%d\n", segmento);

    p_time[0] = INT_MAX; p_time[1] = INT_MIN; 
    int soma = 0;
    int i = 0; 
    while(i < NUM_PROC){
        pid = fork();
        if(pid == 0){
            clock_t temp = clock();
            if (temp < p_time[0])
                p_time[0] = temp;
            
            for(int j = V_SIZE/NUM_PROC * i; j < V_SIZE/NUM_PROC * (i + 1); j++){
                p[j] = p[j] * 2;
                soma += p[j];
            }
            p2[i] = soma;
            temp = clock();
            if (temp > p_time[1])
                p_time[1] = temp;
            exit(0);
        }
        i++;
    }
    for(int i = 0; i < V_SIZE; i++){
        wait(&status);
    }

    int sum_total = 0;
    for(int i = 0; i < NUM_PROC; i++){
        sum_total = sum_total + p2[i];
    }
    printf("%d\n", sum_total);
    printf("%f - %f\n", (double)p_time[0], (double)p_time[1]);
    printf("%f\n", (double)(p_time[1] - p_time[0]) / CLOCKS_PER_SEC);
    return 0;
}
