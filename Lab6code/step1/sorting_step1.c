// SORTING_STEP1.C [161113]
// Supplied for use with ELEC278 Lab 6
//
// History:
// 161113	Hesham Farahat	First Release
// 171111	DA				Minor tweaking

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "minheap.h"


void print(int *a, int n)
// Print contents of array
{
	int i;
	for (i = 0; i < n; i++)	printf("%d ", a[i]);
	printf("\n");
}//print()


void swap (int *a, int *b)
// Swap two integers.  Parameters are pointers to integers, so integers
// can be anywhere.
{
	int t = *a;    *a = *b;    *b = t;
}//swap()


//*******************Insertion Sort**************************
long insertionSort(int *array, int n) {
	int i, j;
	int ctr = 0;
	for (i = 1; i < n; i++) {
		for (j = i; j > 0 && (array[j - 1] > array[j]); j--) {
			swap(&array[j], &array[j - 1]);
			ctr++;
		}
	}
	return ctr;
}


long insertionSortQ(int *array, int left, int right) {
	int i, j;
	int ctr = 0;
	for (i = left + 1; i < right + 1; i++) {
        // ascending: (array[j - 1] > array[j])
        // descending: (array[j - 1] < array[j])
		for (j = i; j > 0 && (array[j - 1] < array[j]); j--) {
			swap(&array[j], &array[j - 1]);
            ctr++;
		}
	}
	return ctr;
}


//*******************Bubble Sort**************************
long bubbleSort(int* array, int n) {
	int i, j, swapped;
	long ctr = 0;

	for (i = 0; i < n; ++i) {
		swapped = 0;
		for (j = n - 1; j > i; --j) {
            // ascending: (array[j] < array[j - 1])
            // descending: (array[j] > array[j - 1])
			if (array[j] > array[j - 1]) {
				swapped = 1;
				swap(&array[j], &array[j - 1]);
                ctr++;
			}
		}
		if (swapped == 0) break;
	}
	return ctr;
}


//*******************Quick Sort**************************

int partition(int* a, int left, int right, long* swaps) {
	int i = left;
	int j = right - 1;
	int pivot_index = left + (right - left) / 2;
	int pivot = a[pivot_index];
	swap(&a[right], &a[pivot_index]);
	while (i < j) {
        // ascending:
        // while (a[i] < pivot) i++;
        // while (a[j] > pivot) j--;
        // descending:
        // while (a[i] > pivot) i++;
        // while (a[j] < pivot) j--;
		while (a[i] > pivot) i++;
		while (a[j] < pivot) j--;
		if (i <= j) {
			swap(&a[i], &a[j]);
			i++;
			j--;
		}
	}
	a[right] = a[i];
	a[i] = pivot;
	return i;
}


long quickSort(int* a, int left, int right) {
	long swaps = 0;
	if (right - left > 2) {
		int pivot = partition(a, left, right, &swaps);
        swaps += quickSort(a, left, pivot - 1) + 1;
        swaps += quickSort(a, pivot + 1, right) + 1;
	} else {
		 insertionSortQ(a, left, right);
	}
	return swaps;
}

//*******************Heap Sort**************************

long heapSort(int* a, int n) {
	Heap* h = heapify(a, n);
	long swaps = 0;
	int i;
	for (i = n - 1; i > 0; i--) {
		swap(&h->a[0], &h->a[i]);
		h->last--;
		swaps += reheapDown(h, 0);
	}
	return swaps;
}

//*******************Merge Sort**************************

long merge(int*a, int start, int middle, int end, int*b) {
	int i;
	int j = start;
	int k = middle + 1;
    int swaps = 0;
    // printf("merge: start = %d, middle = %d, end = %d\n", start, middle, end);
	for (i = start; j <= middle && k <= end; i++) {
        // ascending: a[j] < a[k]
        // descending: a[j] > a[k]
		if (a[j] > a[k]) {
			b[i] = a[j];
			j++;
            swaps++;
		} else {
			b[i] = a[k];
			k++;
		}
	}
	while (j <= middle)
		b[i++] = a[j++];

	while (k <= end)
		b[i++] = a[k++];

	for (i = start; i <= end; i++)
		a[i] = b[i];
    return swaps;
}

//*******************Merge Sort**************************

long mergeSortR(int* a, int start, int end, int* b) {
	int		middle;
    int swaps = 0;
	if (start >= end) return;

	middle = start + (end - start) / 2;
	mergeSortR(a, start, middle, b);
	mergeSortR(a, middle + 1, end, b);
	swaps = merge(a, start, middle, end, b);
    
    return swaps;
}

long mergeSort(int* a, int n) {
	int* b = malloc(sizeof(int) * n);
	int i;
    int swaps = 0;
	for (i = 0; i < n; i++) {
		b[i] = a[i];
	}
	swaps = mergeSortR(a, 0, n - 1, b);
	return swaps;
}
//*******************Bucket Sort**************************

void bucketSort(int *a, int n, int b) {
	int* buckets = malloc(sizeof(int) * b);
	int i, j, k;
	for (i = 0; i < b; i++) // initialize buckets array
		buckets[i] = 0;
	for (i = 0; i < n; i++) // count number of repeated data in each bucket
		buckets[a[i]]++;
	i = 0;
	for (j = 0; j < b; j++) { // loop for every bucket
		for (k = 0; k < buckets[j]; k++) {
			a[i] = j;
			i++;
			}
		}
}

//*******************Radix Sort**************************

long radixSortOrig(int *a, int n, int p) {
	int i, j, k;
    for (k = 0; k < p; ++k)
    {
        int count[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        // int* tmp = malloc(sizeof(int) * n);
        // int* offset = malloc(sizeof(int) * 10);
        int tmp[] = { 0, 0, 0, 0, 0, 0, 0 };
        int offset[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        for (i = 0; i < n; i++)
        {
            int cidx = (a[i] / (int)pow(10, k)) % 10;
            count[cidx]++;
        }

        offset[0] = 0;
        
        for (i = 1; i < 10; i++)
        {
            offset[i] = 0;
            for (j = 0; j < i; j++)
            {
                offset[i] += count[j];
            }
        }
        
        // for (i = 0; i < n; i++)
        for (i = (n-1); i >= 0; i--)
        {
            int idx = offset[(a[i] / (int)pow(10, k)) % 10]++;
            tmp[idx] = a[i];
        }
        for (i = 0; i < n; i++)
        {
            a[i] = tmp[i];
        }
    }
	return 0;
}

long radixSort(int* a, int n, int p)
{
    int i, m = 0, exp = 1, b[10];
    for (i = 0; i < n; i++)
        if (a[i] > m)
            m = a[i];
    while (m / exp > 0)
    {
        int bucket[10] = { 0 };
        for (i = 0; i < n; i++)
            bucket[9 - a[i] / exp % 10]++;         // changed this line
        for (i = 1; i < 10; i++)
            bucket[i] += bucket[i - 1];
        for (i = n - 1; i >= 0; i--)
            b[--bucket[9 - a[i] / exp % 10]] = a[i]; // changed this line
        for (i = 0; i < n; i++) {
            a[i] = b[i];                       // changed this line
        }
        exp *= 10;
    }
}


void initArray(int* a) {
	a[0] = 10;
	a[1] = 24;
	a[2] = 5;
	a[3] = 32;
	a[4] = 1;
	a[5] = 84;
	a[6] = 19;
}


int main() {
	int a[] = { 10, 24, 5, 32, 1, 84, 19 };
	int n = 7;
	long	swaps = 0;
	printf("Before   Sorting:\t\t");
	print(a, n);
	printf("*****\n");

	swaps = insertionSortQ(a, 0, n - 1);
	printf("After Insertion Sort:\t\t");
	print(a, n);
	printf("Number of swaps: %ld\n*****\n",swaps);

	initArray(a);
	swaps = bubbleSort(a, n);
	printf("After Bubble Sort:\t\t");
	print(a, n);
	printf("Number of swaps: %ld\n*****\n",swaps);

	initArray(a);
	swaps = quickSort(a, 0, n - 1);
	printf("After Quick Sort:\t\t");
	print(a, n);
	printf("Number of swaps: %ld\n*****\n",swaps);


	initArray(a);
	swaps = heapSort(a, n);
	printf("After Heap  Sort:\t\t");
	print(a, n);
	printf("Number of swaps: %ld\n*****\n",swaps);


	initArray(a);
	swaps = mergeSort(a, n);
	printf("After Merge Sort:\t\t");
	print(a, n);
	printf("Number of swaps: %ld\n*****\n",swaps);


	initArray(a);
	swaps = radixSort(a, n, 3);
	printf("After Radix Sort:\t\t");
	print(a, n);
	printf("Number of swaps: %ld\n",swaps);


	return 0;
}
