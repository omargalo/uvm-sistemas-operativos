#include <iostream>
#include <vector>
#include <string>
#include <mutex>

// Definición de la estructura Contacto
struct Contacto {
    std::string nombre;
    std::string email;
    std::string telefono;
};

// Clase ListaContactos para manejar los contactos con mutex integrado
class ListaContactos {
private:
    std::vector<Contacto> contactos;
    // Mutex para sincronizar el acceso a la lista de contactos
    mutable std::mutex mtx;

public:
    void agregarContacto(const Contacto& contacto) {
        // Bloqueo automático durante la vida útil del objeto lock
        std::lock_guard<std::mutex> lock(mtx);
        contactos.push_back(contacto);
    }

    void mostrarContactos() const {
        // Asegura que el acceso a contactos sea seguro en entornos multi-thread
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Lista de Contactos:\n";
        for (const auto& contacto : contactos) {
            std::cout << "Nombre: " << contacto.nombre
                << ", Email: " << contacto.email
                << ", Teléfono: " << contacto.telefono << std::endl;
        }
    }
};

int main() {
    ListaContactos listaDeContactos;

    // Añadir algunos contactos
    listaDeContactos.agregarContacto({ "Garcia Del Carmen Jose Antonio", "a010170693@my.uvm.edu.mx", "5528944468" });
    listaDeContactos.agregarContacto({ "Garcia Lopez Omar", "a040252463@my.uvm.edu.mx", "5529767457" });
    listaDeContactos.agregarContacto({ "Perez Bernal Mauricio Ignacio", "a020227966@my.uvm.edu.mx", "5536590049" });
    listaDeContactos.agregarContacto({ "Saleh Subaie Faissal", "a340450129@my.uvm.edu.mx", "5552184832" });

    // Mostrar todos los contactos
    listaDeContactos.mostrarContactos();

    return 0;
}
