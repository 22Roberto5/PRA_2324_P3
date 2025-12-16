#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {

private:
    int nelem;
    BSNode<T>* root;

    // --- BÚSQUEDA ---
    BSNode<T>* search(BSNode<T>* n, T e) const {
        if (n == nullptr) {
            throw std::runtime_error("Elemento no encontrado");
        }
        if (e == n->elem) {
            return n;
        }
        if (e < n->elem) {
            return search(n->left, e);
        } else {
            return search(n->right, e);
        }
    }

    // --- INSERCIÓN ---
    BSNode<T>* insert(BSNode<T>* n, T e) {
        if (n == nullptr) {
            nelem++;
            return new BSNode<T>(e);
        }
        if (e == n->elem) {
            throw std::runtime_error("Elemento duplicado");
        }
        if (e < n->elem) {
            n->left = insert(n->left, e);
        } else {
            n->right = insert(n->right, e);
        }
        return n;
    }

    // --- RECORRIDO INORDEN ---
    void print_inorder(std::ostream& out, BSNode<T>* n) const {
        if (n != nullptr) {
            print_inorder(out, n->left);
            out << n->elem << " ";
            print_inorder(out, n->right);
        }
    }

    // --- MÁXIMO ---
    T max(BSNode<T>* n) const {
        if (n->right == nullptr) {
            return n->elem;
        }
        return max(n->right);
    }

    // --- ELIMINAR MÁXIMO ---
    BSNode<T>* remove_max(BSNode<T>* n) {
        if (n->right == nullptr) {
            BSNode<T>* left = n->left;
            delete n;
            return left;
        }
        n->right = remove_max(n->right);
        return n;
    }

    // --- ELIMINACIÓN ---
    BSNode<T>* remove(BSNode<T>* n, T e) {
        if (n == nullptr) {
            throw std::runtime_error("Elemento no encontrado");
        }
        if (e < n->elem) {
            n->left = remove(n->left, e);
        } else if (e > n->elem) {
            n->right = remove(n->right, e);
        } else {
            // nodo encontrado
            nelem--;
            if (n->left == nullptr) {
                BSNode<T>* right = n->right;
                delete n;
                return right;
            }
            if (n->right == nullptr) {
                BSNode<T>* left = n->left;
                delete n;
                return left;
            }
            // dos hijos: reemplazo por máximo del subárbol izquierdo
            n->elem = max(n->left);
            n->left = remove_max(n->left);
        }
        return n;
    }

    // --- DESTRUCTOR RECURSIVO ---
    void delete_cascade(BSNode<T>* n) {
        if (n != nullptr) {
            delete_cascade(n->left);
            delete_cascade(n->right);
            delete n;
        }
    }

public:
    // --- CONSTRUCTOR ---
    BSTree() : nelem(0), root(nullptr) {}

    // --- TAMAÑO ---
    int size() const {
        return nelem;
    }

    // --- BÚSQUEDA ---
    T search(T e) const {
        return search(root, e)->elem;
    }

    T operator[](T e) const {
        return search(e);
    }

    // --- INSERCIÓN ---
    void insert(T e) {
        root = insert(root, e);
    }

    // --- ELIMINACIÓN ---
    void remove(T e) {
        root = remove(root, e);
    }

    // --- IMPRESIÓN ---
    friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst) {
        bst.print_inorder(out, bst.root);
        return out;
    }

    // --- DESTRUCTOR ---
    ~BSTree() {
        delete_cascade(root);
    }
};

#endif

