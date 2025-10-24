# Player_Sort
Visor de estadísticas de jugadores de básquet con QuickSort y listas doblemente ligadas  
Este proyecto carga un archivo tipo tabla (CSV) con nombres de jugadores y sus estadísticas (PTS, REB, AST, STL, BLK). El programa permite elegir una estadística y mostrar a todos los jugadores ordenados de manera ascendente o descendente según ese valor.

Ejemplo:  
Archivo CSV: `sample_players_basket.csv`

## Funcionamiento actualizado:

### Paso 1: 
El programa lee automáticamente el archivo CSV y carga los jugadores en una **lista doblemente ligada** (`DoublyLinkedList`), lo que permite recorrer los datos en ambas direcciones y facilita la implementación de algoritmos de ordenamiento sobre nodos.

### Paso 2: 
El usuario selecciona la opción del menú:
   - [1] Ordenar por PTS (puntos)
   - [2] Ordenar por REB (rebotes)
   - [3] Ordenar por AST (asistencias)
   - [4] Ordenar por STL (robos)
   - [5] Ordenar por BLK (bloqueos)
   - [6] Registrar un nuevo jugador
   - [0] Salir del programa

### Paso 3 (solo para opciones 1-5):
El usuario elige el orden del listado:
   - [1] Ascendente
   - [2] Descendente

### Paso 4 (solo para opciones 1-5):
El programa ordena los jugadores usando **QuickSort sobre la lista doblemente ligada** y luego imprime la tabla con `Nombre | Estadística` ya ordenada.

### Paso 5 (opción 6):
El usuario puede **registrar un nuevo jugador** desde la consola, que se agrega tanto a la lista como al CSV. Si el nombre ya existe, se cancela el registro para evitar duplicados.

### Paso 6:
El usuario puede repetir las operaciones anteriores hasta elegir **Salir**.

---

### SICT0302B: Toma decisiones
**Selecciona y usa una estructura de datos adecuada al problema**  
En este avance se optó por una **lista doblemente ligada** porque:
- Permite recorrer los elementos hacia adelante y hacia atrás, útil para QuickSort adaptado a nodos.
- Facilita la inserción y eliminación de jugadores sin reacomodar todo el contenedor.
- Se mantiene QuickSort como algoritmo de ordenamiento por ser eficiente para listas de tamaño moderado y sencillo de implementar sobre nodos.

**Comparación con otros algoritmos y estructuras:**
- **Vectores + QuickSort:** O(n log n) promedio, pero inserciones requieren mover elementos → O(n)
- **Lista doblemente ligada + QuickSort:** O(n log n) promedio, inserciones y borrado O(1) si ya tienes el nodo.
- **Selection/Insertion sort sobre listas:** O(n²), menos eficiente para listas medianas/grandes.
- **Merge Sort:** O(n log n) promedio y peor caso, pero requiere memoria extra → O(n).

**Complejidad de QuickSort (Lomuto) sobre DLL:**
- Mejor caso: O(n log n)
- Promedio: O(n log n)
- Peor caso: O(n²) (cuando la lista ya está ordenada y siempre se elige un pivote desfavorable)
- Memoria: O(log n) por la pila de llamadas recursivas

---

### SICT0301B: Evalúa los componentes
**Hace un análisis de complejidad correcto y completo del programa:**

Lectura del CSV (`loadPlayers`):
- Lee n filas y convierte los valores → O(n)

Construcción de la lista doblemente ligada:
- Inserción de n jugadores al final → O(n)

Ordenamiento con QuickSort sobre la lista:
- Mejor caso: O(n log n)
- Promedio: O(n log n)
- Peor caso: O(n²)
- Memoria: O(log n) por recursión

Impresión de la tabla (`printTable`):
- Recorre la lista → O(n)

Registro de un nuevo jugador:
- Inserción al final de la lista → O(1)
- Guardado en CSV → O(1)

En conjunto, el costo total está dominado por el ordenamiento: **O(n log n) en promedio**.

---

### SICT0303B: Implementa acciones científicas
- Se implementaron mecanismos para **consultar información de la lista doblemente ligada**: recorrer la lista y acceder a nodos según la métrica seleccionada.
- Se implementó correctamente la **lectura de archivos CSV** para cargar los datos en la lista.

---

### Nota:
Este avance introduce el uso de **listas doblemente ligadas**, manteniendo QuickSort como método de ordenamiento, lo que permite manejar datos de manera más flexible y eficiente en operaciones de inserción y recorridos bidireccionales.

