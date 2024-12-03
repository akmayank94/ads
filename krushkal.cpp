#include <iostream>
#include <algorithm>

using namespace std;

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    Edge* edges;
};

Graph* createGraph(int V, int E) {
    Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edges = new Edge[E];
    return graph;
}

int find(int parent[], int i) {
    if (parent[i] != i) {
        parent[i] = find(parent, parent[i]);
    }
    return parent[i];
}

void unionSets(int parent[], int rank[], int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);

    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

void kruskalMST(Graph* graph) {
    int V = graph->V;
    Edge result[V - 1];
    int e = 0;

    sort(graph->edges, graph->edges + graph->E, compareEdges);

    int parent[V], rank[V];
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int i = 0; e < V - 1 && i < graph->E; i++) {
        Edge nextEdge = graph->edges[i];
        int x = find(parent, nextEdge.src);
        int y = find(parent, nextEdge.dest);

        if (x != y) {
            result[e++] = nextEdge;
            unionSets(parent, rank, x, y);
        }
    }

    cout << "Edges in the Minimum Spanning Tree:\n";
    int totalWeight = 0;
    for (int i = 0; i < e; i++) {
        cout << result[i].src << " -- " << result[i].dest << " == " << result[i].weight << endl;
        totalWeight += result[i].weight;
    }
    cout << "Total weight of the Minimum Spanning Tree: " << totalWeight << endl;
}

int main() {
    int V, E;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;

    Graph* graph = createGraph(V, E);

    cout << "Enter the edges (source, destination, weight):\n";
    for (int i = 0; i < E; i++) {
        cin >> graph->edges[i].src >> graph->edges[i].dest >> graph->edges[i].weight;
    }

    kruskalMST(graph);

    delete[] graph->edges;
    delete graph;

    return 0;
}

// TC: O(ElogE + E. alpha(V))
// for sparse graph E = V : O(ElogE)
// SC: O(E+V)

// advantage : simple+ efficiend for edge list representation + works well for sparse E<= V^2
// disadv: costly for dense graph + for adj matrix , prims algo is faster

