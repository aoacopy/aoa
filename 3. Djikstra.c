// At each step:
// Pick the unvisited vertex with the smallest distance.
// Update the distances to its neighbors if a shorter path is found through it.

#include <stdio.h>
#define MAX 50
#define INF 99999

int distance[MAX];  // Distance from source to each vertex
int pred[MAX];      // Predecessor for each vertex
int visited[MAX];   // Track visited vertices
int graph[MAX][MAX];

// Find vertex with minimum distance not yet visited
int minDistance(int V) {
    int min = INF, min_index = -1;

    for(int v = 0; v < V; v++) {
        if(!visited[v] && distance[v] <= min) {
            min = distance[v];
            min_index = v;
        }
    }
    return min_index;
}

void dijkstra(int V, int src) {
    for(int i = 0; i < V; i++) {
        distance[i] = INF;  // all dist inf + no predecssors + no vertex visited 
         pred[i] = -1; 
        visited[i] = 0;
    }
    // dist to source 0 coz dist node to itself = 0 
    distance[src] = 0; 

    for(int count = 0; count < V - 1; count++) {
        int u = minDistance(V); // Visit smallest distance using minDistance() 

        if (u == -1) break; // No reachable vertex remaining
        visited[u] = 1;

        for(int v = 0; v < V; v++) {
            if(!visited[v] && graph[u][v] && distance[u] != INF && distance[u] + graph[u][v] < distance[v]) //graph[u][v]: an edge exists from u to v
            {
                distance[v] = distance[u] + graph[u][v];
                pred[v] = u;
            }
        }
    }
}

// Print as table
void printTable(int V, int src) {
    printf("\n%-10s%-15s%-15s\n", "Vertex", "Distance (D)", "Predecessor (Pi)");
    for(int i = 0; i < V; i++) {
        printf("%-10d%-15d", i + 1, distance[i]); // vertex + distance print karega

        if(pred[i] == -1)
            printf("%-15s\n", "NIL");
        else
            printf("%-15d\n", pred[i] + 1);
    }
}

// Recursively print path from source to destination
void printPath(int src, int dest) {
    if(dest == src) {
        printf("%d", src + 1);
        return;
    }

    if(pred[dest] == -1) {
        printf("No Path");
        return;
    }

    printPath(src, pred[dest]);
    printf(" -> %d", dest + 1);
}

int main() {
    int V, src;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("\nEnter Adjacency Matrix (-1 for no edge):\n");

    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            int weight;
            scanf("%d", &weight);

            if(weight == -1 && i != j)
                graph[i][j] = 0;  // No edge
            else
                graph[i][j] = weight;
        }
    }

    printf("\nEnter Source Vertex (1 to %d): ", V);
    scanf("%d", &src);
    src--;

    dijkstra(V, src);
    printTable(V, src);

    printf("\nShortest Path from %d to each vertex:\n", src + 1);
    for(int i = 0; i < V; i++) {
        if(i != src) {
            printf("Path to %d: ", i + 1);
            printPath(src, i);
            printf("\n");
        }
    }
    return 0;
}


// 0   4   8   0   0   0   0   0   0  
// 4   0  11   8   0   0   0   0   0  
// 8  11   0   0   7   1   0   0   0  
// 0   8   0   0   2   0   7   4   0  
// 0   0   7   2   0   6   0   0   0  
// 0   0   1   0   6   0   2   0   0  
// 0   0   0   7   0   2   0  14   9  
// 0   0   0   4   0   0  14   0  10  
// 0   0   0   0   0   0   9  10   0