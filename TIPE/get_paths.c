#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include "functions.h"

// Function to check if a node is already present in the current path
int isVisited(int path[], int pathLength, int node) {
    for (int i = 0; i < pathLength; i++) {
        if (path[i] == node) {
            return 1;
        }
    }
    return 0;
}

// Recursive function to find all possible paths
void findPaths(int matrix[SIZE][SIZE], int start, int end, int path[], int pathLength, int* allPaths[], int* numPaths) {
    path[pathLength] = start;
    pathLength++;

    if (start == end) {
        int* newPath = (int*)malloc(pathLength * sizeof(int));
        for (int i = 0; i < pathLength; i++) {
            newPath[i] = path[i];
        }
        allPaths[*numPaths] = newPath;
        (*numPaths)++;
    }
    else {
        for (int i = 0; i < SIZE; i++) {
            if (matrix[start][i] && !isVisited(path, pathLength, i)) {
                findPaths(matrix, i, end, path, pathLength, allPaths, numPaths);
            }
        }
    }

    pathLength--;
}


int main() {

    int numNodes = SIZE;
    int src = 1;
    int dest = 5;
 
    int matrix[SIZE][SIZE] = {
        {1, 1, 4, 7, 4 ,0},
        {2, 0, 9, 0, 0 ,0},
        {5, 0, 0, 6, 2 ,5},
        {1, 2, 3, 4, 8 ,6},
        {1, 2, 3, 4, 0, 1},
        {1, 2, 3, 4, 5, 2},
    };
   

    int path[SIZE];
    int pathLength = 0;

    int* allPaths[SIZE];
    int numPaths = 0;

    findPaths(matrix, src, dest, path, pathLength, allPaths, &numPaths);

    printf("Paths between %d and %d:\n", src, dest);
    for (int i = 0; i < numPaths; i++) {
        printf("Path %d: ", i + 1);
        int* currentPath = allPaths[i];
        for (int j = 0; j < pathLength; j++) {
            printf("%d ", currentPath[j]);
        }
        printf("\n");
        free(currentPath);
    }

    return 0;
}