// Guilherme Barbosa de Mattos - 2111691
// Thomaz Miranda - 2110527

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <limits.h>

int main(int argc, char* argv[]) {
    int segmento, id, pid, status;
    char* temp = (char*)malloc(sizeof(char) * 100);
    char* msg_string = (char*)malloc(sizeof(char) * 100);
    
    msg_string[0] = '\0';

    for (int i = 1; i < argc; i++) {
        strcpy(temp, argv[i]);
        strcat(msg_string, temp);
        strcat(msg_string, " ");
        free(temp);
        temp = (char*)malloc(sizeof(char) * 100);
    }

    char* p;
    segmento = shmget(7000, strlen(msg_string) + 1, IPC_CREAT | IPC_EXCL | 0600);
    if (segmento == -1) {
        perror("shmget");
        return 1;
    }

    p = (char*)shmat(segmento, 0, 0);
    if (p == (char*)(-1)) {
        perror("shmat");
        return 1;
    }

    strcpy(p, msg_string);
    printf("Segment ID: %d\n", segmento);

    // Clean up: Detach from the shared memory segment.
    if (shmdt(p) == -1) {
        perror("shmdt");
        return 1;
    }

    // Free dynamically allocated memory.
    free(temp);
    free(msg_string);

    return 0;
}
