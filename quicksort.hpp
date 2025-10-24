#pragma once
#include <functional>  // para std::function
#include <utility>     // para std::swap
#include "csv.hpp"     // struct Player

// --------------------------------------------------------------
// Nodo de la lista doblemente ligada
// Contiene un Player y punteros al nodo anterior y siguiente
// --------------------------------------------------------------
struct Node {
    Player data;     // datos del jugador
    Node* prev = nullptr; // puntero al nodo anterior
    Node* next = nullptr; // puntero al nodo siguiente

    // Constructor que recibe un Player
    Node(const Player& p) : data(p), prev(nullptr), next(nullptr) {}

    // Constructor por defecto
    Node() = default;
};

// --------------------------------------------------------------
// Función de partición para QuickSort sobre lista doblemente ligada
// Entrada: l = inicio de la lista, h = fin de la lista
//        cmp = función de comparación entre dos Players
// Salida: puntero al nodo pivote
// Complejidad: O(n) donde n = número de nodos entre l y h
// --------------------------------------------------------------
Node* partitionDLL(Node* l, Node* h, std::function<bool(const Player&, const Player&)> cmp) {
    Player pivot = h->data; // el pivote es el último nodo
    Node* i = l->prev;      // i marca el último nodo menor que pivot

    // Recorre todos los nodos desde l hasta h-1
    for (Node* j = l; j != h; j = j->next) {
        // Si j es menor que el pivote según cmp
        if (cmp(j->data, pivot)) {
            // Avanza i o inicialízalo si es nullptr
            i = (i == nullptr) ? l : i->next;
            // Intercambia los datos de i y j
            std::swap(i->data, j->data);
        }
    }

    // Coloca el pivote en su posición final
    i = (i == nullptr) ? l : i->next;
    std::swap(i->data, h->data);

    return i; // retorna nodo pivote
}

// --------------------------------------------------------------
// QuickSort recursivo para lista doblemente ligada
// Entrada: l = inicio de la lista, h = fin de la lista
//        cmp = función de comparación entre dos Players
// Complejidad:
//   Mejor caso: O(n log n) (cuando el pivote divide la lista de manera equilibrada)
//   Promedio:   O(n log n)
//   Peor caso:  O(n²) (cuando siempre se elige un pivote desfavorable, lista ya ordenada o casi ordenada)
// Memoria: O(log n) por la pila de llamadas recursivas
// --------------------------------------------------------------
void quickSortDLL(Node* l, Node* h, std::function<bool(const Player&, const Player&)> cmp) {
    // Solo ordena si hay al menos 2 nodos
    if (h != nullptr && l != h && l != h->next) {
        // Particiona la lista y obtiene el pivote
        Node* p = partitionDLL(l, h, cmp);

        // Ordena recursivamente la sublista izquierda
        quickSortDLL(l, p->prev, cmp);

        // Ordena recursivamente la sublista derecha
        quickSortDLL(p->next, h, cmp);
    }
}
