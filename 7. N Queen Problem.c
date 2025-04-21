#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

int board[SIZE];             // Stores column positions for each row
int backtrackSteps = 0;      // Counts total steps in backtracking
int functionCalls = 0;       // Counts total recursive function calls

// Checks if placing a queen at (row, col) is safe ( RETURN 1 IS SAFE ) 
int isSafe(int row, int col) {
    for (int prevRow = 1; prevRow < row; prevRow++) {
        // Check same column or diagonal threat
        if (board[prevRow] == col || 
            abs(board[prevRow] - col) == abs(prevRow - row)) {
            return 0;
        }
    }
    return 1;
}

// Displays the board configuration
void displayBoard(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf((board[i] == j) ? "Q " : "- "); 
        }
        printf("\n");
    }
}

// Solves N-Queens using backtracking
void solveNQueens(int row, int n) {
    functionCalls++;      // Count function call
    backtrackSteps++;     // Count each step attempt

    for (int col = 1; col <= n; col++) {
        if (isSafe(row, col)) {
            board[row] = col;    // Place queen

            if (row == n) {
                // Found a solution
                printf("Solution: ");
                for (int i = 1; i <= n; i++) {
                    printf("%d ", board[i]);
                }
                printf("\nBoard:\n");
                displayBoard(n);
                printf("\n");
            } else {
                solveNQueens(row + 1, n);  // Recurse to next row
            }
        }
    }
}

int main() {
    int n;

    printf("Enter the number of Queens: ");
    scanf("%d", &n);
    solveNQueens(1, n);

    printf("Backtracking steps: %d\n", backtrackSteps);
    printf("Total calls to solveNQueens: %d\n", functionCalls);

    return 0;
}
