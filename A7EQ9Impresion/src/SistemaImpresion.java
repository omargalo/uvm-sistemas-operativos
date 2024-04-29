public class SistemaImpresion {
    private Impresora impresora;
    private final Object otroRecurso = new Object();

    public SistemaImpresion() {
        impresora = Impresora.getInstancia();
    }

    // Método para usar ambos recursos: impresora y otro recurso
    public void usarAmbosRecursos(String documento) {
        synchronized (impresora) {
            synchronized (otroRecurso) {
                impresora.imprimir(documento);
                System.out.println("Usando otro recurso junto con la impresora");
            }
        }
    }

    public static void main(String[] args) {
        SistemaImpresion sistema = new SistemaImpresion();
        Thread t1 = new Thread(() -> sistema.usarAmbosRecursos("Actividad1.pdf"));
        Thread t2 = new Thread(() -> sistema.usarAmbosRecursos("Actividad2.pdf"));
        Thread t3 = new Thread(() -> sistema.usarAmbosRecursos("Actividad3.pdf"));
        Thread t4 = new Thread(() -> sistema.usarAmbosRecursos("Actividad4.pdf"));

        t1.start();
        t2.start();
        t3.start();
        t4.start();
    }
}