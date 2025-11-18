/*
Manuel Eduardo Contreras Flores - A01707142
Proyecto Player_Sort - Avance 3 (Final)
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cctype>
#include "csv.hpp"
#include "quicksort.hpp"

// Convertir string a minúsculas
static std::string toLower(const std::string& s) {
    std::string out = s;
    std::transform(out.begin(), out.end(), out.begin(),
        [](unsigned char c){ return std::tolower(c); });
    return out;
}

struct Row { 
    std::string name; 
    double val; 
};

static void printTable(const std::vector<Row>& v, const std::string& metric) {
    const int W = 24;
    std::cout << "\nNombre" << std::string(std::max(0, W-6),' ') << " | " << metric << "\n";
    std::cout << std::string(W + 3 + (int)metric.size(), '-') << "\n";
    for (auto& r : v) {
        std::string n = r.name.size() > (size_t)W ? r.name.substr(0, W-1) + "…" : r.name;
        std::cout << std::left << std::setw(W) << n << " | " << r.val << "\n";
    }
}

static bool appendJugadorCSV(const std::string& file, const Player& p) {
    std::ofstream out(file, std::ios::app);
    if (!out.is_open()) return false;
    out << p.name << "," << p.PTS << "," << p.REB << "," << p.AST
        << "," << p.STL << "," << p.BLK << "\n";
    return true;
}

std::vector<Player> dllToVector(Node* head) {
    std::vector<Player> v;
    Node* curr = head;
    while (curr) {
        v.push_back(curr->data);
        curr = curr->next;
    }
    return v;
}

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

void registrarJugador(std::vector<Player>& players, const std::string& csvFile) {
    Player p;
    std::cout << "\n--- Registro de Jugador ---\nNombre: ";
    std::getline(std::cin >> std::ws, p.name);

    for (const auto& existing : players) {
        if (toLower(existing.name) == toLower(p.name)) {
            std::cout << "⚠️ El jugador ya existe.\n"; 
            return;
        }
    }

    std::cout << "PTS: "; std::cin >> p.PTS;
    std::cout << "REB: "; std::cin >> p.REB;
    std::cout << "AST: "; std::cin >> p.AST;
    std::cout << "STL: "; std::cin >> p.STL;
    std::cout << "BLK: "; std::cin >> p.BLK;

    players.push_back(p);

    if (appendJugadorCSV(csvFile, p)) 
        std::cout << "✅ Registrado y guardado.\n";
    else 
        std::cout << "⚠️ Error al guardar en archivo.\n";
}

void buscarJugador(const std::vector<Player>& players) {
    std::string busqueda;
    std::cout << "\nIngrese nombre a buscar: ";
    std::getline(std::cin >> std::ws, busqueda);

    std::string bLower = toLower(busqueda);
    bool found = false;

    std::cout << "\n--- Resultados de Búsqueda ---\n";
    for (const auto& p : players) {
        if (toLower(p.name).find(bLower) != std::string::npos) {
            std::cout << "🏀 " << p.name 
                      << " [PTS:" << p.PTS << " REB:" << p.REB 
                      << " AST:" << p.AST << " STL:" << p.STL << " BLK:" << p.BLK << "]\n";
            found = true;
        }
    }

    if (!found) std::cout << "⚠️ No se encontraron coincidencias.\n";
}

// =======================================================
//                      MAIN
// =======================================================
int main() {
    std::string csvFile = "sample_players_basket.csv";
    std::vector<Player> players;
    std::string err;

    if (!loadPlayers(csvFile, players, err))
        std::cout << "⚠️ " << err << "\n";
    else
        std::cout << "✅ " << players.size() << " jugadores cargados.\n";

    int opcion;
    do {
        std::cout << "\n========= MENÚ FINAL =========\n";
        std::cout << "1-5. Ordenar por Estadistica (PTS, REB, AST, STL, BLK)\n";
        std::cout << "6. Registrar nuevo jugador\n";
        std::cout << "7. Buscar jugador\n";
        std::cout << "8. Exportar lista actual a CSV\n";
        std::cout << "0. Salir\n";
        std::cout << "Opción: ";
        std::cin >> opcion;

        if (opcion >= 1 && opcion <= 5) {
            Node* head = nullptr; 
            Node* tail = nullptr;

            head = buildDLL(players, tail);

            int orden;
            std::cout << "1. Ascendente\n2. Descendente\nOrden: ";
            std::cin >> orden;
            bool asc = (orden == 1);

            // ✔️ FIX: Comparador correcto
            quickSortDLL(head, tail, [opcion, asc](const Player& a, const Player& b){
                double va = 0.0, vb = 0.0;
                switch(opcion){
                    case 1: va = a.PTS; vb = b.PTS; break;
                    case 2: va = a.REB; vb = b.REB; break;
                    case 3: va = a.AST; vb = b.AST; break;
                    case 4: va = a.STL; vb = b.STL; break;
                    case 5: va = a.BLK; vb = b.BLK; break;
                }
                return asc ? va < vb : va > vb;   // Comparación estricta
            });

            players = dllToVector(head);
            deleteDLL(head);

            std::vector<Row> data;
            for (const auto& p : players) {
                double val = (opcion==1?p.PTS:opcion==2?p.REB:
                              opcion==3?p.AST:opcion==4?p.STL:p.BLK);
                data.push_back({p.name, val});
            }

            printTable(data, (opcion==1?"PTS":opcion==2?"REB":
                              opcion==3?"AST":opcion==4?"STL":"BLK"));

        } 
        else if (opcion == 6) {
            registrarJugador(players, csvFile);
        } 
        else if (opcion == 7) {
            buscarJugador(players);
        } 
        else if (opcion == 8) {
            std::string fName;
            std::cout << "Nombre del archivo a guardar (ej: reporte.csv): ";
            std::cin >> fName;

            std::string error;
            if (saveAllPlayers(fName, players, error))
                std::cout << "✅ Archivo guardado correctamente.\n";
            else
                std::cout << "⚠️ " << error << "\n";
        }

    } while (opcion != 0);

    std::cout << "👋 Bye.\n";
    return 0;
}
