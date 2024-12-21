#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

#include <string>
#include <list>
#include <unordered_map>
#include "SchemaManager.h"  
class SchemaManager;

struct Pagina{
    std::string tablaNombre;
    int paginaNumero;
    std::string data; 
};

class BufferManager{
public:
    BufferManager(size_t maxPaginas);
    std::string getPagina(const std::string& tablaNombre, int paginaNumero, const SchemaManager& schemaManager);
    void mostrarBufferContenido() const;

private:
    size_t maxPaginas;
    std::list<Pagina> paginaLista;
    std::unordered_map<std::string, std::list<Pagina>::iterator> paginaMap;
    Pagina cargarPaginaArchivo(const std::string& tablaNombre, int paginaNumero, const SchemaManager& schemaManager);
};

#endif
