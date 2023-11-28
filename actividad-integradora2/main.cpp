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
void Prim(vector<vector<int>>adjMatrix, int N) {
    vector<Edge>mst;

    // Minheap para determinar la arista con el menor peso
    priority_queue<Edge, vector<Edge>, greater<Edge>> minHeap;

    // map para registrar los nodos ya vistados
    map<int,bool>visited;

    // Definimos la Arista inicial
    Edge source = Edge(0,0);

    // // Añadimos la arista al minheap
    minHeap.push(source);

    // mst.push_back(source);

    while(!minHeap.empty()) {
        // Obtenemos la arista con menor peso del minheap
        Edge current = minHeap.top();

        std::cout << "curr edge OUTSIDE: (" << current.destinationNode << ", " << current.weight << ")\n";

        // Checar si el nodo actual no ha sido visitado
        if(visited.find(current.destinationNode) == visited.end()) {
            // Marcamos el nodo como visitado para evitar ciclos
            visited[current.destinationNode] = true;

             std::cout << "curr: (" << current.destinationNode << ", " << current.weight << ")\n";
             // Guardamos la arista
            mst.push_back(current);

            for(int i = 0; i < N; i++) {
                // verificamos que de las aristas que vamos a agregar al minheap ninguna conecte con un nodo ya visitado
                // if(visited.find(i) == visited.end()) {
                    Edge edge = Edge(i, adjMatrix[current.destinationNode][i]); // creamos la arista a añadir
                    std::cout << "edge to add: (" << edge.destinationNode << ", " << edge.weight << ")\n";
                    minHeap.push(edge); 
                
            // }
          }
        }

        // borramos del minheap la arista actual
        minHeap.pop();
    }


    // cout << "Edges of the Minimum Spanning Tree:\n";
    for (int i = 0; i < mst.size(); i++) {
        std::cout << "Edge: (" << mst[i].destinationNode << ", " << mst[i].weight << ")\n";
    }
}


int main() {
    // vector<vector<int>>m = {
    //     {0,16,45,32},
    //     {16,0,18,21},
    //     {45,18,0,7},
    //     {32,21,7,0}
    // };

     vector<vector<int>>m = {
        {0, 1, 3, 6, INT_MAX, INT_MAX},
        {1, 0, 4, INT_MAX, 10, 8},
        {3, 4, 0, 2, 9, 7},
        {6, INT_MAX, 2, 0, INT_MAX, 5},
        {INT_MAX, 10, 9, INT_MAX, 0, 2},
        {INT_MAX, 8, 7, 5, 2, 0}
    };



    int n = m.size();
    Prim(m,n);
    return 0;
}