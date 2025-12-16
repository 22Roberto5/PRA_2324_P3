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
    int n;
    int max;
    ListLinked<TableEntry<V>>* table;

    int h(std::string key) {
        int sum = 0;
        for (size_t i = 0; i < key.length(); i++) {
            sum += int(key.at(i));
        }
        return sum % max;
    }

public:
    HashTable(int size) : n(0), max(size) {
        table = new ListLinked<TableEntry<V>>[max];
    }

    ~HashTable() {
        delete[] table;
    }

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

    V search(std::string key) override {
        int pos = h(key);
        TableEntry<V> entry(key);

        int found = table[pos].search(entry);
        if (found == -1) {
            throw std::runtime_error("Clave no encontrada");
        }

        return table[pos].get(found).value;
    }

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

    int entries() override {
        return n;
    }

    int capacity() {
        return max;
    }

    V operator[](std::string key) {
        return search(key);
    }

    friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& th) {
        for (int i = 0; i < th.max; i++) {
            out << i << ": " << th.table[i] << std::endl;
        }
        return out;
    }
};

#endif

