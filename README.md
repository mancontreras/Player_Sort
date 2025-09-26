# Player_Sort
Visor de estadísticas de jugadores de básquet con QuickSort
Este proyecto carga un archivo tipo tabla (CSV) con nombres de jugadores y sus estadísticas (PTS, REB, AST, STL, BLK). El programa permite elegir una estadística y mostrar a todos los jugadores ordenados de manera ascendente o descendente según ese valor.

Ejemplo:
Archivo CSV: `sample_players_basket.csv`

## Funcionamiento:

## Paso 1: 
El programa lee automáticamente el archivo CSV.

## Paso 2: 
El usuario selecciona el tipo de estadística que quiere ordenar.
   - [0] PTS (puntos)
   - [1] REB (rebotes)
   - [2] AST (asistencias)
   - [3] STL (robos)
   - [4] BLK (bloqueos)
   - 
## Paso 3:
El usuario elige el orden:
   - [1] Ascendente
   - [2] Descendente
   - 
## Paso 4:
El programa imprime la tabla con `Nombre | Estadística` ya ordenada.

---

### SICT0302B: Toma decisiones
**Selecciona y usa un algoritmo de ordenamiento adecuado al problema**  
Para este proyecto uso **QuickSort con partición de Lomuto**, porque es un algoritmo clásico, relativamente sencillo de implementar y en promedio trabaja en O(n log n), lo que es eficiente para ordenar listas de jugadores.  
Las funciones donde se ve esto son `partition_lomuto` y `quickSort` que están en el archivo `quicksort.hpp`.

- Complejidad QuickSort:
  - Promedio: O(n log n)
  - Peor caso: O(n²) (cuando el arreglo ya está ordenado y siempre se elige un pivote malo)
  - Memoria: O(log n) por las llamadas recursivas

---

### SICT0301B: Evalúa los componentes
**Hace un análisis de complejidad correcto y completo para el programa**

- **Lectura del CSV (`loadPlayers`)**:  
  Lee n filas y convierte los valores → O(n).
- **Construcción del vector auxiliar para la métrica**:  
  Se recorre la lista de jugadores una vez → O(n).
- **Ordenamiento con QuickSort**:  
  - Promedio O(n log n)  
  - Peor O(n²)  
  - Memoria O(log n)
- **Impresión de la tabla (`printTable`)**:  
  Recorre el vector para mostrarlo → O(n).

En conjunto, el costo total del programa está dominado por el ordenamiento: **O(n log n) en promedio**.


