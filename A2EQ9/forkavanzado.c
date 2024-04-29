#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void ejecutarTarea(char *name) {
    const int NUM_TIMES = 2;
    for (int i = 0; i < NUM_TIMES; i++) {
        int sleepTime = rand() % 4;
        printf("%s Iniciando paso %d, suspender por %d segundos\n", name, i, sleepTime);
        sleep(sleepTime);
        printf("%s Completado paso %d\n", name, i);
    }
}

int main(int argc, char *argv[]) {
    printf("Iniciando proceso main PID: %d\n", (int) getpid());

    pid_t pid = fork();
    srand((int) pid);
    printf("fork() returned: %d\n", (int) pid);

    if (pid < 0) {
        perror("Fallo fork");
        return 1;
    }

    if (pid == 0) {
        // Proceso hijo
        printf("Proceso hijo PID: %d\n", (int) getpid());
        ejecutarTarea("Hijo");
        // Proceso hijo existe con el codigo de status 42
        exit(33);
    }

    // Este bloque se ejecuta solamente por el proceso padre
    printf("Proceso pade PID: %d, esperando al proceso hijo\n", (int) getpid());

    int status;
    pid_t childpid = wait(&status);
    printf("Proceso hijo %d termino\n", (int) childpid);
    if (WIFEXITED(status)) {
        int childReturnValue = WEXITSTATUS(status);
        printf("Proceso hijo termino con codigo de status %d\n", childReturnValue);
    } else {
        printf("Proceso hijo termino de manera anormal");
    }

    return 0;
}