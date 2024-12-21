#include "Table.h"
#include <iostream>

Tabla::Tabla(const std::string& tablaNombre) : tablaNombre(tablaNombre){}

void Tabla::agregarAtributo(const std::string& atributoNombre, const std::string& atributoTipo){
    atributos.push_back({atributoNombre, atributoTipo});
}

void Tabla::mostrarAtributos() const{
    for (const auto& attribute : atributos){
        std::cout<<"  Attribute: "<<attribute.first<<" ("<<attribute.second<<")"<<std::endl;
    }
}

void Tabla::mostrarTabla() const{
    std::cout<<"Tabla: "<<tablaNombre<<std::endl;
    mostrarAtributos();
}

bool Tabla::esValido() const{
    return !tablaNombre.empty() && !atributos.empty();
}

std::string Tabla::getTablaNombre() const{
    return tablaNombre;
}

const std::vector<std::pair<std::string, std::string>>& Tabla::getAtributos() const{
    return atributos;
}
