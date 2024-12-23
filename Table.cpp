#include "Table.h"
#include <iostream>

Tabla::Tabla(const std::string& tablaNombre) : tablaNombre(tablaNombre) {}

void Tabla::agregarAtributo(const std::string& atributoNombre, const std::string& atributoTipo) {
    atributos.emplace_back(atributoNombre, atributoTipo);
}

void Tabla::mostrarAtributos() const {
    for (const auto& atributo : atributos) {
        std::cout << atributo.first << " (" << atributo.second << ")\n";
    }
}

bool Tabla::esValido() const {
    return !atributos.empty();
}

std::string Tabla::getTablaNombre() const {
    return tablaNombre;
}

const std::vector<std::pair<std::string, std::string>>& Tabla::getAtributos() const {
    return atributos;
}

void Tabla::agregarRegistro(const std::vector<std::string>& registro) {
    registros.push_back(registro);
    // Insertar en los índices
    for (size_t i = 0; i < atributos.size(); ++i) {
        insertarIndice(atributos[i].first, registro[i], registros.size() - 1);  // Usamos la posición del registro
    }
}

const std::vector<std::vector<std::string>>& Tabla::getRegistros() const {
    return registros;
}

void Tabla::insertarIndice(const std::string& atributo, const std::string& valor, size_t posicion) {
    indexManager.insertarIndice(tablaNombre, atributo, valor, posicion);
}

void Tabla::mostrarTabla() const {
    std::cout << "Tabla: " << tablaNombre << "\n";
    for (const auto& registro : registros) {
        for (const auto& campo : registro) {
            std::cout << campo << " ";
        }
        std::cout << "\n";
    }
}
