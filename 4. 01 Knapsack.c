#include <stdio.h>
#define MAX 100

// Function to find maximum of two integers     
int max(int a, int b) {
    return (a > b) ? a : b;
}

// 0/1 Knapsack implementation
void knapsack(int n, int weights[], int profits[], int capacity) {
    int K[n + 1][capacity + 1]; // Matrix to store solutions rows - items , columns - capacity 

    // Build the matrix K[][] in bottom-up manner
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0; // Base case: 0 items or 0 capacity

            // checks if current item can fit in capacity
            else if (weights[i - 1] <= w)  
                // k[i][w] = max(include,exclude)
                K[i][w] = max(profits[i - 1] + K[i - 1][w - weights[i - 1]], K[i - 1][w]);
            else
                // Can't include item i-1 because it exceeds current capacity
                K[i][w] = K[i - 1][w];
        }
    }

    // Print the Knapsack matrix (DP table)
    printf("\nKnapsack Matrix (K[i][w]):\n");
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            printf("%3d ", K[i][w]); 
        }
        printf("\n");
    }

    // Backtrack to find solution vector
    int solution[n];    // = 1 if item i is included
    for (int i = 0; i < n; i++) 
        solution[i] = 0;    // Initialize all to 0

    int i = n, w = capacity;
    while (i > 0 && w > 0) {
        if (K[i][w] != K[i - 1][w]) {
            // If value changes from previous row, item i-1 was included
            solution[i - 1] = 1; 
            w = w - weights[i - 1]; // Reduce remaining capacity
        }
        i--;
    }

    // Print solution vector
    printf("\nSolution Vector (Items included = 1):\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", solution[i]);
    }

    // Total profit earned
    printf("\nTotal Profit Earned: %d\n", K[n][capacity]);
}

int main() {
    int n, capacity;
    int weights[MAX], profits[MAX];

    printf("Enter maximum capacity of knapsack: ");
    scanf("%d", &capacity);

    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter weights of %d items:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &weights[i]);

    printf("Enter profits of %d items:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &profits[i]);

    knapsack(n, weights, profits, capacity);

    return 0;
}


// OUTPUT EXAMPLE

// Enter number of items: 4
// Enter weights of 4 items:
// 2 3 4 5
// Enter profits of 4 items:
// 3 4 5 6
// Enter maximum capacity of knapsack: 5

// Knapsack Matrix (K[i][w]):
//   0  0  0  0  0  0 
//   0  0  3  3  3  3 
//   0  0  3  4  4  7 
//   0  0  3  4  5  7 
//   0  0  3  4  5  7 

// Solution Vector (Items included = 1):
// 0 1 0 0 
// Total Profit Earned: 7

