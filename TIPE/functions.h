#define SIZE 6


// Structure to represent a path
typedef struct {
    int* nodes;
    int length;
} Path;

int* dijkstra(int graph[SIZE][SIZE], int src, int dest, int* pathLength);

Path* findAllPathsWrapper(int graph[SIZE][SIZE], int src, int dest, int* pathCount);
