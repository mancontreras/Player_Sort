# Proyecto Player_Sort - Avance 3 (Final)
**Autor:** Manuel Eduardo Contreras Flores (A01707142)

## Descripción
Este proyecto es una aplicación en C++ para administrar, analizar y ordenar estadísticas de jugadores de baloncesto. El sistema permite cargar datos desde un archivo CSV, limpiar la información, visualizarla, buscar jugadores específicos, registrar nuevos datos y exportar reportes ordenados.

Ejemplo de archivo base: `sample_players_basket.csv`

## Funcionamiento del Programa

### 1. Carga y Limpieza
Al iniciar, el programa lee el archivo CSV automáticamente. Se utiliza un parser robusto que limpia caracteres basura (como BOM o espacios) y estandariza formatos numéricos.

### 2. Menú Interactivo
El usuario cuenta con las siguientes opciones:
- **[1-5] Ordenar:** Clasifica a los jugadores por PTS, REB, AST, STL o BLK (Ascendente/Descendente).
- **[6] Registrar:** Agrega un jugador validando duplicados (se guarda en el CSV original).
- **[7] Buscar:** Localiza jugadores por nombre (búsqueda parcial).
- **[8] Exportar:** Guarda la lista tal cual está ordenada en ese momento en un **nuevo archivo CSV**.
- **[0] Salir**

---

### SICT0302B: Toma decisiones
**Selecciona y usa una estructura de datos adecuada al problema**

Se optó por una **arquitectura híbrida** para aprovechar las fortalezas de dos estructuras:

1.  **std::vector (Almacenamiento Principal):**
    * Se usa para mantener la base de datos en memoria, realizar búsquedas y gestionar la escritura en archivos. Su acceso aleatorio permite iteraciones rápidas para la exportación.

2.  **Lista Doblemente Ligada (DLL) (Módulo de Ordenamiento):**
    * Para ordenar, los datos se convierten temporalmente a una DLL.
    * *Justificación:* El algoritmo **QuickSort** requiere múltiples intercambios (`swaps`). En una lista ligada, intercambiar elementos es una operación de punteros ($O(1)$) sin necesidad de desplazar bloques de memoria como en un vector.
    * *Gestión de Memoria:* Se implementó una función de limpieza (`deleteDLL`) que libera la memoria dinámica inmediatamente después de ordenar para evitar fugas (*memory leaks*).

---

### SICT0301B: Evalúa los componentes
**Hace un análisis de complejidad correcto y completo del programa final**

A continuación se detalla el análisis asintótico (Big O) de todas las funcionalidades implementadas:

#### 1. Carga de datos (`loadPlayers`)
Lectura secuencial y limpieza de cadenas.
* **Complejidad:** $O(n)$ (Lineal con respecto al número de filas).

#### 2. Ordenamiento (`quickSortDLL`)
Algoritmo QuickSort optimizado para listas dobles.
* **Mejor caso / Promedio:** $O(n \log n)$.
* **Peor caso:** $O(n^2)$ (Si la lista ya está ordenada o existen muchos valores duplicados y el pivote es extremo).
* *Nota:* La conversión entre Vector y DLL es $O(n)$, lo cual no afecta la complejidad dominante del ordenamiento.

#### 3. Búsqueda (`buscarJugador`)
Búsqueda lineal por coincidencia de texto (*substring*).
* **Mejor caso:** $O(1)$ (El jugador está al inicio).
* **Peor caso:** $O(n)$ (No encontrado o está al final de la lista).

#### 4. Exportación / Escritura (`saveAllPlayers`)
Recorrido lineal del vector para escribir en disco un nuevo archivo.
* **Complejidad:** $O(n)$.

#### 5. Registro (`registrarJugador`)
Verificación de duplicados (recorrido) + Inserción al final.
* **Complejidad:** $O(n)$ (Debido a la verificación de existencia antes de insertar).

**Conclusión:**
La complejidad general del programa en el caso promedio es **$O(n \log n)$**, dominada por el proceso de ordenamiento.

---

### SICT0303B: Implementa acciones científicas
**Implementa mecanismos de lectura y escritura de archivos para guardar los datos correctamente**

1.  **Lectura Robusta:**
    Se desarrolló la función `splitCSV` y `clean` capaz de procesar archivos con formato irregular (espacios extra, comillas) y estandarizar los valores numéricos (cambio de comas por puntos) para asegurar una lectura correcta de las estadísticas.

2.  **Escritura (Persistencia y Reportes):**
    El programa implementa dos estrategias de escritura:
    * **Persistencia (Append):** Al registrar un jugador (Opción 6), se utiliza el modo `std::ios::app`. Esto permite agregar datos al final del archivo original de manera eficiente sin reescribir todo el historial.
    * **Exportación (Sobreescritura):** La función `saveAllPlayers` (Opción 8) permite generar **nuevos archivos CSV** con los datos ya ordenados. Recorre la estructura ordenada en memoria y la escribe secuencialmente en disco, permitiendo al usuario guardar sus análisis (ej. "top_anotadores.csv").
