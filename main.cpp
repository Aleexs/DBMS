#include "SchemaManager.h"
#include "BufferManager.h"
#include <iostream>

int main() {
    // Crear un objeto de SchemaManager
    SchemaManager schemaManager;

    // Cargar un archivo de esquema (usando un nombre de archivo válido)
    schemaManager.cargarSchema("Schema.txt");

    // Crear índice sobre una tabla y una columna específica
    schemaManager.crearIndice("customer", "first_name");

    // Buscar índice con un valor específico
    std::vector<size_t> indices = schemaManager.buscarIndice("customer", "first_name", "John");

    // Mostrar los índices encontrados
    if (indices.empty()) {
        std::cout << "No se encontraron índices para el valor 'John' en la columna 'first_name'." << std::endl;
    } else {
        std::cout << "Índices encontrados para 'John': ";
        for (size_t idx : indices) {
            std::cout << idx << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
