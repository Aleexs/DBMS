#ifndef SCHEMAMANAGER_H
#define SCHEMAMANAGER_H

#include <string>
#include <vector>
#include <map>
#include "BufferManager.h"
#include "Table.h"
#include "IndexManager.h"

class SchemaManager {
public:
    SchemaManager();
    void cargarSchema(const std::string& schemaArchivo);
    void mostrarTablas() const;
    void mostrarContenidoTablas(const std::string& tablaNombre) const;
    std::string formatearRegistro(const std::string& tablaNombre, const std::string& registro) const;
    const Tabla* obtenerTabla(const std::string& tablaNombre) const;
    std::string obtenerPagina(const std::string& tablaNombre, int paginaNumero, BufferManager& bufferManager);
    void listarAtributosDeTabla(const std::string& tablaNombre) const;
    void crearIndice(const std::string& tablaNombre, const std::string& columna);
    std::vector<size_t> buscarIndice(const std::string& tablaNombre, const std::string& columna, const std::string& valor) const;

private:
    std::map<std::string, Tabla> tablas;
    std::map<std::string, IndexManager> indices;
};

#endif
