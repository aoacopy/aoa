#include <stdio.h>

int w[10], x[10], n, W; // w[] = input elements, x[] = 0/1 decision array, n = number of elements, W = target sum
int callCount = 0;  // count for no of fn calls

// Recursive function to find subsets that sum to W
void sumOfSubsets(int k, int currentSum, int r) {

    int i;
    callCount++;  // Increment function call count
    x[k] = 1;  // Include the current element w[k]

    // Case 1: current subset sum exactly matches the target
    if (currentSum + w[k] == W) {
        printf("\nSubset: ");
        for (i = 0; i <= k; i++) {
            if (x[i] == 1)
                printf("%d ", w[i]);  // Print included elements
        }
    }

    // Case 2: try adding next element if it's promising (won’t exceed W)
    else if (currentSum + w[k] + w[k + 1] <= W) {
        sumOfSubsets(k + 1, currentSum + w[k], r - w[k]);  // Include w[k] and move forward
    }

    // Case 3: backtrack – exclude current element and explore other branches
    if ((currentSum + r - w[k]) >= W && (currentSum + w[k + 1]) <= W) {    // (( r IS REMAINING WEIGHT ))  
        // ^^ w[k] hatake bhi W reach ho sakta / w[k + 1] add kara to bhi W exceed nahi hora 2 conditions

        x[k] = 0;  // Do not include w[k]
        sumOfSubsets(k + 1, currentSum, r - w[k]);    // Exclude w[k] and check further...
    }
}   

int main() {
    int i, total = 0;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements in increasing order: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &w[i]);  // Input array elements
        total = total + w[i];  // calculate total sum of elements
    }

    printf("Enter target sum: ");
    scanf("%d", &W);

    if (total < W) {
        printf("\nNo subset possible.\n");
    } else {
        sumOfSubsets(0, 0, total);  // Start from first element
        printf("\n\nTotal calls to sumOfSubsets: %d\n", callCount);
    }

    return 0;
}
