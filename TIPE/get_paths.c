#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "functions.h"



// Function to perform a modified depth-first search (DFS) to find all paths
void findAllPaths(int graph[SIZE][SIZE], int src, int dest, bool visited[], int path[], int pathIndex, Path* allPaths, int* pathCount)
{
    visited[src] = true;
    path[pathIndex] = src;
    pathIndex++;

    if (src == dest)
    {
        // Store the current path
        allPaths[*pathCount].length = pathIndex;
        allPaths[*pathCount].nodes = malloc(pathIndex * sizeof(int));
        for (int i = 0; i < pathIndex; i++)
        {
            allPaths[*pathCount].nodes[i] = path[i];
        }
        (*pathCount)++;
    }
    else
    {
        for (int i = 0; i < SIZE; i++)
        {
            if (graph[src][i] && !visited[i])
            {
                findAllPaths(graph, i, dest, visited, path, pathIndex, allPaths, pathCount);
            }
        }
    }

    // Reset the visited flag for the current node
    visited[src] = false;
}

// Function to find all paths between two nodes and return an array of paths
Path* findAllPathsWrapper(int graph[SIZE][SIZE], int src, int dest, int* pathCount)
{
    bool visited[SIZE];
    int path[SIZE];
    *pathCount = 0;

    // Initialize visited array
    for (int i = 0; i < SIZE; i++)
    {
        visited[i] = false;
    }

    Path* allPaths = malloc(SIZE * sizeof(Path));

    findAllPaths(graph, src, dest, visited, path, 0, allPaths, pathCount);

    return allPaths;
}



// Function to free the memory allocated for paths
void freePaths(Path* allPaths, int pathCount)
{
    for (int i = 0; i < pathCount; i++)
    {
        free(allPaths[i].nodes);
    }
    free(allPaths);
}

int* linked_stations(int graph[SIZE][SIZE], int src, int dest, int pathCount, int* length) { //function that returns an array of stations linked to the problematic station
    Path* paths = findAllPathsWrapper(graph, src, dest, &pathCount);
    *length = 0;

    for (int i = 0; i < pathCount; i++) {

        *length += paths[i].length;
    }
    
    int* linked_stations = malloc(*length * sizeof(int));
    int idx = 0;
    for (int i = 0; i < pathCount; i++) {

        for (int j = 0; j < paths[i].length; j++) {
            
            linked_stations[idx] = paths[i].nodes[j];
            idx++;
        }

    }
    for (int i = 0; i < *length; i++) {
        for (int j = i + 1; j < *length;) {
            if (linked_stations[j] == linked_stations[i]) {
                // Shift elements to the left
                for (int k = j; k < *length - 1; k++) {
                    linked_stations[k] = linked_stations[k + 1];
                }
                (*length)--; // Reduce the size of the array
            }
            else {
                j++;
            }
        }
    }
    
    for (int i = 0; i < *length; i++) {
        printf("%d", linked_stations[i]);

    }
    
}



int main()
{
    int graph[SIZE][SIZE] = {
         {1, 1, 4, 7, 4 ,0},
         {2, 0, 9, 0, 0 ,0},
         {5, 0, 0, 6, 2 ,5},
         {1, 2, 3, 4, 8 ,6},
         {1, 2, 3, 4, 0, 1},
         {1, 2, 3, 4, 5, 2},
    };
    int src = 1;
    int dest = 5;

    int pathCount;
    int length;
    Path* allPaths = findAllPathsWrapper(graph, src, dest, &pathCount);

    printf("All Paths from %d to %d:\n", src, dest);
    for (int i = 0; i < pathCount; i++)
    {
        for (int j = 0; j < allPaths[i].length; j++)
        {
            printf("%d ", allPaths[i].nodes[j]);
        }
        printf("\n");
    }

    printf("\nTotal Paths: %d\n", pathCount);

    freePaths(allPaths, pathCount);

    linked_stations(graph, src, dest, pathCount, &length);
 

    return 0;
}
