#include "BufferManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "SchemaManager.h"

BufferManager::BufferManager(size_t maxPaginas) : maxPaginas(maxPaginas){}

Pagina BufferManager::cargarPaginaArchivo(const std::string& tablaNombre, int paginaNumero, const SchemaManager& schemaManager) {
    std::ifstream file("Schema/" + tablaNombre + ".txt");
    if (!file) {
        std::cerr<<"Error: No se puede abrir el archivo de la tabla "<<tablaNombre<<std::endl;
        return {"", -1, ""};
    }

    const int filasPorPagina = 10;
    int lineaInicio = paginaNumero * filasPorPagina;
    int lineaFin = lineaInicio + filasPorPagina;

    std::string linea;
    std::ostringstream dataStream;
    int contadorLineas = 0;

    while (std::getline(file, linea)) {
        if (contadorLineas >= lineaInicio && contadorLineas < lineaFin) {
            dataStream<<linea<<"\n";
        }
        if (contadorLineas >= lineaFin) {
            break;
        }
        contadorLineas++;
    }

    if (dataStream.str().empty()) {
        std::cerr<<"Advertencia: La pagina "<<paginaNumero<<" de la tabla "<<tablaNombre<<" está vacia\n";
        return {"", -1, ""};
    }

    Pagina pagina = {tablaNombre, paginaNumero, dataStream.str()};
    return pagina;
}



std::string BufferManager::getPagina(const std::string& tablaNombre, int paginaNumero, const SchemaManager& schemaManager){
    std::string paginaKey = tablaNombre + "_" + std::to_string(paginaNumero);

    if (paginaMap.find(paginaKey) != paginaMap.end()){
        paginaLista.splice(paginaLista.begin(), paginaLista, paginaMap[paginaKey]);
        return paginaMap[paginaKey]->data;
    }
    if (paginaLista.size() >= maxPaginas){
        paginaMap.erase(paginaLista.back().tablaNombre + "_" + std::to_string(paginaLista.back().paginaNumero));
        paginaLista.pop_back();
    }
    Pagina pagina = cargarPaginaArchivo(tablaNombre, paginaNumero, schemaManager);
    paginaLista.push_front(pagina);
    paginaMap[paginaKey] = paginaLista.begin();

    return pagina.data;
}

void BufferManager::mostrarBufferContenido() const{
    std::cout<<"Contenido del Buffer (LRU):\n";
    for (const auto& pagina : paginaLista){
        std::cout<<"Tabla: "<<pagina.tablaNombre<<" | Pagina: "<<pagina.paginaNumero<<std::endl;
    }
}