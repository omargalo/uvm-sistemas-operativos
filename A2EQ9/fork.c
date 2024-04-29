#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid;
    pid = fork();

    if (pid == -1) {
        // Error, falló la llamada a fork()
        perror("Fallo la llamada a fork");
        return 1;
    } else if (pid == 0) {
        // Este bloque se ejecuta en el proceso hijo
        printf("Proceso hijo: PID = %d, Padre PID = %d\n", getpid(), getppid());
    } else {
        // Este bloque se ejecuta en el proceso padre
        printf("Proceso padre: PDI = %d, Hijo PID = %d\n", getpid(), pid);
    }
    // Ambos procesos se ejecutan en este bloque
    printf("Ambos procesos se ejecutan aqui.\n");

    return 0;
}
