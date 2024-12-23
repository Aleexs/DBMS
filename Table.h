#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include <map>
#include "IndexManager.h"  // Asegúrate de incluir el encabezado correctamente

class Tabla {
public:
    IndexManager indexManager;  // Ahora debería reconocer la clase IndexManager
    Tabla() = default;
    Tabla(const std::string& tablaNombre);

    void agregarAtributo(const std::string& atributoNombre, const std::string& atributoTipo);
    void mostrarAtributos() const;
    bool esValido() const;
    std::string getTablaNombre() const;
    const std::vector<std::pair<std::string, std::string>>& getAtributos() const;

    void agregarRegistro(const std::vector<std::string>& registro);
    const std::vector<std::vector<std::string>>& getRegistros() const;

    void insertarIndice(const std::string& atributo, const std::string& valor, size_t posicion);
    void mostrarTabla() const;

private:
    std::string tablaNombre;
    std::vector<std::pair<std::string, std::string>> atributos;
    std::vector<std::vector<std::string>> registros;
};

#endif
