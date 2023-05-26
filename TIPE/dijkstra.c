#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 4

int minDistance(int dist[], int visited[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (visited[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

void printPath(int parent[], int j) {
    if (parent[j] == -1) {
        printf("%d ", j);
        return;
    }

    printPath(parent, parent[j]);
    printf("%d ", j);
}

void dijkstra(int graph[V][V], int src) {
    int dist[V], visited[V], parent[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printf("Chemin le plus court de la source Ã  tous les nÅuds:\n");
    for (int i = 0; i < V; i++) {
        printf("NÅuds %d, distance = %d, Chemin = ", i, dist[i]);
        printPath(parent, i);
        printf("\n");
    }
}

int main() {
    int graph[V][V] = {
        {0, 0, 4, 7},
        {2, 0, 9, 7},
        {5, 0, 0, 0},
        {0, 2, 3, 0},
    };

    dijkstra(graph, 0);

    return 0;
}
