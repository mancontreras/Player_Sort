//Manuel Eduardo Contreras Flores - A01707142 

#pragma once
#include <vector>
#include <utility> // para usar swap()

// función para dividir el arreglo con el esquema de Lomuto
// básicamente deja todos los menores que el pivote a la izq y los mayores a la der
// Complejidad: recorre de l a r una sola vez -> O(n)
template <class T, class Cmp>
int partition_lomuto(std::vector<T>& a, int l, int r, Cmp cmp) {
    T pivot = a[r]; // agarro el último como pivote
    int i = l;      // este va marcando dónde termina la parte "chica"
    for (int j = l; j < r; ++j) { // recorro de izq a der, O(n)
        if (cmp(a[j], pivot)) {   // si este elemento es menor que el pivote
            std::swap(a[i], a[j]); // lo paso al lado "chico"
            i++;                  // muevo la frontera
        }
    }
    std::swap(a[i], a[r]); // pongo el pivote en medio (en su lugar correcto)
    return i;              // regreso la posición del pivote
}

// implementación del QuickSort usando recursión
// Promedio: O(n log n)   Peor caso: O(n^2)   Memoria: O(log n) por la pila de recursión
template <class T, class Cmp>
void quickSort(std::vector<T>& a, int l, int r, Cmp cmp) {
    if (l >= r) return;                        // caso base, nada que ordenar
    int p = partition_lomuto(a, l, r, cmp);    // divido el arreglo, O(n)
    quickSort(a, l, p - 1, cmp);               // ordeno la parte izq
    quickSort(a, p + 1, r, cmp);               // ordeno la parte der
}

// versión cortita para llamar sin pasar índices
// nomás le dices el vector y ya
template <class T, class Cmp>
void quickSort(std::vector<T>& a, Cmp cmp) {
    if (!a.empty()) quickSort(a, 0, (int)a.size() - 1, cmp);
}

