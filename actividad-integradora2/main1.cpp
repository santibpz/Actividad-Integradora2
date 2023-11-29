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

using namespace std;

struct Edge {
    int destinationNode; // Nodo al que se conecta esta arista
    int weight; // Peso de la arista

    // Constructor
    Edge(int _destinationNode, int _weight) {
        destinationNode = _destinationNode;
        weight = _weight;
    }

    // Función para comparar objetos Edge en base al peso
    bool operator>(const Edge other) const {
        return weight > other.weight;
    }
};

// Algoritmo de Prim
void prim(vector<vector<int>> adjMatrix, int N) {
    vector<Edge> mst;

    // Minheap para determinar la arista con el menor peso
    priority_queue<Edge, vector<Edge>, greater<Edge>> minHeap;

    // map para registrar los nodos ya vistados
    map<int, bool> visited;

    // Definimos la Arista inicial
    Edge source = Edge(0, 0);

    // Añadimos la arista al minheap
    minHeap.push(source);

    while (!minHeap.empty()) {
         // Obtenemos la arista con menor peso del minheap
        Edge current = minHeap.top();

        std::cout << "curr edge OUTSIDE: (" << current.destinationNode << ", " << current.weight << ")\n";

        // Checar si el nodo actual no ha sido visitado
        if (visited.find(current.destinationNode) == visited.end()) {
            // Marcamos el nodo como visitado para evitar ciclos
            visited[current.destinationNode] = true;

            std::cout << "curr: (" << current.destinationNode << ", " << current.weight << ")\n";

            // Guardamos la arista
            mst.push_back(current);

            for (int i = 0; i < N; i++) {
                // verificamos que de las aristas que vamos a agregar al minheap ninguna conecte con un nodo ya visitado
                // if(visited.find(i) == visited.end()) {
                    Edge edge = Edge(i, adjMatrix[current.destinationNode][i]); // creamos la arista a añadir
                    std::cout << "edge to add: (" << edge.destinationNode << ", " << edge.weight << ")\n";
                    minHeap.push(edge);
            }
        }

        // borramos del minheap la arista actual
        minHeap.pop();
    }

    for (const auto &edge : mst) {
        cout << "(" << edge.destinationNode << "," << edge.weight << ") ";
    }
    cout << endl;
}

// Función para calcular la distancia entre dos puntos del plano
int calculateDistance(pair<int, int> p1, pair<int, int> p2) {
    return round(sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2)));
}

// Agente viajero
vector<int> travelingSalesman(vector<pair<int, int>> &coordinates, vector<pair<int, int>> &route) {
    int N = coordinates.size();
    vector<int> bestRoute(N);
    for (int i = 0; i < N; ++i) bestRoute[i] = i;

    int bestDistance = INT_MAX;

    do {
        int totalDistance = 0;
        for (int i = 0; i < N - 1; ++i) {
            totalDistance += calculateDistance(coordinates[bestRoute[i]], coordinates[bestRoute[i + 1]]);
        }
        totalDistance += calculateDistance(coordinates[bestRoute[N - 1]], coordinates[bestRoute[0]]);

        if (totalDistance < bestDistance) {
            bestDistance = totalDistance;
            route.clear();
            for (int i = 0; i < N; ++i) route.push_back({bestRoute[i], bestRoute[(i + 1) % N]});
        }
    } while (next_permutation(bestRoute.begin() + 1, bestRoute.end()));

    return bestRoute;
}

// Función para encontrar la central más cercana
int closestCentral(vector<pair<int, int>> &centrals, pair<int, int> &newHiringLocation) {
    int closestIndex = 0;
    int minDistance = calculateDistance(centrals[0], newHiringLocation);

    for (int i = 1; i < centrals.size(); ++i) {
        int d = calculateDistance(centrals[i], newHiringLocation);
        if (d < minDistance) {
            minDistance = d;
            closestIndex = i;
        }
    }

    return closestIndex;
}

int main() {
    vector<vector<int>> m = {
        {0, 1, 3, 6, INT_MAX, INT_MAX},
        {1, 0, 4, INT_MAX, 10, 8},
        {3, 4, 0, 2, 9, 7},
        {6, INT_MAX, 2, 0, INT_MAX, 5},
        {INT_MAX, 10, 9, INT_MAX, 0, 2},
        {INT_MAX, 8, 7, 5, 2, 0}
    };

    int N = m.size();

    // Parte 1
    prim(m, N);

    // Parte 2
    vector<pair<int, int>> centralCoordinates = {{200, 500}, {300, 100}, {450, 150}, {520, 480}};
    vector<pair<int, int>> salesmanRoute;
    vector<int> visitOrder = travelingSalesman(centralCoordinates, salesmanRoute);
    cout << "\nTraveling Salesman Route:\n";
    for (const auto &city : visitOrder) {
        cout << char('A' + city) << " ";
    }
    cout << endl;

    // Parte 3
    pair<int, int> newHiringLocation;
    cout << "\nEnter the location of the new hiring (as a pair of coordinates x y): ";
    cin >> newHiringLocation.first >> newHiringLocation.second;

    int closestCentralIndex = closestCentral(centralCoordinates, newHiringLocation);
    cout << "The closest central to the new hiring location is in colony: " << char('A' + closestCentralIndex) << endl;

    return 0;
}
