#include "SchemaManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "BufferManager.h"
#include "IndexManager.h"

SchemaManager::SchemaManager(){}

void SchemaManager::cargarSchema(const std::string& schemaArchivo) {
    std::ifstream schemaArchivoStream("Schema/" + schemaArchivo);
    std::string line;

    while (getline(schemaArchivoStream, line)) {
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::istringstream ss(line);
        std::string tablaNombre;
        getline(ss, tablaNombre, '#');

        if (tablaNombre.empty()) {
            std::cerr << "Advertencia: La tabla no tiene un formato valido" << std::endl;
            continue;
        }

        Tabla tabla(tablaNombre);
        std::string atributoNombre, atributoTipo;

        while (getline(ss, atributoNombre, '#') && getline(ss, atributoTipo, '#')) {
            if (atributoNombre.empty() || atributoTipo.empty()) {
                std::cerr << "Advertencia: Atributo invalido en la tabla " << tablaNombre << std::endl;
                break;
            }
            tabla.agregarAtributo(atributoNombre, atributoTipo);
        }

        if (tabla.esValido()) {
            tablas[tablaNombre] = tabla;
        } else {
            std::cerr << "Advertencia: La tabla " << tablaNombre << " no tiene un formato valido" << std::endl;
        }
    }
}

void SchemaManager::mostrarTablas() const {
    if (tablas.empty()) {
        std::cout << "No se han cargado tablas" << std::endl;
        return;
    }

    for (const auto& tablaPair : tablas) {
        tablaPair.second.mostrarTabla();
    }
}

void SchemaManager::mostrarContenidoTablas(const std::string& tablaNombre) const {
    std::ifstream tablaFile("Schema/" + tablaNombre + ".txt");
    if (!tablaFile) {
        std::cout << "El archivo de la tabla '" << tablaNombre << "' no existe" << std::endl;
        return;
    }

    std::cout << "Contenido de la tabla '" << tablaNombre << "':" << std::endl;

    std::string line;
    while (getline(tablaFile, line)) {
        std::cout << line << std::endl;
    }
}

std::string SchemaManager::formatearRegistro(const std::string& tablaNombre, const std::string& registro) const {
    auto it = tablas.find(tablaNombre);
    if (it == tablas.end()) {
        return "Error: Tabla no encontrada.";
    }

    const Tabla& tabla = it->second;
    const auto& atributos = tabla.getAtributos();

    std::istringstream ss(registro);
    std::string valor;
    std::ostringstream resultado;

    size_t i = 0;
    while (std::getline(ss, valor, '#') && i < atributos.size()) {
        if (atributos[i].second == "int") {
            try {
                std::stoi(valor);
                resultado << valor;
            } catch (const std::invalid_argument&) {
                std::cerr << "Error: El valor " << valor << " no es un entero válido para el atributo " << atributos[i].first << std::endl;
                return "Error: Valor no válido";
            }
        } else if (atributos[i].second == "str") {
            resultado << valor;
        } else {
            std::cerr << "Error: Tipo de atributo desconocido: " << atributos[i].second << std::endl;
            return "Error: Tipo no soportado";
        }

        if (i < atributos.size() - 1) {
            resultado << " ";
        }
        ++i;
    }

    return resultado.str();
}

const Tabla* SchemaManager::obtenerTabla(const std::string& tablaNombre) const {
    auto it = tablas.find(tablaNombre);
    return (it != tablas.end()) ? &it->second : nullptr;
}

std::string SchemaManager::obtenerPagina(const std::string& tablaNombre, int paginaNumero, BufferManager& bufferManager) {
    return bufferManager.getPagina(tablaNombre, paginaNumero, *this);
}

void SchemaManager::listarAtributosDeTabla(const std::string& tablaNombre) const {
    const Tabla* tabla = obtenerTabla(tablaNombre);
    if (tabla == nullptr) {
        std::cerr << "Error: La tabla '" << tablaNombre << "' no existe." << std::endl;
        return;
    }

    std::cout << "Atributos de la tabla '" << tablaNombre << "':" << std::endl;
    for (const auto& atributo : tabla->getAtributos()) {
        std::cout << "  " << atributo.first << std::endl;
    }
}

void SchemaManager::crearIndice(const std::string& tablaNombre, const std::string& columna) {
    auto it = tablas.find(tablaNombre);
    if (it != tablas.end()) {
        IndexManager index;
        const auto& tabla = it->second;
        const auto& registros = tabla.getRegistros();

        for (size_t i = 0; i < registros.size(); ++i) {
            const std::string& valor = registros[i][0];
            index.insertarIndice(tablaNombre, columna, valor, i);
        }

        indices[tablaNombre] = index;
    }
}

std::vector<size_t> SchemaManager::buscarIndice(const std::string& tablaNombre, const std::string& columna, const std::string& valor) const {
    auto it = indices.find(tablaNombre);
    if (it != indices.end()) {
        return it->second.buscarIndice(tablaNombre, columna, valor);  // Llamada a la función del índice
    }
    return {};  // Devuelve un vector vacío si no se encuentra el índice
}
