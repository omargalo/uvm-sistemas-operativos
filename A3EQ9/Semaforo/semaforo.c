#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

/*
sem_t: Declara la variable sem de tipo sem_t, que se usa para representar el semáforo.
Los semáforos son mecanismos de sincronización que se utilizan para controlar el
acceso a recursos compartidos por múltiples hilos o procesos.
*/
sem_t semaforo;

// Contador compartido
int contador = 0;

// Función que incrementa el contador
void* incrementar(void* arg) {
    // Identificador para el hilo
    int id = *(int*)arg; 
    for (int i = 0; i < 10; i++) {
        /*
        sem_wait: Esta función es llamada antes de que un hilo acceda al recurso compartido.
        Disminuye el valor del semáforo (si es mayor que cero) o bloquea el hilo si el
        valor es cero, hasta que otro hilo libere el semáforo. Esto asegura que solo un
        hilo pueda incrementar el contador a la vez, previniendo condiciones de carrera.
        */
        sem_wait(&semaforo);
        printf("Hilo %d incrementando el contador de %d a %d\n", id, contador, contador + 1);
        contador++;
        /*
        sem_post: Incrementa el valor del semáforo, señalando que el hilo ha terminado de
        usar el recurso compartido. Si otros hilos estaban esperando, uno de ellos podrá
        proceder y acceder al recurso.
        */
        sem_post(&semaforo);
    }
    return NULL;
}

int main() {
    /*
    pthread_t: Define las variables hilo1 y hilo2 de tipo pthread_t, que son identificadores
    para los hilos que se van a crear. En pthread, este tipo se utiliza para almacenar
    información sobre los hilos.
    */
    pthread_t hilo1, hilo2;
    int id1 = 1, id2 = 2;

    /*
    sem_init: Inicializa el semáforo sem. El segundo argumento 0 indica que el semáforo se
    usa para sincronización entre hilos del mismo proceso. El tercer argumento 1 establece
    el valor inicial del semáforo a 1, lo que significa que solo un hilo puede acceder
    al recurso compartido (el contador) a la vez.
    */
    sem_init(&semaforo, 0, 1);

    printf("Iniciando hilos...\n");

    /*
    pthread_create: Esta función se usa para crear nuevos hilos. Toma cuatro parámetros:
    una referencia al pthread_t, atributos del hilo (en este caso NULL para los
    atributos por defecto), la función que el hilo ejecutará (en este caso incrementar),
    y un puntero a los argumentos que se pasarán a la función del hilo. En el código,
    se pasan id1 y id2 como argumentos a los hilos, permitiendo identificar cada hilo
    en la salida.
    */
    pthread_create(&hilo1, NULL, incrementar, &id1);
    pthread_create(&hilo2, NULL, incrementar, &id2);

    /*
    pthread_join: Esta función espera a que el hilo especificado termine. Asegura que
    el programa principal no finalizará hasta que ambos hilos hayan completado su
    ejecución. Esto evita que el programa termine prematuramente, permitiendo que
    los hilos completen su trabajo de incrementar el contador.
    */
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    /*
    sem_destroy: Libera los recursos ocupados por el semáforo. Esto se hace al final
    del programa, después de que se haya completado el trabajo de los hilos.
    */
    sem_destroy(&semaforo);

    printf("Valor final del contador: %d\n", contador);

    return 0;
}
