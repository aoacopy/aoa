#include <stdio.h>
#define INF 9999

int graph[100][100];
int cost[100], parent[100], visited[100];
int V; // number of vertices

int findMinVertex() {
    int min = INF, vertex = -1;
    for (int i = 1; i <= V; i++) {
        if (!visited[i] && cost[i] < min) {
            min = cost[i];
            vertex = i;
        }
    }
    return vertex;
}

void prims(int start) {
    for (int i = 1; i <= V; i++) {
        cost[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    cost[start] = 0;

    for (int count = 1; count <= V - 1; count++) {
        int u = findMinVertex();
        if (u == -1) break;
        visited[u] = 1;

        for (int v = 1; v <= V; v++) {
            if (graph[u][v] && !visited[v] && graph[u][v] < cost[v]) {
                cost[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    int mstCost = 0;
    printf("\nMinimum Spanning Tree Edges:\n");
    for (int i = 1; i <= V; i++) {
        if (parent[i] != -1) {
            printf("Edges(%d,%d) : %d\n", parent[i], i, graph[i][parent[i]]);
            mstCost += graph[i][parent[i]];
        }
    }

    printf("\nTotal MST Cost : %d\n", mstCost);
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter adjacency matrix (0 for no edge):\n");
    for (int i = 1; i <= V; i++) {
        for (int j = 1; j <= V; j++) {
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == 0)
                graph[i][j] = INF;
        }
    }

    prims(1); // Start from vertex 1
    return 0;
}
