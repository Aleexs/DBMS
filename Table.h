#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include <map>

class Tabla{
public:
    Tabla() = default;
    Tabla(const std::string& tablaNombre);
    void agregarAtributo(const std::string& atributoNombre, const std::string& atributoTipo);
    void mostrarAtributos() const;
    void mostrarTabla() const;
    bool esValido() const;
    std::string getTablaNombre() const;
    const std::vector<std::pair<std::string, std::string>>& getAtributos() const; // Nuevo método

private:
    std::string tablaNombre;
    std::vector<std::pair<std::string, std::string>> atributos;
};

#endif
