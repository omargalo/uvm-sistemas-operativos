import java.io.IOException;
import java.io.PipedOutputStream;
import java.io.PipedInputStream;

public class App {
    public static void main(String[] args) throws IOException, InterruptedException {
        /*
        Aquí se crean un PipedOutputStream y un PipedInputStream, conectándolos entre sí.
        Este es el mecanismo que permite la comunicación entre hilos:
        un hilo escribe en el PipedOutputStream, y otro hilo lee del PipedInputStream conectado.
        */
        final PipedOutputStream output = new PipedOutputStream();
        final PipedInputStream input = new PipedInputStream(output);
        
        /*
        Hilo 1 es responsable de escribir los datos en el PipedOutputStream.
        Este hilo comienza ejecutando su tarea de escritura inmediatamente después de iniciarse.
         */

        Thread thread1 = new Thread(() -> {
            try {
                System.out.println("Hilo 1: Escribiendo datos...");
                output.write("Equipo 9, Hilo 1".getBytes());
                output.close();
                System.out.println("Hilo 1: Datos escritos y stream cerrado.");
            } catch (IOException e) {
                e.printStackTrace();
            }
        }, "Hilo 1");

        /*
        Hilo 2 lee los datos del PipedInputStream. Comienza su operación de lectura después de
        iniciarse, pero dado que está leyendo de un pipe, se esperará hasta que haya
        datos disponibles para leer.
         */

        Thread thread2 = new Thread(() -> {
            try {
                System.out.println("Hilo 2: Esperando para leer datos...");
                int data = input.read();
                while (data != -1) {
                    System.out.print((char) data);
                    data = input.read();
                }
                System.out.println("\nHilo 2: Datos leídos y stream cerrado.");
                input.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }, "Hilo 2");

        /*
        La concurrencia en este escenario se maneja a través del bloqueo implícito del
        PipedInputStream. Cuando thread2 intenta leer del input, si no hay datos
        disponibles (porque thread1 aún no ha escrito nada), se bloqueará hasta que
        thread1 escriba datos en el output y los cierre.
         */

        thread1.start();
        thread2.start();

        // Espera a que ambos hilos terminen
        thread1.join();
        thread2.join();
    }
}
