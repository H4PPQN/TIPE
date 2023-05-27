#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include "functions.h"


// Function to find the vertex with the minimum distance value
int minDistance(int dist[], bool visited[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < SIZE; v++)
    {
        if (visited[v] == false && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// Function to print the shortest path from source to destination
int* getPath(int parent[], int dest, int* pathLength)
{
    int* path = NULL;
    int count = 0;
    int current = dest;

    while (current != -1)
    {
        path = (int*)realloc(path, (count + 1) * sizeof(int));
        path[count++] = current;
        current = parent[current];
    }

    *pathLength = count;

    // Reverse the path
    int i, j;
    for (i = 0, j = count - 1; i < j; i++, j--)
    {
        int temp = path[i];
        path[i] = path[j];
        path[j] = temp;
    }

    return path;
}

// Function to implement Dijkstra's algorithm and return the shortest path
int* dijkstra(int graph[SIZE][SIZE], int src, int dest, int* pathLength)
{
    int dist[SIZE];
    bool visited[SIZE];
    int parent[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        dist[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < SIZE - 1; count++)
    {
        int u = minDistance(dist, visited);
        visited[u] = true;

        for (int v = 0; v < SIZE; v++)
        {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    int* path = getPath(parent, dest, pathLength);
    return path;
}


