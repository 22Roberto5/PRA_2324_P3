#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

template <typename V>
class TableEntry {
public:
    std::string key;
    V value;

    // Constructores
    TableEntry() : key(""), value() {}

    TableEntry(std::string key) : key(key), value() {}

    TableEntry(std::string key, V value) : key(key), value(value) {}

    // Comparación SOLO por clave
    friend bool operator==(const TableEntry<V>& te1, const TableEntry<V>& te2) {
        return te1.key == te2.key;
    }

    friend bool operator!=(const TableEntry<V>& te1, const TableEntry<V>& te2) {
        return te1.key != te2.key;
    }

    // Salida por pantalla
    friend std::ostream& operator<<(std::ostream& out, const TableEntry<V>& te) {
        out << "(" << te.key << ", " << te.value << ")";
        return out;
    }
};

#endif

