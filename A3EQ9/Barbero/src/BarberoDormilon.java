import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.Queue;
import java.util.LinkedList;

public class BarberoDormilon {

    private static final int NUM_SILLAS = 2;
    private static final int TOTAL_CLIENTES = 13;
    // Semáforo para controlar el número de sillas de espera disponibles
    private static Semaphore sillasEspera = new Semaphore(NUM_SILLAS);
    // Semáforo para sincronizar la llegada de nuevos clientes
    private static Semaphore clienteListo = new Semaphore(0);
    // Contador para seguir el progreso de los clientes atendidos
    private static AtomicInteger clientesAtendidos = new AtomicInteger(0);
    // Cola para gestionar el orden de llegada de los clientes
    private static Queue<Integer> colaClientes = new LinkedList<>();
    // Variable para controlar si el barbero está dormido o no
    private static boolean estaDurmiendo = true;
    // Semáforo para controlar el acceso al sillón del barbero
    private static Semaphore sillonesBarbero = new Semaphore(1);

    public static void main(String[] args) {
        // Hilo del barbero
        Thread barbero = new Thread(BarberoDormilon::barbero, "Barbero");
        barbero.start();

        for (int i = 1; i <= TOTAL_CLIENTES; i++) {
            int clienteId = i;
            // Hilos de los clientes
            Thread cliente = new Thread(() -> cliente(clienteId), "Cliente " + clienteId);
            cliente.start();
            try {
                // Simula la llegada aleatoria de los clientes
                Thread.sleep((long) (Math.random() * 1000));
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }

    private static void barbero() {
        while (clientesAtendidos.get() < TOTAL_CLIENTES) {
            try {
                // Espera a que llegue un cliente
                clienteListo.acquire();
                if (estaDurmiendo) {
                    System.out.println("El barbero ha sido despertado por un cliente");
                    estaDurmiendo = false;
                }
                Integer clienteId = null;
                synchronized (colaClientes) {
                    if (!colaClientes.isEmpty()) {
                        // Toma el siguiente cliente de la cola
                        clienteId = colaClientes.poll();
                    }
                }
                if (clienteId != null) {
                    try {
                        // Adquiere el sillón del barbero
                        sillonesBarbero.acquire();
                        System.out.println("El barbero está afeitando al cliente " + clienteId + ".");
                        // Simula el tiempo que toma afeitar a un cliente
                        Thread.sleep(500);
                        System.out.println("El barbero ha terminado con el cliente " + clienteId + ".");
                        // Incrementa el contador de clientes atendidos
                        clientesAtendidos.incrementAndGet();
                    } finally {
                        // Libera el sillón del barbero después de atender al cliente
                        sillonesBarbero.release();
                    }
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
        if (!estaDurmiendo) {
            System.out.println("¡Fue un gran día! El barbero se va a dormir.");
            estaDurmiendo = true;
        }
        System.out.println("Todos los clientes han sido atendidos.");
        // Finaliza el programa correctamente
        System.exit(0);
    }

    private static void cliente(int clienteId) {
        try {
            // Intenta adquirir una silla de espera
            if (sillasEspera.tryAcquire()) {
                System.out.println("Cliente " + clienteId + " está esperando.");
                synchronized (colaClientes) {
                    // Agrega el cliente a la cola
                    colaClientes.add(clienteId);
                    // Indica al barbero que un cliente está listo
                    clienteListo.release();
                }
                // Simula el tiempo que el cliente pasa sentado antes de ser atendido
                Thread.sleep(100);
                // No libera la silla de espera aquí, se libera después de que el cliente es atendido o decide irse
            } else {
                System.out.println("Cliente " + clienteId + " se ha ido, no hay sillas disponibles.");
                // Sale del programa si no hay sillas de espera disponibles para un cliente
                System.exit(0);
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        } finally {
            // Libera la silla de espera solo si el cliente es atendido o decide irse
            sillasEspera.release();
        }
    }
}
