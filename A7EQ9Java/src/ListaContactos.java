import java.util.ArrayList;
import java.util.List;

// Clase ListaContactos utilizando el patrón de diseño Singleton
public class ListaContactos {
    private static ListaContactos instance;
    private List<Contacto> contactos;
    // Objeto de bloqueo para sincronización
    private final Object lock = new Object();

    // Constructor privado para prevenir la instanciación desde fuera
    private ListaContactos() {
        contactos = new ArrayList<>();
    }

    // Método público estático para obtener la instancia Singleton
    public static ListaContactos getInstance() {
        // Verifica si la instancia ya fue creada
        if (instance == null) {
            // Bloque sincronizado para proteger la creación de la instancia
            synchronized (ListaContactos.class) {
                // Doble comprobación para asegurar una única instancia
                if (instance == null) {
                    // Creación de la instancia
                    instance = new ListaContactos();
                }
            }
        }
        return instance;
    }

    // Método para agregar un contacto a la lista con sincronización
    public void agregarContacto(Contacto contacto) {
        // Sincroniza el acceso a la lista de contactos
        synchronized (lock) {
            contactos.add(contacto);
        }
    }

    // Método para mostrar los contactos con sincronización
    public void mostrarContactos() {
        // Sincroniza el acceso a la lista de contactos
        synchronized (lock) {
            System.out.println("Lista de Contactos:");
            for (Contacto contacto : contactos) {
                System.out.println("Nombre: " + contacto.getNombre() +
                        ", Email: " + contacto.getEmail() +
                        ", Teléfono: " + contacto.getTelefono());
            }
        }
    }

    // Clase interna Contacto para almacenar detalles del contacto
    public static class Contacto {
        private String nombre;
        private String email;
        private String telefono;

        public Contacto(String nombre, String email, String telefono) {
            this.nombre = nombre;
            this.email = email;
            this.telefono = telefono;
        }

        // Getters para acceso a las propiedades del contacto
        public String getNombre() { return nombre; }
        public String getEmail() { return email; }
        public String getTelefono() { return telefono; }
    }

    // Método main para ejecutar la aplicación
    public static void main(String[] args) {
        // Obtención de la instancia Singleton de la lista de contactos
        ListaContactos lista = ListaContactos.getInstance();

        // Creación y ejecución de threads para manipular la lista de contactos
        Thread t1 = new Thread(() -> {
            lista.agregarContacto(new Contacto("Garcia Del Carmen Jose Antonio", "a010170693@my.uvm.edu.mx", "5528944468"));
            lista.mostrarContactos();
        });

        Thread t2 = new Thread(() -> {
            lista.agregarContacto(new Contacto("Garcia Lopez Omar", "a040252463@my.uvm.edu.mx", "5529767457"));
            lista.mostrarContactos();
        });

        Thread t3 = new Thread(() -> {
            lista.agregarContacto(new Contacto("Perez Bernal Mauricio Ignacio", "a020227966@my.uvm.edu.mx", "5536590049"));
            lista.mostrarContactos();
        });

        Thread t4 = new Thread(() -> {
            lista.agregarContacto(new Contacto("Saleh Subaie Faissal", "a340450129@my.uvm.edu.mx", "5552184832"));
            lista.mostrarContactos();
        });

        // Inicio de threads
        t1.start();
        t2.start();
        t3.start();
        t4.start();
    }
}
