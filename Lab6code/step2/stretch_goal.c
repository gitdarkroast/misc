// SORTING_STEP2.C [161113]
//
// History:
//	161113	HF		First release
//	191014	DFA		Minor edits and format tweaks.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "maxheap.h"

int arr_size = 0;

void print(int *a, int n)
// Print n integers starting at location given by a
{
	int i;
	for (i = 0; i < n; i++)	printf("%d ", a[i]);
	printf("\n");		// make it pretty
}//print()

// swap integer contents of two locations
void swap(long *a, long *b) {int t = *a; *a = *b; *b = t;} //swap()

long insertionSortQ(int* array, int* idx_array, int left, int right) {
    int i, j;
    int ctr = 0;
    for (i = left + 1; i < right + 1; i++) {
        // for (j = i; j > 0 && (array[j - 1] > array[j]); j--)
        for (j = i; j > 0 && (array[idx_array[j - 1]] > array[idx_array[j]]); j--)
        {
            // swap(&array[j], &array[j - 1]);
            swap(&idx_array[j], &idx_array[j - 1]);
            
        }
    }
    return ctr;
}

//*******************Quick Sort**************************

int partition(int a[], int idx_a[], int left, int right, int* swaps)
{
    int i = left;
    int j = right - 1;
    int pivot_index = left + (right - left) / 2;
    printf("Pivot index: %d\n", pivot_index);
    int pivot = a[idx_a[pivot_index]];
    // swap(&a[right], &a[pivot_index]);
    swap(&idx_a[right], &idx_a[pivot_index]);
    while (i < j) {
        while (a[idx_a[i]] < pivot)
        {
            printf("a[idx_a[i]] = %d\n", a[idx_a[i]]);
            i++;
        }
        while ((j >= 0) && (a[idx_a[j]] > pivot))
        {
            printf("a[idx_a[j]] = %d\n", a[idx_a[j]]);
            j--;
        }
        if (i <= j) 
        { 
            swap(&idx_a[i], &idx_a[j]); 
            i++; 
            j--; 
        }
    }
    idx_a[right] = idx_a[i];
    idx_a[i] = pivot_index;
    printf("idx array: ");
    print(idx_a, arr_size);
    return i;
}//partition()




int quickSort(int* a, int* idx_a, int left, int right) {
    int swaps = 0;
    if (right - left > 2) {
        int pivot = partition(a, idx_a, left, right, &swaps);
        quickSort(a, idx_a, left, pivot - 1);
        quickSort(a, idx_a, pivot + 1, right);
    }
    else {
        insertionSortQ(a, idx_a, left, right);
    }
    return swaps;
}//quickSort()



int main() {
    // int a[] = { 34, 17, 62, 91, 3, 37, 59, 18 };
    int a[] = { 34, 17, 62, 91, 3, 37, 59, 18};
    int n = sizeof(a) / sizeof(int);
    int* idx_a = malloc(sizeof(int) * n);

    arr_size = n;

    for(int i = 0; i < n; i++)
    {
        idx_a[i] = i;
    }

    printf("Before Sorting, data:\t\t");
    print(a, n);
    printf("*****\n");

    printf("Before Sorting, index array:\t");
    print(idx_a, n);
    printf("*****\n");

    quickSort(a, idx_a, 0, n - 1);
    printf("After Quick Sort, data:\t\t");
    print(a, n);
    printf("*****\n");
    printf("After Sorting, index array:\t");
    print(idx_a, n);
    printf("*****\n");

    printf("Sorted data using index:\t");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[idx_a[i]]);
    }
    printf("\n");		// make it pretty
	return 0;
}

