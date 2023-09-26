// Guilherme Barbosa de Mattos - 2111691
// Thomaz Miranda - 2110527

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main() {
    int segmento;
    char *p;
    segmento = shmget(7000, 0, 0);
    if (segmento == -1) {
        perror("shmget");
        return 1;
    }

    p = (char *)shmat(segmento, 0, 0);
    if (p == (char *)(-1)) {
        perror("shmat");
        return 1;
    }

    printf("Message from shared memory: %s\n", p);

    if (shmdt(p) == -1) {
        perror("shmdt");
        return 1;
    }

    return 0;
}
