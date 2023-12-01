// Actividad Integradora 2 - Estructuras de datos y Algoritmos Avanzados

// Integrantes:
// Mauricio
// Oswaldo
// Santiago

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <climits>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

struct Edge {
    int sourceNode; // nodo origen
    int destinationNode; // Nodo al que se conecta esta arista
    int weight; // Peso de la arista

    // Constructor
    Edge(int _sourceNode, int _destinationNode, int _weight) {
        sourceNode = _sourceNode;
        destinationNode = _destinationNode;
        weight = _weight;
    }

    // Función para comparar objetos Edge en base al peso
    bool operator>(const Edge other) const {
        return weight > other.weight;
    }
};

// Algoritmo de Prim
vector<Edge>prim(vector<vector<int>> adjMatrix, int N) {
    vector<Edge> mst;

    // Minheap para determinar la arista con el menor peso
    priority_queue<Edge, vector<Edge>, greater<Edge>> minHeap;

    // map para registrar los nodos ya vistados
    map<int, bool> visited;

    // Definimos la Arista inicial
    Edge source = Edge(0, 0, 0);

    // Añadimos la arista al minheap
    minHeap.push(source);

    while (!minHeap.empty()) {
         // Obtenemos la arista con menor peso del minheap
        Edge current = minHeap.top();

        // Checar si el nodo actual no ha sido visitado
        if (visited.find(current.destinationNode) == visited.end()) {

            // Marcamos el nodo como visitado
            visited[current.destinationNode] = true;

            // añadimos la arista al vector resultado de aristas que conforman el arbol de expansión minima
            mst.push_back(current);

            for (int i = 0; i < N; i++) {
                
                    // creamos y añadimos la arista a la cola con prioridad
                    Edge edge = Edge(current.destinationNode, i, adjMatrix[current.destinationNode][i]); // creamos la arista a añadir
                    minHeap.push(edge);
            }
        }

        // borramos del minheap la arista actual
        minHeap.pop();
    }

    return mst; // regresamos el vector de aristas resultado
}

// Función para calcular la distancia entre dos puntos del plano
int calculateDistance(pair<int, int> p1, pair<int, int> p2) {
    return round(sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2)));
}

// Agente viajero
// Función que resuelve el Problema del Viajero (TSP)
// La función toma las coordenadas de los puntos y una ruta inicial, y devuelve la mejor ruta encontrada.
vector<int> travelingSalesman(vector<pair<int, int>> &coordinates, vector<pair<int, int>> &route) {
    // Número de puntos (ciudades) en el problema
    int N = coordinates.size();

    // Inicialización de la mejor ruta con una permutación inicial
    vector<int> bestRoute(N);
    for (int i = 0; i < N; ++i) bestRoute[i] = i;

    // Inicialización de la mejor distancia con un valor infinito
    int bestDistance = INT_MAX;

    // Bucle que genera todas las permutaciones posibles de la ruta
    do {
        // Calcula la distancia total de la ruta actual
        int totalDistance = 0;
        for (int i = 0; i < N - 1; ++i) {
            totalDistance += calculateDistance(coordinates[bestRoute[i]], coordinates[bestRoute[i + 1]]);
        }
        totalDistance += calculateDistance(coordinates[bestRoute[N - 1]], coordinates[bestRoute[0]]);

        // Compara la distancia actual con la mejor distancia encontrada hasta ahora
        if (totalDistance < bestDistance) {
            // Si la distancia actual es mejor, actualiza la mejor distancia y la mejor ruta
            bestDistance = totalDistance;
            route.clear();
            for (int i = 0; i < N; ++i) route.push_back({bestRoute[i], bestRoute[(i + 1) % N]});
        }
    } while (next_permutation(bestRoute.begin() + 1, bestRoute.end())); // Genera la siguiente permutación

    // Devuelve la mejor ruta encontrada
    return bestRoute;
}


// Función para encontrar la central más cercana
int closestCentral(vector<pair<int, int>> &centrals, pair<int, int> &newHiringLocation) {
    // Inicialización del índice de la central más cercana y la distancia mínima
    int closestIndex = 0;
    int minDistance = calculateDistance(centrals[0], newHiringLocation);

    // Bucle que recorre las centrales para encontrar la más cercana
    for (int i = 1; i < centrals.size(); ++i) {
        // Calcula la distancia entre la central actual y la nueva ubicación
        int d = calculateDistance(centrals[i], newHiringLocation);

        // Compara la distancia actual con la distancia mínima encontrada hasta ahora
        if (d < minDistance) {
            // Si la distancia actual es menor, actualiza la distancia mínima y el índice de la central más cercana
            minDistance = d;
            closestIndex = i;
        }
    }

    // Devuelve el índice de la central más cercana
    return closestIndex;
}



int main() {
    ifstream file("input.txt"); // archivo
    // ifstream file("input2.txt"); // archivo

    if (!file.is_open()) {
        cerr << "Error al abrir el archivo" << endl;
        return 1;
    }

    int N; // Número de nodos
    file >> N;

    vector<vector<int>> m(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            file >> m[i][j];
            if(i != j && m[i][j] == 0) {
                m[i][j] = INT_MAX;
            }
        }
    }

    vector<pair<int, int>> centralCoordinates;
    for (int i = 0; i < N; ++i) {
        int x, y;
        char ch; // para no considerar comas y paréntesis
        file >> ch >> x >> ch >> y >> ch;
        centralCoordinates.push_back(make_pair(x, y));
    }

    file.close();

    // Parte 1: Prim's Algorithm
    vector<Edge>mst = prim(m, N);
    cout << "Forma de cablear las colonias\n";
    for (int i = 1; i < mst.size(); i++)
    {
        cout << "(" << mst[i].sourceNode << "," << mst[i].destinationNode << ")" << " ";
    }
    cout <<endl;

    // Parte 2: TSP
    vector<pair<int, int>> salesmanRoute;
    vector<int> visitOrder = travelingSalesman(centralCoordinates, salesmanRoute);
    cout << "\nTraveling Salesman Route:\n";
    for (const auto &city : visitOrder) {
        cout << char('A' + city) << " ";
    }
    cout << endl;

    // Parte 3: Central cercana
    pair<int, int> newHiringLocation;
    cout << "\nIngresa las coordenadas x,y: ";
    cin >> newHiringLocation.first >> newHiringLocation.second;

    int closestCentralIndex = closestCentral(centralCoordinates, newHiringLocation);
    cout << "La central mas cercana es: " << char('A' + closestCentralIndex) << endl;

    return 0;
}