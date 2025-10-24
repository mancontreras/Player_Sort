/*
Manuel Eduardo Contreras Flores - A01707142
Proyecto Player_Sort - Avance 2
Uso de lista doblemente ligada y QuickSort sobre DLL
*/

#include <iostream>   // para std::cout, std::cin
#include <iomanip>    // para std::setw y formateo de salida
#include <vector>     // para std::vector
#include <string>     // para std::string
#include <algorithm>  // para std::transform
#include <fstream>    // para std::ofstream
#include <cctype>     // para std::tolower
#include "csv.hpp"    // funciones para leer CSV y struct Player
#include "quicksort.hpp" // funciones QuickSort sobre DLL

// --------------------------------------------------------------
// Convierte string a minúsculas
// Entrada: s (string)
// Salida: copia de s en minúsculas
// Complejidad: O(n) donde n = longitud del string
// --------------------------------------------------------------
static std::string toLower(const std::string& s) {
    std::string out = s; 
    std::transform(out.begin(), out.end(), out.begin(),
                   [](unsigned char c){ return std::tolower(c); }); 
    return out;
}

// --------------------------------------------------------------
// Estructura auxiliar para mostrar tabla
// --------------------------------------------------------------
struct Row {
    std::string name; // nombre del jugador
    double val;       // valor de la estadística seleccionada
};

// --------------------------------------------------------------
// Imprime tabla de datos de jugadores
// Complejidad: O(n) donde n = número de jugadores
// --------------------------------------------------------------
static void printTable(const std::vector<Row>& v, const std::string& metric) {
    const int W = 24; 
    std::cout << "\nNombre" << std::string(std::max(0, W-6),' ') << " | " << metric << "\n"; 
    std::cout << std::string(W + 3 + (int)metric.size(), '-') << "\n"; 

    for (auto& r : v) {
        std::string n = r.name.size() > (size_t)W ? r.name.substr(0, W-1) + "…" : r.name; 
        std::cout << std::left << std::setw(W) << n << " | " << r.val << "\n"; 
    }
}

// --------------------------------------------------------------
// Guardar jugador en CSV
// Entrada: file (archivo CSV), p (Player)
// Salida: true si se escribió correctamente
// Complejidad: O(1) por cada jugador
// --------------------------------------------------------------
static bool guardarJugadorCSV(const std::string& file, const Player& p) {
    std::ofstream out(file, std::ios::app); 
    if (!out.is_open()) return false; 
    out << p.name << "," << p.PTS << "," << p.REB << "," << p.AST
        << "," << p.STL << "," << p.BLK << "\n"; 
    return true;
}

// --------------------------------------------------------------
// Registrar jugador desde consola
// Entrada: players (vector de jugadores), csvFile (archivo CSV)
// Complejidad: Mejor caso O(1), Promedio/Peor caso O(n) por verificar duplicados
// --------------------------------------------------------------
static void registrarJugador(std::vector<Player>& players, const std::string& csvFile) {
    Player p; 
    std::cout << "\n--- Registro de Jugador ---\n"; 

    std::cout << "Nombre: "; 
    std::getline(std::cin >> std::ws, p.name); 

    for (const auto& existing : players) {
        if (toLower(existing.name) == toLower(p.name)) {
            std::cout << "⚠️ El jugador '" << p.name << "' ya existe. Registro cancelado.\n";
            return; 
        }
    }

    std::cout << "PTS: "; std::cin >> p.PTS;
    std::cout << "REB: "; std::cin >> p.REB;
    std::cout << "AST: "; std::cin >> p.AST;
    std::cout << "STL: "; std::cin >> p.STL;
    std::cout << "BLK: "; std::cin >> p.BLK;

    players.push_back(p); 
    if (guardarJugadorCSV(csvFile, p))
        std::cout << "✅ Jugador registrado y guardado en CSV correctamente.\n";
    else
        std::cout << "⚠️ No se pudo guardar el jugador en el archivo.\n";
}

// --------------------------------------------------------------
// Construye lista doblemente ligada a partir del vector de jugadores
// Entrada: vector de Player
// Salida: puntero a head y tail de la DLL
// Complejidad: O(n), n = número de jugadores
// --------------------------------------------------------------
Node* buildDLL(const std::vector<Player>& players, Node*& tail) {
    Node* head = nullptr;  
    tail = nullptr;        
    Node* prev = nullptr;  

    for (auto& p : players) {
        Node* n = new Node(p); 
        if (!head) head = n;  
        n->prev = prev;        
        if (prev) prev->next = n; 
        prev = n;              
    }

    tail = prev; 
    return head;
}

// --------------------------------------------------------------
// Menú principal
// Complejidad general:
// Lectura CSV: O(n)
// Construcción DLL: O(n)
// QuickSort DLL: promedio O(n log n), peor O(n²)
// Impresión tabla: O(n)
// --------------------------------------------------------------
int main() {
    std::string csvFile = "sample_players_basket.csv"; 
    std::vector<Player> players; 
    std::string err; 

    if (!loadPlayers(csvFile, players, err)) {
        std::cout << "⚠️ " << err << "\n"; 
    }

    int opcion;
    do {
        std::cout << "\n========= MENÚ PRINCIPAL =========\n";
        std::cout << "1. Ordenar por PTS\n";
        std::cout << "2. Ordenar por REB\n";
        std::cout << "3. Ordenar por AST\n";
        std::cout << "4. Ordenar por STL\n";
        std::cout << "5. Ordenar por BLK\n";
        std::cout << "6. Registrar nuevo jugador\n";
        std::cout << "0. Salir\n";
        std::cout << "=================================\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        if (opcion >= 1 && opcion <= 5) {
            Node* head = nullptr; 
            Node* tail = nullptr; 
            head = buildDLL(players, tail); 

            int orden;
            std::cout << "1. Ascendente\n2. Descendente\nSeleccione orden: ";
            std::cin >> orden;
            bool asc = (orden == 1);

            quickSortDLL(head, tail, [opcion, asc](const Player& a, const Player& b){
                double va=0, vb=0;
                switch(opcion){
                    case 1: va=a.PTS; vb=b.PTS; break;
                    case 2: va=a.REB; vb=b.REB; break;
                    case 3: va=a.AST; vb=b.AST; break;
                    case 4: va=a.STL; vb=b.STL; break;
                    case 5: va=a.BLK; vb=b.BLK; break;
                }
                return asc ? va < vb : va > vb;
            });

            std::vector<Row> data;
            for (Node* n=head; n!=nullptr; n=n->next)
                data.push_back({n->data.name, (opcion==1?n->data.PTS:opcion==2?n->data.REB:
                                                  opcion==3?n->data.AST:opcion==4?n->data.STL:n->data.BLK)});
            printTable(data, (opcion==1?"PTS":opcion==2?"REB":opcion==3?"AST":opcion==4?"STL":"BLK"));

        } else if (opcion == 6) {
            registrarJugador(players, csvFile);
        } else if (opcion != 0) {
            std::cout << "⚠️ Opción no válida.\n";
        }

    } while (opcion != 0); 

    std::cout << "👋 Programa finalizado.\n";
    return 0;
}
