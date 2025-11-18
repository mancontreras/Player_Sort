#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm> 
#include <cctype>

// Estructura para guardar datos de un jugador
struct Player {
    std::string name;
    double PTS=0, REB=0, AST=0, STL=0, BLK=0;
};

// Función auxiliar para limpiar basura (espacios, comillas, \r)
static inline std::string clean(std::string s) {
    if (s.empty()) return s;
    size_t start = 0;
    while (start < s.size() && (std::isspace((unsigned char)s[start]) || s[start] == '\"')) start++;
    
    size_t end = s.size();
    while (end > start && (std::isspace((unsigned char)s[end-1]) || s[end-1] == '\"')) end--;
    
    return s.substr(start, end - start);
}

// Función para partir una línea CSV
static inline std::vector<std::string> splitCSV(const std::string& line) {
    std::vector<std::string> out;
    std::string cell;
    std::stringstream ss(line);
    while (std::getline(ss, cell, ',')) {
        out.push_back(clean(cell)); // IMPORTANTE: Limpiamos cada celda
    }
    return out;
}

// Convertir string a minúsculas
static inline std::string lower(std::string s) {
    for (auto& c : s) c = std::tolower((unsigned char)c);
    return s;
}

// Cargar jugadores desde CSV
inline bool loadPlayers(const std::string& path, std::vector<Player>& out, std::string& err) {
    std::ifstream in(path);
    if (!in) { err = "No se pudo abrir: " + path; return false; }

    std::string header;
    if (!std::getline(in, header)) { err = "CSV vacío."; return false; }

    // Eliminar BOM (Byte Order Mark) si existe (común en Excel)
    if (header.size() >= 3 && (unsigned char)header[0]==0xEF && (unsigned char)header[1]==0xBB && (unsigned char)header[2]==0xBF) {
        header = header.substr(3);
    }

    auto H = splitCSV(header);

    std::unordered_map<std::string,int> idx;
    for (int i=0;i<(int)H.size();++i) idx[lower(H[i])] = i;

    if (!idx.count("name")) { err = "Falta columna 'name' (Revisa cabeceras)."; return false; }

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        auto cols = splitCSV(line);
        Player p;
        if (idx["name"] < (int)cols.size()) p.name = cols[idx["name"]];

        auto setNum = [&](const char* key, double& field){
            auto k = lower(key);
            if (idx.count(k)) {
                int j = idx[k];
                if (j < (int)cols.size() && !cols[j].empty()) {
                    try { 
                        std::string val = cols[j];
                        // Asegurar que usamos punto decimal
                        std::replace(val.begin(), val.end(), ',', '.');
                        field = std::stod(val); 
                    }
                    catch(...) { field = 0.0; }
                }
            }
        };

        setNum("PTS", p.PTS); setNum("REB", p.REB);
        setNum("AST", p.AST); setNum("STL", p.STL); setNum("BLK", p.BLK);

        if (!p.name.empty()) out.push_back(p);
    }
    if (out.empty()) { err = "No se hallaron filas válidas."; return false; }
    return true;
}

// Función para guardar toda la lista
inline bool saveAllPlayers(const std::string& path, const std::vector<Player>& players, std::string& err) {
    std::ofstream out(path);
    if (!out) { err = "No se pudo crear el archivo: " + path; return false; }

    out << "name,PTS,REB,AST,STL,BLK\n";
    for (const auto& p : players) {
        out << p.name << "," << p.PTS << "," << p.REB << "," << p.AST
            << "," << p.STL << "," << p.BLK << "\n";
    }
    return true;
}