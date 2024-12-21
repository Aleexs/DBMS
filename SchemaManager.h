#ifndef SCHEMAMANAGER_H
#define SCHEMAMANAGER_H

#include <string>
#include <map>
#include <vector>
class BufferManager;
#include "Table.h"

class SchemaManager{
public:
    SchemaManager();
    void cargarSchema(const std::string& schemaArchivo);
    void mostrarTablas() const;
    void mostrarContenidoTablas(const std::string& tablaNombre) const;
    std::string formatearRegistro(const std::string& tablaNombre, const std::string& registro) const;
    const Tabla* obtenerTabla(const std::string& tablaNombre) const;

    std::string obtenerPagina(const std::string& tablaNombre, int paginaNumero, BufferManager& bufferManager);

private:
    std::map<std::string, Tabla> tablas;
};

#endif
