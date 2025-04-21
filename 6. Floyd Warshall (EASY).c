#include <stdio.h>
#define MAX 50
#define INF 99999

int distance[MAX][MAX];  // Matrix to store shortest distances
int pred[MAX][MAX];      // Predecessor matrix for path tracking

// Initialize distance and predecessor matrices
void initializeMat(int V) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) {
                distance[i][j] = 0;
                pred[i][j] = -1;
            } else if (distance[i][j] == INF) {
                pred[i][j] = -1;
            } else {
                pred[i][j] = i; // Predecessor is source
            }
        }
    }
}

// Print Distance matrix
void printDistMat(int V) {
    printf("\nDistance Matrix (D): \n\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (distance[i][j] == INF)
                printf("%4s", "INF");
            else
                printf("%4d", distance[i][j]);
        }
        printf("\n");
    }
}

// Print Predecessor matrix
void printPredMat(int V) {
    printf("\nPredecessor Matrix (Pi): \n\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (pred[i][j] == -1)
                printf("%4s", "NIL");
            else
                printf("%4d", pred[i][j] + 1); // 1-based indexing for display
        }
        printf("\n");
    }
}

// checks if including k in path i to j gives shorter path (& updates)
void floydWarshall(int V) {
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (distance[i][k] != INF && distance[k][j] != INF &&   // checks if ik and kj path exists
                    distance[i][k] + distance[k][j] < distance[i][j]) {     // & if its shorter
                    
                    distance[i][j] = distance[i][k] + distance[k][j];
                    pred[i][j] = pred[k][j]; // Update predecessor (for i to j, go from i to pred[k][j]
                }
            }
        }
    }
}

// Recursively print the path from i to j
void printPath(int i, int j) {
    if (i == j) {
        printf("%d", i + 1);
        return;
    }
    if (pred[i][j] == -1) {
        printf("No Path");
        return;
    }
    printPath(i, pred[i][j]);
    printf(" -> %d", j + 1);
}

int main() {
    int V;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("\nEnter Adjacency Matrix (-1 for no edge between nodes):\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            int weight;
            scanf("%d", &weight);

            if (weight == -1 && i != j)
                distance[i][j] = INF; // No edge
            else
                distance[i][j] = weight; // Edge weight
        }
    }

    initializeMat(V);
    floydWarshall(V);

    printDistMat(V);
    printPredMat(V);

    printf("\nShortest Path between every pair of vertices:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i != j) {
                printf("Shortest path from %d to %d: ", i + 1, j + 1);
                printPath(i, j);
                printf("\n");
            }
        }
    }
    return 0;
}



// OUTPUT EXAMPLE
// Enter number of vertices: 5

// Enter Adjacency Matrix (-1 for no edge between nodes):
// 0 -1 6 3 -1
// 3 0 -1 -1 -1 
// -1 -1 0 2 -1
// -1 1 1 0 -1
// -1 4 -1 2 0

// Distance Matrix (D): 

//    0   4   4   3 INF
//    3   0   7   6 INF
//    6   3   0   2 INF
//    4   1   1   0 INF
//    6   3   3   2   0

// Predecessor Matrix (Pi): 

//  NIL   4   4   1 NIL
//    2 NIL   4   1 NIL
//    2   4 NIL   3 NIL
//    2   4   4 NIL NIL
//    2   4   4   5 NIL

// Shortest Path between every pair of vertices:
// Shortest path from 1 to 2: 1 -> 4 -> 2
// Shortest path from 1 to 3: 1 -> 4 -> 3
// Shortest path from 1 to 4: 1 -> 4
// Shortest path from 1 to 5: No Path
// Shortest path from 2 to 1: 2 -> 1
// Shortest path from 2 to 3: 2 -> 1 -> 4 -> 3
// Shortest path from 2 to 4: 2 -> 1 -> 4
// Shortest path from 2 to 5: No Path
// Shortest path from 3 to 1: 3 -> 4 -> 2 -> 1
// Shortest path from 3 to 2: 3 -> 4 -> 2
// Shortest path from 3 to 4: 3 -> 4
// Shortest path from 3 to 5: No Path
// Shortest path from 4 to 1: 4 -> 2 -> 1
// Shortest path from 4 to 2: 4 -> 2
// Shortest path from 4 to 3: 4 -> 3
// Shortest path from 4 to 5: No Path
// Shortest path from 5 to 1: 5 -> 4 -> 2 -> 1
// Shortest path from 5 to 2: 5 -> 4 -> 2
// Shortest path from 5 to 3: 5 -> 4 -> 3
// Shortest path from 5 to 4: 5 -> 4
