#include <iostream>
#include <climits>

using namespace std;

struct Edge {
    int src, dest, weight;
};

void bellmanFord(int V, int E, Edge* edges, int source) {
    int* distance = new int[V]; // Dynamic allocation for distance array

    for (int i = 0; i < V; i++) {
        distance[i] = INT_MAX;
    }
    distance[source] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;

            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
            }
        }
    }

    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int weight = edges[j].weight;

        if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
            cout << "Graph contains a negative-weight cycle.\n";
            delete[] distance; // Clean up dynamic memory
            return;
        }
    }

    cout << "Vertex\tDistance from Source\n";
    for (int i = 0; i < V; i++) {
        if (distance[i] == INT_MAX)
            cout << i << "\tINF\n"; // Handle infinity distance manually
        else
            cout << i << "\t" << distance[i] << endl;
    }

    delete[] distance; // Clean up dynamic memory
}

int main() {
    int V, E, source;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;

    Edge* edges = new Edge[E]; // Dynamically allocate memory for edges
    cout << "Enter the edges (source, destination, weight):\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    cout << "Enter the source vertex: ";
    cin >> source;

    bellmanFord(V, E, edges, source);

    delete[] edges; // Clean up dynamic memory
    return 0;
}

//tc : o(v) intialization and o(vxe) for relaxation soo exv
// sc: o of v+e
// adv: handle -ve wiehgt edge
// dis: slower to dijkrstra as for no -ve wiehgt

