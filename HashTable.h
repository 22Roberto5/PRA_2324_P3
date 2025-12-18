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
    int n;                      // número de elementos
    int max;                    // capacidad
    ListLinked<TableEntry<V>>* table;

    // Función hash
    int h(std::string key) const {
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

    // Inserción
    void insert(std::string key, V value) override {
        int pos = h(key);
        TableEntry<V> entry(key, value);

        int found = table[pos].search(entry);
        if (found != -1) {
            throw std::runtime_error("Clave duplicada");
        }

        table[pos].insert(table[pos].size(), entry);
        n++;
    }

    // Búsqueda
    V search(std::string key) override {
        int pos = h(key);
        TableEntry<V> entry(key);

        int found = table[pos].search(entry);
        if (found == -1) {
            throw std::runtime_error("Clave no encontrada");
        }

        return table[pos].get(found).value;
    }

    // Eliminación
    V remove(std::string key) override {
        int pos = h(key);
        TableEntry<V> entry(key);

        int found = table[pos].search(entry);
        if (found == -1) {
            throw std::runtime_error("Clave no encontrada");
        }

        V value = table[pos].get(found).value;
        table[pos].remove(found);
        n--;
        return value;
    }

    // Número de entradas
    int entries() override {
        return n;
    }

    // Capacidad
    int capacity() const {
        return max;
    }

    // Operador []
    V operator[](std::string key) {
        return search(key);
    }

    // ---------- MÉTODO PEDIDO EN EL ENUNCIADO ----------
    HashTable<V> rehash() {
        // Nueva tabla con el doble de capacidad
        HashTable<V> newTable(2 * max);

        // Reinsertar todos los elementos
        for (int i = 0; i < max; i++) {
            for (int j = 0; j < table[i].size(); j++) {
                TableEntry<V> entry = table[i].get(j);
                newTable.insert(entry.key, entry.value);
            }
        }

        return newTable;
    }
    // ---------------------------------------------------

    // Impresión
    friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& th) {
        for (int i = 0; i < th.max; i++) {
            out << i << ": " << th.table[i] << std::endl;
        }
        return out;
    }
};

#endif

