#include <stdio.h>
#include <string.h>
#define MAX 100

// Returns max of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to find and print LCS length, sequence, and matrix
void LCS(char str1[], char str2[]) {
    int m = strlen(str1);
    int n = strlen(str2);

    int L[m + 1][n + 1];         // LCS length matrix
    char direction[m + 1][n + 1];  // To store direction arrows

    // Fill LCS matrix and direction matrix (CHECK YT VID)
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                L[i][j] = 0;
                direction[i][j] = '0'; // No direction
            }
            else if (str1[i - 1] == str2[j - 1]) {
                L[i][j] = L[i - 1][j - 1] + 1;
                direction[i][j] = '\\'; // Diagonal arrow
            }
            else if (L[i - 1][j] >= L[i][j - 1]) {
                L[i][j] = L[i - 1][j];
                direction[i][j] = '^'; // Upward arrow
            }
            else {
                L[i][j] = L[i][j - 1];
                direction[i][j] = '<'; // Left arrow
            }
        }
    }

    // Backtrack to find LCS characters
    int index = L[m][n];
    char lcs_string[index + 1];
    lcs_string[index] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (str1[i - 1] == str2[j - 1]) {
            lcs_string[index - 1] = str1[i - 1];
            i--;
            j--;
            index--;
        }
        else if (L[i - 1][j] > L[i][j - 1])
            i--;
        else
            j--;
    }

    // Print matrix with arrows
    printf("\nLCS Matrix with Arrows:\n");
    printf("    ");
    for (int j = 0; j <= n; j++) {
        if (j == 0)
            printf("  ");
        else
            printf(" %c ", str2[j - 1]);
    }
    printf("\n");

    for (int i = 0; i <= m; i++) {
        if (i == 0)
            printf("  ");
        else
            printf("%c ", str1[i - 1]);

        for (int j = 0; j <= n; j++) {
            printf("%d%c ", L[i][j], direction[i][j]);
        }
        printf("\n");
    }

    // Print final results
    printf("\nLength of LCS: %d", L[m][n]);
    printf("\nLongest Common Subsequence: %s\n", lcs_string);
}

int main() {
    char str1[MAX], str2[MAX];

    printf("Enter 1st String : ");
    scanf("%s", str1);
    printf("Enter 2nd String : ");
    scanf("%s", str2);

    LCS(str1, str2);
    return 0;
}
