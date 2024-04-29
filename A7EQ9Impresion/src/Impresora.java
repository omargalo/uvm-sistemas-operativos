public class Impresora {
    private static Impresora instancia;
    // Objeto de bloqueo para la sincronización
    private final Object lock = new Object();

    // Constructor privado para el patrón Singleton
    private Impresora() {
    }

    // Método para obtener la instancia de la impresora
    public static Impresora getInstancia() {
        if (instancia == null) {
            synchronized (Impresora.class) {
                if (instancia == null) {
                    instancia = new Impresora();
                }
            }
        }
        return instancia;
    }

    // Método para imprimir un documento
    public void imprimir(String documento) {
        synchronized (lock) {
            System.out.println("Imprimiendo documento: " + documento);
            // Simulación del tiempo de impresión
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                System.out.println("Impresión interrumpida");
            }
            System.out.println("Documento impreso: " + documento);
        }
    }
}
