## Resultados

El programa ejecuta dos hilos que incrementan un contador compartido 6 veces cada uno. Al finalizar ambos hilos, el contador debería tener un valor final de 12, en la consola se observa la secuencia de operaciones donde cada hilo incrementa el contador junto con mensajes que indican el inicio de la operación, el hilo que está actuando y el valor del contador antes y después de la operación. Finalmente, se muestra el valor final del contador.

## Archivos

Un único archivo fuente en C, usualmente con la extensión .c (semaforo.c) que contiene la implementación completa del programa. Tras compilar el código fuente en un sistema como Ubuntu, se genera un archivo ejecutable comúnmente sin extensión (/bin/semaforo).

## Posibles problemáticas

Aunque el uso de semáforos está destinado a evitar condiciones de carrera al acceder al recurso compartido (el contador), una implementación incorrecta o el uso inadecuado de semáforos podrían aún permitir condiciones de carrera. En este código, si se omite sem_wait o sem_post accidentalmente podría resultar en un acceso concurrente no sincronizado al contador. Si el semáforo no se libera correctamente después de ser adquirido (por ejemplo, si se omite sem_post después de sem_wait), puede conducir a un deadlock o interbloqueo donde un hilo permanece esperando indefinidamente.

El uso excesivo de semáforos puede causar un rendimiento menos que óptimo debido a la espera innecesaria de los hilos. Problemas como la liberación de un semáforo que nunca se solicito, intentar solicitar un semáforo demasiadas veces, o no inicializar adecuadamente el semáforo pueden causar comportamientos inesperados o fallos en el programa.