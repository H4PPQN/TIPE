
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "metro_v.h"
#include "functions.h"
/*
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


    int pathLength;
    int* path = dijkstra(graph, src, dest, &pathLength);

    printf("Shortest Path from %d to %d: ", src, dest);
    for (int i = 0; i < pathLength; i++)
    {
        printf("%d ", path[i]);
    }
    printf("\n");

    free(path);

    return;
}
*/