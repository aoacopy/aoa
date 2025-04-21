#include <stdio.h>
#include <string.h>

// Preprocessing function to fill LPS (Longest Prefix Suffix) array
void computeLPSArray(char P[], int m, int lps[]) {
    int len = 0; // length of the previous longest prefix suffix
    int i = 1;

    lps[0] = 0; // lps[0] is always 0

    while (i < m) {
        if (P[i] == P[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1]; // try previous prefix
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP string matching function
void KMPSearch(char T[], char P[]) {
    int n = strlen(T);
    int m = strlen(P);
    int lps[100]; // to hold longest prefix suffix values
    int i = 0, j = 0; // i for T[], j for P[]
    int matchCount = 0;

    computeLPSArray(P, m, lps);

    printf("Pattern length (m) = %d\nText length (n) = %d\n", m, n);

    while (i < n) {
        if (T[i] == P[j]) {
            i++;
            j++;
        }

        if (j == m) {
            printf("\nPattern found at index %d", i - j);
            matchCount++;
            j = lps[j - 1]; // look for next match
        } else if (i < n && T[i] != P[j]) {
            if (j != 0) {
                j = lps[j - 1]; // mismatch after j matches
            } else {
                i++;
            }
        }
    }

    printf("\nTotal matches found: %d\n", matchCount);
}

int main() {
    char T[100], P[100];

    printf("Enter Text String: ");
    scanf("%s", T);

    printf("Enter Pattern String: ");
    scanf("%s", P);

    KMPSearch(T, P);
    return 0;
}
