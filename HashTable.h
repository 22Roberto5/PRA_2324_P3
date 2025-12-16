#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>

#include "Dict.h"
#include "TableEntry.h"
#include "../PRA_2324_P1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {

private:
    int n;                          // número de elementos
    int max;                        // número de cubetas
    ListLinked<TableEntry<V>>* table;

    // Función hash
    int h(std::string key) {
        int sum = 0;
        for (size_t i = 0; i < key.length(); i++) {
            sum += int(key.at(i));
        }
        return sum % max;
    }

public:
    // Constructor
    HashTable(int size) : n(0), max(size) {
        table = new ListLinked<TableEntry<V>>[max];
    }

    // Destructor
    ~HashTable() {
        delete[] table;
    }

    // Inserta un par clave->valor
    void insert(std::string key, V value) override {
        int pos = h(key);
        TableEntry<V> entry(key, value);

        if (table[pos].search(entry) != nullptr) {
            throw std::runtime_error("Clave duplicada");
        }

        table[pos].insert(entry);
        n++;
    }

    // Busca un valor por clave
    V search(std::string key) override {
        int pos = h(key);
        TableEntry<V> entry(key);

        TableEntry<V>* found = table[pos].search(entry);
        if (found == nullptr) {
            throw std::runtime_error("Clave no encontrada");
        }

        return found->value;
    }

    // Elimina una entrada
    V remove(std::string key) override {
        int pos = h(key);
        TableEntry<V> entry(key);

        TableEntry<V>* found = table[pos].search(entry);
        if (found == nullptr) {
            throw std::runtime_error("Clave no encontrada");
        }

        V value = found->value;
        table[pos].remove(entry);
        n--;
        return value;
    }

    // Número de entradas
    int entries() override {
        return n;
    }

    // Número de cubetas
    int capacity() {
        return max;
    }

    // Operador []
    V operator[](std::string key) {
        return search(key);
    }

    // Salida por pantalla
    friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& th) {
        for (int i = 0; i < th.max; i++) {
            out << i << ": ";
            out << th.table[i] << std::endl;
        }
        return out;
    }
};

#endif

