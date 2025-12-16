#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {

private:
    BSTree<TableEntry<V>>* tree;

public:
    // Constructor
    BSTreeDict() {
        tree = new BSTree<TableEntry<V>>();
    }

    // Destructor
    ~BSTreeDict() {
        delete tree;
    }

    // Número de entradas
    int entries() override {
        return tree->size();
    }

    // Inserción
    void insert(std::string key, V value) override {
        tree->insert(TableEntry<V>(key, value));
    }

    // Búsqueda
    V search(std::string key) override {
        return tree->search(TableEntry<V>(key)).value;
    }

    // Eliminación
    V remove(std::string key) override {
        TableEntry<V> e = tree->search(TableEntry<V>(key));
        tree->remove(e);
        return e.value;
    }

    // Operador []
    V operator[](std::string key) {
        return search(key);
    }

    // Impresión
    friend std::ostream& operator<<(std::ostream& out, const BSTreeDict<V>& bs) {
        out << *(bs.tree);
        return out;
    }
};

#endif

