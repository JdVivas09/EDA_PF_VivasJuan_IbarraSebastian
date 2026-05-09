````markdown
# EDA_PF_VivasJuan_IbarraSebastian

## Práctica Final Integradora - Estructuras de Datos y Algoritmos

Este proyecto corresponde a la práctica final integradora del curso **Estructuras de Datos y Algoritmos**. El objetivo principal es analizar una red de transporte real mediante algoritmos sobre grafos, usando el dataset **roadNet-PA**, perteneciente a la colección SNAP de Stanford.

El grafo representa la red vial de Pennsylvania, Estados Unidos, donde los nodos corresponden a intersecciones o puntos de la red vial, y las aristas representan conexiones entre estos puntos.

El proyecto está implementado en **C++** y se divide en tres módulos principales:

- Módulo A: carga y análisis estructural del grafo.
- Módulo B: comparación entre Dijkstra y BFS para consultas punto a punto.
- Módulo C: análisis de subgrafo inducido, MST y verificación DAG.

---

## Dataset utilizado

El dataset utilizado es:

**roadNet-PA - Pennsylvania Road Network**

Fuente oficial:

- https://snap.stanford.edu/data/roadNet-PA.html
- https://snap.stanford.edu/data/roadNet-PA.txt.gz

Referencia:

Leskovec, J. & Krevl, A. (2014). SNAP Datasets: Stanford Large Network Dataset Collection. http://snap.stanford.edu/data

El archivo utilizado en el proyecto debe estar ubicado en la carpeta:

```txt
data/roadNet-PA.txt
````

El archivo contiene aristas en formato:

```txt
FromNodeId    ToNodeId
```

Las líneas que comienzan con `#` son comentarios y son ignoradas durante la carga.

Aunque el dataset original representa aristas dirigidas, en este proyecto el grafo se trabaja como **no dirigido**, por lo que cada arista se inserta en ambas direcciones.

---

## Estructura del repositorio

```txt
EDA_PF_VivasJuan_IbarraSebastian/
│
├── data/
│   └── roadNet-PA.txt
│
├── results/
│   ├── analisis_estructural.txt
│   ├── consultas_p2p.csv
│   ├── camino_Q01.txt
│   ├── camino_Q06.txt
│   ├── subgrafo_caminos.txt
│   ├── analisis_subgrafo.txt
│   └── tiempos.csv
│
├── src/
│   ├── bfs.cpp
│   ├── dijkstra.cpp
│   ├── graph.cpp
│   ├── graph.hpp
│   ├── loader.cpp
│   ├── main.cpp
│   ├── structural.cpp
│   └── subgraph.cpp
│
├── report/
│   └── Informe.pdf
│
└── README.md
```

---

## Descripción general del proyecto

El proyecto carga un grafo de gran escala y ejecuta algoritmos clásicos de grafos para analizar su estructura y comportamiento.

La representación principal utilizada es una **lista de adyacencia**, debido a que el grafo contiene más de un millón de nodos y más de tres millones de conexiones dirigidas. Una matriz de adyacencia sería inviable en memoria para este tamaño de grafo.

Se trabajan dos tipos de grafos:

```cpp
GrafoNoPonderado
```

Utilizado para BFS, componentes conexas, grado, diámetro aproximado y análisis estructural.

```cpp
GrafoPonderado
```

Utilizado para Dijkstra y MST. Como el dataset no incluye pesos, se asignan pesos aleatorios entre 1 y 10 usando una semilla fija:

```cpp
srand(42);
peso = (rand() % 10) + 1;
```

Esto permite que los resultados sean reproducibles.

---

## Módulo A: Análisis estructural del grafo

El Módulo A se encarga de cargar el grafo y calcular estadísticas estructurales.

### Funcionalidades principales

* Lectura y parseo del archivo `roadNet-PA.txt`.
* Construcción del grafo no ponderado.
* Cálculo del número de nodos.
* Cálculo del número de aristas.
* Cálculo del grado promedio.
* Identificación del nodo de mayor grado.
* Cálculo del número de componentes conexas.
* Identificación del tamaño de la componente conexa principal.
* Estimación del diámetro aproximado usando BFS desde el nodo de mayor grado.

### Archivo generado

```txt
results/analisis_estructural.txt
```

Este archivo contiene las estadísticas calculadas del grafo y sirve para comparar los resultados obtenidos con los valores de referencia publicados por SNAP.

---

## Módulo B: Comparación entre Dijkstra y BFS

El Módulo B realiza consultas de camino mínimo punto a punto sobre el grafo.

Para cada consulta se ejecutan dos algoritmos:

### Dijkstra

Dijkstra trabaja sobre el grafo ponderado. Su objetivo es encontrar el camino de menor costo entre un nodo origen y un nodo destino.

El costo de un camino corresponde a la suma de los pesos de sus aristas.

La implementación usa un heap mínimo mediante:

```cpp
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>
```

### BFS

BFS trabaja sobre el grafo no ponderado. Su objetivo es encontrar el camino con menor número de saltos entre un nodo origen y un nodo destino.

En BFS todas las aristas se consideran con el mismo costo.

### Consultas ejecutadas

El proyecto ejecuta las siguientes 10 consultas fijas:

```txt
Q01: 1 -> 500000
Q02: 100 -> 1000000
Q03: 50000 -> 750000
Q04: 200000 -> 800000
Q05: 300000 -> 100000
Q06: 1 -> 1087562
Q07: 500000 -> 1
Q08: 250000 -> 600000
Q09: 10000 -> 900000
Q10: 400000 -> 150000
```

Para cada consulta se reporta:

* Nombre de la consulta.
* Nodo origen.
* Nodo destino.
* Distancia mínima obtenida con Dijkstra.
* Número de saltos obtenido con BFS.
* Nodos explorados por Dijkstra.
* Nodos explorados por BFS.
* Tiempo de ejecución de Dijkstra en milisegundos.
* Tiempo de ejecución de BFS en milisegundos.

### Archivo generado

```txt
results/consultas_p2p.csv
```

El archivo contiene la siguiente estructura:

```csv
consulta,origen,destino,dist_dijkstra,saltos_bfs,nodos_dijkstra,nodos_bfs,t_dijkstra_ms,t_bfs_ms
```

Además, se reconstruyen y guardan los caminos completos de las consultas Q01 y Q06 usando el arreglo `prev[]`.

Archivos generados:

```txt
results/camino_Q01.txt
results/camino_Q06.txt
```

Estos caminos son usados posteriormente en el Módulo C.

---

## Módulo C: Subgrafo inducido, MST y DAG

El Módulo C utiliza los caminos reconstruidos de las consultas Q01 y Q06 para construir un subgrafo inducido.

### Funcionalidades principales

* Construcción del subgrafo inducido por la unión de los caminos Q01 y Q06.
* Exportación del subgrafo como lista de nodos y aristas.
* Cálculo del MST usando Kruskal.
* Verificación de si el subgrafo es DAG mediante DFS.

### Subgrafo inducido

El subgrafo inducido se construye tomando todos los nodos que aparecen en los caminos reconstruidos de Q01 y Q06.

Luego, se agregan las aristas del grafo original que conectan nodos pertenecientes a ese conjunto.

### MST

Para calcular el árbol de expansión mínima se utiliza el algoritmo de Kruskal. Este algoritmo ordena las aristas por peso y selecciona aquellas que no forman ciclos, hasta conectar todos los nodos posibles del subgrafo.

### DAG

Se verifica si el subgrafo es un DAG, es decir, un grafo dirigido acíclico. Para esto se utiliza una búsqueda DFS con control de nodos visitados y nodos en la pila de recursión.

### Archivos generados

```txt
results/subgrafo_caminos.txt
results/analisis_subgrafo.txt
```

El archivo `subgrafo_caminos.txt` contiene la lista de nodos y aristas del subgrafo inducido.

El archivo `analisis_subgrafo.txt` contiene:

```txt
Numero de nodos del subgrafo
Numero de aristas del subgrafo
Peso total del MST
Resultado de la verificacion DAG
```

---

## Compilación

El proyecto fue desarrollado en C++ y puede compilarse usando `cl` en Windows con Visual Studio Build Tools.

Desde la carpeta raíz del proyecto, ejecutar:

```bat
cl /EHsc /std:c++17 /O2 /Fe:eda_pf.exe src\main.cpp src\loader.cpp src\structural.cpp src\dijkstra.cpp src\bfs.cpp src\graph.cpp src\subgraph.cpp
```

También puede compilarse con `g++` si el entorno lo tiene instalado:

```bash
g++ -std=c++17 -O2 -o eda_pf src/main.cpp src/loader.cpp src/structural.cpp src/dijkstra.cpp src/bfs.cpp src/graph.cpp src/subgraph.cpp
```

---

## Ejecución

El programa recibe como argumento el módulo que se desea ejecutar.

### Ejecutar Módulo A

```bat
eda_pf.exe A
```

Este comando ejecuta el análisis estructural del grafo y genera:

```txt
results/analisis_estructural.txt
```

### Ejecutar Módulo B

```bat
eda_pf.exe B
```

Este comando ejecuta las consultas punto a punto con Dijkstra y BFS, generando:

```txt
results/consultas_p2p.csv
results/camino_Q01.txt
results/camino_Q06.txt
```

### Ejecutar Módulo C

```bat
eda_pf.exe C
```

Este comando ejecuta el análisis del subgrafo inducido, MST y DAG, generando:

```txt
results/subgrafo_caminos.txt
results/analisis_subgrafo.txt
```

---

## Complejidad de los algoritmos

### BFS

BFS tiene complejidad:

```txt
O(V + E)
```

donde:

* `V` es el número de nodos.
* `E` es el número de aristas.

BFS recorre cada nodo y cada arista como máximo una vez.

### Dijkstra con heap mínimo

Dijkstra con heap mínimo tiene complejidad aproximada:

```txt
O((V + E) log V)
```

Esto se debe al uso de una cola de prioridad para seleccionar el nodo con menor distancia acumulada.

### Kruskal

Kruskal tiene complejidad:

```txt
O(E log E)
```

debido al ordenamiento de las aristas por peso.

---

## Decisiones de implementación

### Lista de adyacencia

Se utiliza lista de adyacencia porque el grafo es disperso y tiene una gran cantidad de nodos. Usar una matriz de adyacencia requeriría una cantidad de memoria demasiado alta.

### Grafo no ponderado

Se utiliza para:

* BFS.
* Componentes conexas.
* Diámetro aproximado.
* Grado de nodos.
* Análisis estructural.

### Grafo ponderado

Se utiliza para:

* Dijkstra.
* MST.
* Análisis de caminos con pesos.

### Pesos aleatorios reproducibles

Como el dataset original no incluye pesos, se asignan pesos enteros aleatorios entre 1 y 10.

Para garantizar reproducibilidad, se usa:

```cpp
srand(42);
```

De esta forma, los pesos generados son los mismos en cada ejecución.

---

## Manejo de casos especiales

El programa valida que los nodos de origen y destino existan dentro del grafo antes de ejecutar BFS o Dijkstra.

Si un nodo no existe o no hay camino entre origen y destino, se reporta el resultado como:

```txt
INF
```

o como:

```txt
no hay camino
```

según el archivo generado.

---

## Resultados esperados

Al ejecutar correctamente los tres módulos, la carpeta `results/` debe contener al menos los siguientes archivos:

```txt
analisis_estructural.txt
consultas_p2p.csv
camino_Q01.txt
camino_Q06.txt
subgrafo_caminos.txt
analisis_subgrafo.txt
```

Estos archivos permiten verificar los resultados del análisis estructural, la comparación de algoritmos y el análisis del subgrafo inducido.

---

## Herramientas utilizadas

Durante el desarrollo se utilizaron las siguientes herramientas:

* Visual Studio Code.
* Visual Studio Build Tools.
* Git y GitHub.
* C++17.
* ChatGPT como apoyo para explicación conceptual, revisión de estructura del proyecto, depuración de errores y redacción del README.

El código fue revisado, adaptado y comprendido por los integrantes del equipo antes de su entrega.

---

## Autores

**Juan Daniel Vivas Granada**

**Sebastian Andres Ibarra Prada**

```
```
