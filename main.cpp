#include <iostream>
#include "SchemaManager.h"
#include "BufferManager.h"

int main(){
    SchemaManager schemaManager;
    schemaManager.cargarSchema("Schema.txt");

    std::cout<<"Tablas cargadas:"<<std::endl;
    schemaManager.mostrarTablas();

    BufferManager bufferManager(3);

    std::cout<<"\nObteniendo paginas del buffer..."<<std::endl;

    std::string pagina1 = bufferManager.getPagina("actor", 1, schemaManager);
    std::cout<<"Pagina 1 de actor cargada: "<<pagina1.substr(0, 50)<<"...\n";

    std::string pagina2 = bufferManager.getPagina("actor", 2, schemaManager);
    std::cout<<"Pagina 2 de actor cargada: "<<pagina2.substr(0, 50)<<"...\n";

    std::string pagina3 = bufferManager.getPagina("address", 1, schemaManager);
    std::cout<<"Pagina 1 de address cargada: "<<pagina3.substr(0, 50)<<"...\n";

    std::string pagina4 = bufferManager.getPagina("actor", 3, schemaManager);
    std::cout<<"Pagina 3 de actor cargada: "<<pagina4.substr(0, 50)<<"...\n";

    std::cout<<"\nContenido del buffer después de cargar 4 paginas:"<<std::endl;
    bufferManager.mostrarBufferContenido();

    std::string pagina5 = bufferManager.getPagina("actor", 1, schemaManager);
    std::cout<<"Pagina 1 de actor (cargada nuevamente): "<<pagina5.substr(0, 50)<<"...\n";

    std::cout<<"\nContenido del buffer final:"<<std::endl;
    bufferManager.mostrarBufferContenido();

    return 0;
}
