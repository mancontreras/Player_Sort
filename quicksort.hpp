#pragma once
#include <functional>
#include <utility>
#include "csv.hpp"

// Nodo de lista doblemente ligada
struct Node {
    Player data;
    Node* prev = nullptr;
    Node* next = nullptr;

    Node(const Player& p) : data(p) {}
    Node() = default;
};

// ==========================================
// PARTITION (Lomuto para lista doble)
// ==========================================
static Node* partitionDLL(Node* l, Node* h,
        const std::function<bool(const Player&, const Player&)>& cmp)
{
    Player pivot = h->data;
    Node* i = l->prev;

    for (Node* j = l; j != h; j = j->next) {
        if (cmp(j->data, pivot)) {     // <--- comparación estricta
            i = (i == nullptr) ? l : i->next;
            std::swap(i->data, j->data);
        }
    }

    i = (i == nullptr) ? l : i->next;
    std::swap(i->data, h->data);
    return i;
}

// ==========================================
// QUICK SORT RECURSIVO
// ==========================================
static void quickSortDLL(Node* l, Node* h,
        const std::function<bool(const Player&, const Player&)>& cmp)
{
    if (!l || !h || l == h) return;
    if (h->next == l) return;  

    Node* p = partitionDLL(l, h, cmp);

    if (p && p != l)
        quickSortDLL(l, p->prev, cmp);

    if (p && p != h)
        quickSortDLL(p->next, h, cmp);
}

// ==========================================
// LIMPIAR LA LISTA
// ==========================================
static inline void deleteDLL(Node* head) {
    while (head) {
        Node* next = head->next;
        delete head;
        head = next;
    }
}
