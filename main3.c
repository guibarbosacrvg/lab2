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
#define NUM_PROC 2

int main(int argc, char *argv[]) {
    int segmento, id, pid, status;
    int *p;
    segmento = shmget(IPC_PRIVATE, sizeof(int) * V_SIZE, 0666);
    p = (int *)shmat(segmento, 0, 0);
    for (int i = 0; i < V_SIZE; i++) {
        p[i] = 5;
    }

    int i = 0;
    while (i < NUM_PROC) {
        pid = fork();
        if (pid == 0) {
            for (int j = V_SIZE / NUM_PROC * i; j < V_SIZE / NUM_PROC * (i + 1); j++) {
                p[j] *= 2;
                p[j] += 2;
            }
            exit(0);
        }
        i++;
    }

    for (int i = 0; i < NUM_PROC; i++) {
        wait(NULL);
    }

    int areEqual = 1;
    for (int i = 1; i < V_SIZE; i++) {
        if (p[i] != p[0]) {
            areEqual = 0;
            break;
        }
    }
    if (areEqual) {
        printf("Todas as posições têm valores iguais: %d\n", p[0]);
    } else {
        printf("Algumas posições têm valores diferentes.\n");
    }

    return 0;
}
