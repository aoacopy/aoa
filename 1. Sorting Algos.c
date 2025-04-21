#include <stdio.h>
int merge_calls = 0;
int quick_calls = 0;

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Insertion Sort Implementation
void insertion_sort(int a[], int n) {
    int i, k, key;
    
    printf("\nOriginal Array: ");
    print_array(a, n);
    
    // Start with the second element (index 1)
    for (k = 1; k < n; k++) {
        // Store current element as key
        key = a[k];
        i = k - 1;
        
        // Move elements greater than key to one position ahead
        while (i >= 0 && key < a[i]) {
            a[i + 1] = a[i]; // Shift element right
            i--;
        }
        // Place key at its correct position
        a[i + 1] = key;
        
        // Print array after each pass to show progress
        printf("Pass %d: ", k);
        print_array(a, n);
    }
}

// Selection Sort Implementation
void selection_sort(int a[], int n) {
    int i, j, min, pos;
    
    printf("\nOriginal Array: ");
    print_array(a, n);
    
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++) {
        // Find the minimum element in unsorted array
        min = a[i];
        pos = i;
        
        // Find minimum element in unsorted portion
        for (j = i + 1; j < n; j++) {
            if (min > a[j]) {
                min = a[j];
                pos = j; // Track index of minimum element
            }
        }
    
        // Swap the found minimum element with the first element
        a[pos] = a[i];
        a[i] = min;
        
        // Print array after each pass
        printf("Pass %d: ", i + 1);
        print_array(a, n);
    }
}

// Merge two subarrays of arr[]
// First subarray is arr[low..mid]
// Second subarray is arr[mid+1..high]
void merge(int arr[], int low, int mid, int high) {
    int i, j, k;
    int n1 = mid - low + 1; // Size of left subarray
    int n2 = high - mid;    // Size of right subarray
    
    // Create temporary arrays
    int L[n1], R[n2];
    
    // Copy data to temporary arrays
    for (i = 0; i < n1; i++)
        L[i] = arr[low + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
        
    // Merge the temporary arrays back into arr[low..high]
    i = 0;      // Initial index of left subarray
    j = 0;      // Initial index of right subarray
    k = low;    // Initial index of merged subarray
    
    // Compare elements and merge in sorted order
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Copy remaining elements of L[] if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Copy remaining elements of R[] if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Main merge sort function
void merge_sort(int arr[], int low, int high) {
    merge_calls++; // Track number of recursive calls
    
    if (low < high) {
        // Find the middle point to divide array into two halves
        int mid = low + (high - low) / 2;
        
        // Sort first and second halves
        merge_sort(arr, low, mid);
        merge_sort(arr, mid + 1, high);
        
        // Merge the sorted halves
        merge(arr, low, mid, high);
    }
}

// Utility function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function for Quick Sort
// Takes last element as pivot and places it at its correct position
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Choose the rightmost element as pivot
    int i = low - 1;       // Index of smaller element
    
    // Compare each element with pivot and swap if needed
    for (int j = low; j < high; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++; // Increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    
    // Place pivot at its correct position
    swap(&arr[i + 1], &arr[high]);
    return i + 1; // Return pivot's position
}

// Main Quick Sort function
void quick_sort(int arr[], int low, int high) {
    quick_calls++; // Track number of recursive calls
    
    if (low < high) {
        // Find partition point
        int pi = partition(arr, low, high);
        
        // Recursively sort elements before and after partition
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

int main() {
    int arr[50], temp[50], n, choice;
    
    // Get array size and elements from user
    printf("Enter array size: ");
    scanf("%d", &n);
    
    printf("Enter array elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    
    // Menu-driven loop
    do {
        printf("\n--- SORTING MENU ---\n");
        printf("1. Insertion Sort\n");
        printf("2. Selection Sort\n");
        printf("3. Quick Sort\n");
        printf("4. Merge Sort\n");
        printf("5. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        // Copy original array to temp array to preserve original input
        for (int i = 0; i < n; i++)
            temp[i] = arr[i];
            
        switch (choice) {
            case 1:
                insertion_sort(temp, n);
                break;
                
            case 2:
                selection_sort(temp, n);
                break;
                
            case 3:
                printf("\nOriginal Array: ");
                print_array(temp, n);
                
                quick_calls = 0; // Reset call counter
                quick_sort(temp, 0, n - 1);
                
                printf("Sorted Array: ");
                print_array(temp, n);
                printf("Calls to Quick Sort: %d\n", quick_calls);
                break;
                
            case 4:
                printf("\nOriginal Array: ");
                print_array(temp, n);
                
                merge_calls = 0; // Reset call counter
                merge_sort(temp, 0, n - 1);
                
                printf("Sorted Array: ");
                print_array(temp, n);
                printf("Calls to Merge Sort: %d\n", merge_calls);
                break;
                
            case 5:
                printf("Exiting program...\n");
                break;
                
            default:
                printf("Invalid choice...\n");
        }
    } 
    while (choice != 0);
    return 0;
}