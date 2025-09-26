//Manuel Eduardo Contreras Flores - A01707142 

#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <cctype>

// estructura simple para guardar datos de un jugador
// cada jugador trae su nombre y sus stats (inicializadas en 0)
struct Player {
    std::string name;
    double PTS=0, REB=0, AST=0, STL=0, BLK=0;
};

// función que parte una línea de texto en pedazos separados por comas
// básicamente sirve para leer cada campo del CSV
// Complejidad: O(longitud de la línea)
static inline std::vector<std::string> splitCSV(const std::string& line) {
    std::vector<std::string> out;
    std::string cell;
    std::stringstream ss(line);
    while (std::getline(ss, cell, ',')) out.push_back(cell); // recorre todo el string
    return out;
}

// convierte un string a minúsculas (ej: "PTS" -> "pts")
// Complejidad: O(tamaño del string)
static inline std::string lower(std::string s) {
    for (auto& c : s) c = std::tolower((unsigned char)c);
    return s;
}

// función para cargar jugadores desde un archivo CSV
// lee cabecera, luego cada fila y la mete al vector out
// Complejidad total: O(n) siendo n el número de filas del CSV
inline bool loadPlayers(const std::string& path, std::vector<Player>& out, std::string& err) {
    std::ifstream in(path);
    if (!in) { err = "No se pudo abrir: " + path; return false; }

    // leo la primera línea (cabecera con los nombres de columnas)
    std::string header;
    if (!std::getline(in, header)) { err = "CSV vacío."; return false; }
    auto H = splitCSV(header);

    // guardo en un mapa qué columna corresponde a qué campo
    std::unordered_map<std::string,int> idx;
    for (int i=0;i<(int)H.size();++i) idx[lower(H[i])] = i;

    // si no existe la columna "name" no sirve el archivo
    if (!idx.count("name")) { err = "Falta columna 'name'."; return false; }

    std::string line;
    // leo línea por línea (cada una es un jugador) -> O(n)
    while (std::getline(in, line)) {
        if (line.empty()) continue; // si viene vacía la salto
        auto cols = splitCSV(line); // divido la línea en columnas
        Player p;
        if (idx["name"] < (int)cols.size()) p.name = cols[idx["name"]];

        // mini función interna para asignar stats (PTS, REB, etc.)
        // Complejidad: O(1) por campo porque solo hace un acceso y un stod
        auto setNum = [&](const char* key, double& field){
            auto k = lower(key);
            if (idx.count(k)) {
                int j = idx[k];
                if (j < (int)cols.size() && !cols[j].empty()) {
                    try { field = std::stod(cols[j]); } // convierto string a double
                    catch(...) { field = 0.0; }        // si falla, lo dejo en 0
                }
            }
        };

        // le asigno todos los stats
        setNum("PTS", p.PTS);
        setNum("REB", p.REB);
        setNum("AST", p.AST);
        setNum("STL", p.STL);
        setNum("BLK", p.BLK);

        // si el jugador tiene nombre válido lo meto al vector
        if (!p.name.empty()) out.push_back(p);
    }

    // si no encontré nada válido, regreso error
    if (out.empty()) { err = "No se hallaron filas válidas."; return false; }
    return true; // todo salió bien
}
