#ifndef DICT_H
#define DICT_H

#include <string>
#include <stdexcept>

template <typename V>
class Dict {
public:
    // Inserta key->value. Error si la clave ya existe.
    virtual void insert(std::string key, V value) = 0;

    // Devuelve el valor asociado a key. Error si no existe.
    virtual V search(std::string key) = 0;

    // Elimina una entrada. Error si no existe.
    virtual V remove(std::string key) = 0;

    // Devuelve cuántos elementos tiene el diccionario.
    virtual int entries() = 0;

    // Destructor virtual obligatorio en clases abstractas
    virtual ~Dict() {}
};

#endif

