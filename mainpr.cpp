/*
Manuel Eduardo Contreras Flores - A01707142
Proyecto Player_Sort
*/

/*
Manuel Eduardo Contreras Flores - A01707142
Proyecto Player_Sort
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cctype>

#include "csv.hpp"       // carga CSV y struct Player
#include "quicksort.hpp" // quickSort plantilla Lomuto

// --------------------------------------------------------------
// Estructura auxiliar para mostrar datos ordenados
// --------------------------------------------------------------
struct Row {
    std::string name;
    double val;
};

// --------------------------------------------------------------
// Convierte string a minúsculas (para comparar nombres)
// --------------------------------------------------------------
static std::string toLower(const std::string& s) {
    std::string out = s;
    std::transform(out.begin(), out.end(), out.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return out;
}

// --------------------------------------------------------------
// Imprime una tabla con nombres y valores
// Complejidad temporal: O(n)
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
// Guarda un jugador nuevo en el CSV
// Complejidad: O(1)
// --------------------------------------------------------------
static bool guardarJugadorCSV(const std::string& file, const Player& p) {
    std::ofstream out(file, std::ios::app);
    if (!out.is_open()) return false;

    out << p.name << "," << p.PTS << "," << p.REB << "," << p.AST
        << "," << p.STL << "," << p.BLK << "\n";
    return true;
}

// --------------------------------------------------------------
// Registra un nuevo jugador desde consola
// Complejidad: O(n) por búsqueda de duplicados
// --------------------------------------------------------------
static void registrarJugador(std::vector<Player>& players, const std::string& csvFile) {
    Player p;
    std::cout << "\n--- Registro de Jugador ---\n";
    std::cout << "Nombre: ";
    std::getline(std::cin >> std::ws, p.name);

    // Verificar duplicados
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
// Menú principal
// --------------------------------------------------------------
int main() {
    std::string csvFile = "sample_players_basket.csv";
    std::vector<Player> players;
    std::string err;

    // Cargar CSV
    if (!loadPlayers(csvFile, players, err)) {
        std::cout << "⚠️ No se pudieron cargar jugadores: " << err << "\n";
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
            std::vector<Row> data;
            std::string metric;

            for (auto& p : players) {
                double val = 0;
                switch(opcion) {
                    case 1: val = p.PTS; metric = "PTS"; break;
                    case 2: val = p.REB; metric = "REB"; break;
                    case 3: val = p.AST; metric = "AST"; break;
                    case 4: val = p.STL; metric = "STL"; break;
                    case 5: val = p.BLK; metric = "BLK"; break;
                }
                data.push_back({p.name, val});
            }

            int orden;
            std::cout << "1. Ascendente\n2. Descendente\nSeleccione orden: ";
            std::cin >> orden;
            bool asc = (orden == 1);

            // QuickSort (Lomuto)
            // Complejidad temporal:
            //   Mejor: O(n log n), Promedio: O(n log n), Peor: O(n²)
            quickSort(data, [asc](const Row& a, const Row& b) {
                return asc ? a.val < b.val : a.val > b.val;
            });

            printTable(data, metric);

        } else if (opcion == 6) {
            registrarJugador(players, csvFile);
        } else if (opcion != 0) {
            std::cout << "⚠️ Opción no válida.\n";
        }

    } while (opcion != 0);

    std::cout << "👋 Programa finalizado.\n";
    return 0;
}
