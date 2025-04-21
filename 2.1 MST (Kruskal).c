#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int graph[MAX][MAX];
int edges[MAX][3]; // edges[i][0]=src, edges[i][1]=dest, edges[i][2]=weight
int parent[MAX], rank[MAX];

int findSet(int x) {
    if (parent[x] != x)
        parent[x] = findSet(parent[x]); // Path compression
    return parent[x];
}

void unionSet(int x, int y) {
    int rootX = findSet(x);
    int rootY = findSet(y);

    if (rootX != rootY) {
        if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

void makeSet(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

// Simplified comparator to sort edges by weight (No pointer casting)
int compare(const void *a, const void *b) {
    // Directly cast the void pointers to integer pointers (array of 3 integers)
    int* edge1 = (int*)a;
    int* edge2 = (int*)b;

    // Compare the weights (the third element of the edges array)
    return edge1[2] - edge2[2];
}

int main() {
    int V, k = 0;  // k = edgecount 

    printf("Enter no of vertices: ");
    scanf("%d", &V);

    printf("Enter adjacency matrix (0 for no edge):\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
            if (i < j && graph[i][j] != 0) { // Undirected edge condition
                edges[k][0] = i;
                edges[k][1] = j;
                edges[k][2] = graph[i][j];
                k++;
            }
        }
    }

    // Sort the edges based on their weight using qsort
    qsort(edges, k, sizeof(edges[0]), compare);

    printf("\nSorted Edge Table:\n");
    for (int i = 0; i < k; i++) {
        printf("(%d, %d) : %d\n", edges[i][0], edges[i][1], edges[i][2]); // 0-based output
    }

    makeSet(V);
    int mstCost = 0;

    printf("\nMinimum Spanning Tree Edges:\n");
    for (int i = 0; i < k; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int wt = edges[i][2];

        if (findSet(u) != findSet(v)) {
            unionSet(u, v);
            mstCost += wt;
            printf("Edges(%d,%d) : %d\n", u, v, wt);  // 0-based output
        }
    }

    printf("\nParent array [] : ");
    for (int i = 0; i < V; i++) {
        printf("%d ", parent[i]);  // 0-based output
    }

    printf("\nRank array   [] : ");
    for (int i = 0; i < V; i++) {
        printf("%d ", rank[i]);
    }

    printf("\n\nTotal MST Cost : %d\n", mstCost);
    return 0;
}


// 4 vertices
// 0 1 4 0
// 1 0 0 2
// 4 0 0 3
// 0 2 3 0
