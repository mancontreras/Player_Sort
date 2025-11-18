# Proyecto Player_Sort - Avance 3 
**Autor:** Manuel Eduardo Contreras Flores (A01707142)

## Descripción
Este proyecto carga un archivo tipo tabla (CSV) con nombres de jugadores y sus estadísticas (PTS, REB, AST, STL, BLK). El programa permite elegir una estadística y mostrar a todos los jugadores ordenados de manera ascendente o descendente según ese valor.

Ejemplo:  
Archivo CSV: `sample_players_basket.csv`

## Funcionamiento actualizado:

### Paso 1: 
El programa lee automáticamente el archivo CSV y carga los jugadores en memoria.

### Paso 2: 
El usuario selecciona la opción del menú:
   - [1-5] Ordenar por PTS, REB, AST, STL, BLK.
   - [6] Registrar un nuevo jugador.
   - [7] **Buscar un jugador** (Nueva función).
   - [8] **Exportar lista actual a CSV** (Nueva función).
   - [0] Salir del programa.

### Paso 3 (Ordenamiento):
El programa ordena los jugadores usando **QuickSort sobre una lista doblemente ligada** y luego imprime la tabla ordenada.

---

### SICT0302B: Toma decisiones
**Selecciona y usa una estructura de datos adecuada al problema**
En este avance se optó por una **lista doblemente ligada (DLL)** para el proceso de ordenamiento porque:
- Permite recorrer los elementos en ambas direcciones (`prev` y `next`), lo cual facilita la lógica de partición en QuickSort sin necesidad de índices numéricos.
- **Eficiencia en memoria:** Al ordenar, el intercambio de nodos se logra ajustando punteros. Esto evita el movimiento masivo de datos que ocurriría en un vector al insertar o mover elementos en posiciones intermedias.

**Comparación de complejidad (Algoritmos y Estructuras):**
- **Vectores + QuickSort:** O(n log n) promedio. Sin embargo, si se requiriera insertar en medio, sería costoso O(n).
- **Lista doblemente ligada + QuickSort:** O(n log n) promedio. La inserción y borrado es O(1) si se tiene la referencia al nodo, o O(n) si se busca, pero nunca cuadrática.
- **Selection/Insertion sort:** O(n²), se descartaron por ser ineficientes para listas que pueden crecer.
- **Merge Sort:** O(n log n) estable, pero requiere memoria auxiliar O(n). QuickSort se realiza *in-place* sobre la lista.

---

### SICT0301B: Evalúa los componentes
**Hace un análisis de complejidad correcto y completo del programa:**

A continuación se desglosa la complejidad temporal (Big O) para cada funcionalidad, detallando explícitamente los tres escenarios:

**1. Carga y Construcción (`loadPlayers` + `buildDLL`):**
Se leen $n$ registros y se agregan a la lista usando un puntero `tail`.
- **Mejor caso:** O(n)
- **Caso promedio:** O(n)
- **Peor caso:** O(n)
- *Análisis:* La lectura es lineal y la inserción al final con `tail` es O(1) por elemento, resultando en O(n) total.

**2. Ordenamiento (QuickSort sobre DLL):**
Depende del pivote y el orden inicial de los datos.
- **Mejor caso:** O(n log n) (Particiones balanceadas).
- **Caso promedio:** O(n log n) (Datos aleatorios).
- **Peor caso:** O(n²) (Lista ya ordenada o inversamente ordenada).
- **Memoria:** O(log n) por la pila de recursión.

**3. Registro de nuevo jugador (`registrarJugador`):**
Implica buscar si el nombre existe (recorrido lineal) y luego insertar.
- **Mejor caso:** O(1) (El duplicado se detecta en el primer nodo).
- **Caso promedio:** O(n) (Se recorre la mitad de la lista).
- **Peor caso:** O(n) (No hay duplicados; se recorre toda la lista y se inserta al final).

**4. Búsqueda de jugador (`buscarJugador`) [NUEVO]:**
Búsqueda lineal por coincidencia de texto en el vector.
- **Mejor caso:** O(1) (Encontrado al inicio).
- **Caso promedio:** O(n) (Encontrado a la mitad o no existe).
- **Peor caso:** O(n) (No encontrado o está al final).

**5. Exportación de archivo (`saveAllPlayers`) [NUEVO]:**
Recorre la estructura completa para escribirla en un nuevo CSV.
- **Mejor caso:** O(n)
- **Caso promedio:** O(n)
- **Peor caso:** O(n)

**6. Visualización (`printTable`):**
Recorrido lineal para imprimir en consola.
- **Mejor caso:** O(n)
- **Caso promedio:** O(n)
- **Peor caso:** O(n)

**Conclusión:**
El costo total del programa está dominado por el ordenamiento: **O(n log n) en promedio**.

---

### SICT0303B: Implementa acciones científicas
**Implementa mecanismos de lectura y escritura de archivos para guardar los datos de manera correcta:**

1.  **Lectura Robusta:**
    Se implementó un mecanismo de limpieza (`clean` y `splitCSV`) que elimina caracteres basura y espacios invisibles del CSV, y estandariza los valores numéricos (reemplazando comas por puntos) para asegurar una lectura correcta de las estadísticas.

2.  **Escritura (Persistencia y Reportes):**
    - **Modo Append:** Para el registro (Opción 6), se usa `std::ios::app` para añadir datos al final del archivo original de manera eficiente sin borrar el historial.
    - **Modo Write (Exportación):** Para la opción 8, se usa `std::ofstream` para crear un archivo nuevo (ej. `reporte.csv`) con los datos ya ordenados y limpios, permitiendo extraer la información procesada correctamente.
