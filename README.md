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
**Selecciona y usa una estructura de datos adecuada al problema** En este avance se optó por una **lista doblemente ligada (DLL)** para el proceso de ordenamiento porque:
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

A continuación se desglosa la complejidad temporal (Big O) para cada funcionalidad, cubriendo los tres escenarios posibles (Mejor, Promedio y Peor caso):

**1. Carga y Construcción (`loadPlayers` + `buildDLL`):**
Se leen $n$ registros y se agregan a la lista.
- **Mejor, Promedio y Peor caso:** O(n).
- *Análisis:* Aunque insertar al final de una lista recorriéndola sería O(n²), en esta implementación se utiliza un puntero `tail`. Esto permite insertar cada nodo al final en O(1), resultando en una complejidad total lineal O(n) para la construcción.

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

**4. Visualización (`printTable`):**
Recorrido lineal para imprimir.
- **Complejidad (Todos los casos):** O(n).

**Conclusión:**
El costo total del programa está dominado por el ordenamiento: **O(n log n) en promedio**.

---

### SICT0303B: Implementa acciones científicas
- Se implementaron mecanismos para **consultar información de la lista doblemente ligada**: recorrer la lista y acceder a nodos según la métrica seleccionada.
- Se implementó correctamente la **lectura de archivos CSV** para cargar los datos en la lista.

---

### Nota:
Este avance introduce el uso de **listas doblemente ligadas**, manteniendo QuickSort como método de ordenamiento, lo que permite manejar datos de manera más flexible y eficiente en operaciones de inserción y recorridos bidireccionales.

