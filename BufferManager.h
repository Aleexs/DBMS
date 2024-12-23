#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

#include <unordered_map>
#include <list>
#include <string>

class SchemaManager;  // Declaración adelantada de la clase SchemaManager

struct Pagina {
    std::string tablaNombre;
    int paginaNumero;
    std::string data;
};

class BufferManager {
public:
    BufferManager(size_t maxPaginas);

    std::string getPagina(const std::string& tablaNombre, int paginaNumero, const SchemaManager& schemaManager);
    void mostrarBufferContenido() const;

private:
    size_t maxPaginas;
    std::unordered_map<std::string, std::list<Pagina>::iterator> paginaMap;
    std::list<Pagina> paginaLista;

    Pagina cargarPaginaArchivo(const std::string& tablaNombre, int paginaNumero, const SchemaManager& schemaManager);
};

#endif // BUFFERMANAGER_H
