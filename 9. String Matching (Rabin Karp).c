#include <stdio.h>
#include <string.h>
#include <math.h>

// Rabin-Karp string matching function
void rabinKarp(char T[], char P[], int d, int q) {
    int n, m, h;
    int i, j;
    int p = 0;        // Hash value for pattern
    int t = 0;        // Hash value for current text window 
    int totalMatches = 0;  // total hash matches (including false positives)
    int actualMatches = 0; // actual pattern matches

    m = strlen(P);    // len of pattern
    n = strlen(T);    // len of textw

    printf(" Pattern length (m) = %d\n Text length (n) = %d", m, n);

    // Hash multiplier + Hash calculation for pattern and first window of text
    h = (int)pow(d, m - 1) % q;
    
    for (i = 0; i < m; i++) {
        p = (d * p + P[i]) % q;
        t = (d * t + T[i]) % q;
    }

    // Slide the pattern over text (n-m coz utne combos hai check karneko)
    for (j = 0; j <= n - m; j++) {
        // If hashes match, check characters
        if (p == t) {
            totalMatches++;

            for (i = 0; i < m; i++) { // compares each char of Pattern P[i] w/ char of text window T[j + i]
                if (T[j + i] != P[i])
                    break;
            }

            // If full match (ie upar ka loop reaches m)
            if (i == m) {
                printf("\n\nPattern found at index %d with hash %d", j, t); 
                actualMatches++;
            }
        }

        // Calculate next hash value
        if (j < n - m) {
            t = (d * (t - T[j] * h) + T[j + m]) % q; //direct formula hai (removes leftmost and adds rightmost character)
            if (t < 0)
                t = t + q; // if result -ve, add q (primemod)
        }
    }

    printf("\nTotal matches found: %d", actualMatches);
    printf("\nTotal hash matches (including false positives): %d\n", totalMatches);
}

int main(void) {
    char T[100], P[100];
    int d = 256;  // Character set size (ASCII)
    int q = 11;   // Prime number for hashing

    printf("Enter Text String: ");
    scanf("%s", T);

    printf("Enter Pattern String: ");
    scanf("%s", P);

    rabinKarp(T, P, d, q);
    return 0;
}

// j represents the starting index of the current window (substring) of the text you're comparing the pattern to.
// For example, if T = "abcdef" and P = "cde" (length 3), then:

// When j = 0: you compare "abc" with "cde"
// When j = 1: you compare "bcd" with "cde"
// When j = 2: you compare "cde" with "cde" → match!

// Slide the pattern over text

// for (j = 0; j <= n - m; j++) {   --  (( n-m )) coz utne m window length fit honge in n text size 