#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void createZombie() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork fallo");
    } else if (pid == 0) {
        // Proceso hijo termina inmediatamente creando un proceso zombi
        printf("Proceso hijo se vuelve zombi PID: %d\n", getpid());
        exit(0);
    } else {
        // Proceso padre se suspende mientras el proceso hijo se vuelve zombi
        sleep(5);
        printf("Proceso hijo-zombi PID: %d\n", pid);
    }
}

void createOrphan() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork fallo");
    } else if (pid == 0) {
        // Proceso hijo se vuelve huerfano cuando el padre termina muy rapido
        printf("Proceso hijo se vuelve huerfano PID: %d\n", getpid());
        // Mantenemos al proceso hijo vivo el suficiente tiempo para asegurar
        // que el proceso padre exista
        sleep(5);
        printf("Proceso huerfano es adoptado por el proceso PID: %d\n", getpid());
    } else {
        // Proceso padre termina rapidamente potencialmente creando un 
        // proceso huerfano
        printf("Proceso padre termina PID: %d\n", getpid());
    }
}

int main() {
    printf("Proceso main PID: %d\n", getpid());

    createZombie();
    // Tiempod espera para observar el proceso zombi utilizando
    // la herramienta del sistema: htop
    sleep(10);
    
    printf("\nCreando un proceso huerfano:\n");
    createOrphan();
    // Tiempo para mostrar el huefano en la lista de procesos
    sleep(1);

    return 0;
}