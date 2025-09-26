//Manuel Eduardo Contreras Flores - A01707142 

#include <iostream>   // para imprimir y leer de consola
#include <iomanip>    // para setw (formato de columnas)
#include <vector>     // vector, obvio
#include <string>     // string
#include <utility>    // por si acaso (swap, etc.)
#include <algorithm>  // para std::max()

#include "csv.hpp"        // mi loader del CSV (Player y loadPlayers)
#include "quicksort.hpp"  // mi QuickSort (Lomuto)

struct Row { std::string name; double val; }; // estructura chiquita solo con lo que voy a mostrar

// imprime la tabla en consola -> O(n) porque recorre el vector una vez
static void printTable(const std::vector<Row>& v, const std::string& metric) {
    const int W = 24; // ancho fijo para la columna de Nombre (para que se vea alineado)
    std::cout << "\nNombre" << std::string(std::max(0, W-6),' ') << " | " << metric << "\n";
    std::cout << std::string(W + 3 + (int)metric.size(), '-') << "\n";
    for (auto& r : v) { // O(n)
        // si el nombre está larguísimo, lo recorto y le pongo "…"
        std::string n = r.name.size() > (size_t)W ? r.name.substr(0, W-1)+"…" : r.name;
        std::cout << std::left << std::setw(W) << n << " | " << r.val << "\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false); // acelera IO (no mezcla con stdio C)
    std::cin.tie(nullptr);            // quita flush automático del cout al leer cin

    // archivo fijo para no andar pidiendo ruta cada vez
    const std::string FILE = "sample_players_basket.csv";

    std::vector<Player> players; std::string err;
    // cargar CSV -> O(n) respecto a las filas (parseo simple por línea)
    if (!loadPlayers(FILE, players, err)) {
        std::cerr << "Error al leer '" << FILE << "': " << err << "\n";
        std::cerr << "Pon el CSV en la misma carpeta que el ejecutable o cambia el nombre arriba.\n";
        return 1; // me salgo si no pude cargar
    }

    // menucito con números, sin complicaciones
    std::cout << "=== Basket Stats (QuickSort) ===\n";
    std::cout << "Elige la métrica a ordenar:\n";
    std::cout << "  [0] PTS (puntos)\n";
    std::cout << "  [1] REB (rebotes)\n";
    std::cout << "  [2] AST (asistencias)\n";
    std::cout << "  [3] STL (robos)\n";
    std::cout << "  [4] BLK (bloqueos)\n";
    std::cout << "Opción: ";
    int idx=0; std::cin >> idx;
    if (idx<0 || idx>4) { std::cerr << "Índice inválido.\n"; return 1; }

    std::cout << "Orden:\n";
    std::cout << "  [1] Ascendente (menor -> mayor)\n";
    std::cout << "  [2] Descendente (mayor -> menor)\n";
    std::cout << "Opción: ";
    int ord=2; std::cin >> ord; bool asc = (ord==1);

    // construir un vector auxiliar solo con (Nombre, ValorElegido) -> O(n)
    std::vector<Row> view; view.reserve(players.size()); // reservar ayuda un poco
    const char* names[5] = {"PTS","REB","AST","STL","BLK"};
    auto metricName = std::string(names[idx]);
    for (auto& p : players) { // O(n)
        // saco el valor correspondiente según el índice que eligieron
        double v = (idx==0? p.PTS : idx==1? p.REB : idx==2? p.AST : idx==3? p.STL : p.BLK);
        view.push_back({p.name, v}); // push amortizado O(1)
    }

    // ordenar con mi QuickSort (Lomuto)
    // Complejidad: promedio O(n log n), peor O(n^2), memoria O(log n) por recursión
    if (asc)  quickSort(view, [](const Row& a, const Row& b){ return a.val < b.val; });
    else      quickSort(view, [](const Row& a, const Row& b){ return a.val > b.val; });

    // imprimir tabla -> O(n)
    printTable(view, metricName);
    std::cout << "\nListo. 👍\n";
    return 0; // fin
}


