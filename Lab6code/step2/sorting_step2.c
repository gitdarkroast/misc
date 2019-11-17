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

void print(int *a, int n)
// Print n integers starting at location given by a
{
	int i;
	for (i = 0; i < n; i++)	printf("%d ", a[i]);
	printf("\n");		// make it pretty
}//print()

// swap integer contents of two locations
void swap(long *a, long *b) {int t = *a; *a = *b; *b = t;} //swap()

//*******************Insertion Sort**************************
long insertionSort(int *array, int n)
{
	int i, j, ctr = 0;
	for (i = 1; i < n; i++) {
		for (j = i; j > 0 && (array[j - 1] > array[j]); j--) {
			swap(&array[j], &array[j - 1]);
			ctr++;
			}
		}
	return ctr;
}//insertionSort()


long insertionSortQ(int *array, int left, int right) {
	int i, j;
	int ctr = 0;
	for (i = left + 1; i < right + 1; i++) {
		for (j = i; j > 0 && (array[j - 1] > array[j]); j--) {
			swap(&array[j], &array[j - 1]);
			}
		}
	return ctr;
}

//*******************Bubble Sort**************************
long bubbleSort(int* array, int n)
{
	int i, j, swapped;
	long ctr = 0;

	for (i = 0; i < n; ++i) {
		swapped = 0;	// no swaps yet this pass
		for (j = n - 1; j > i; --j) {
			if (array[j] < array[j - 1]) {
				swapped = 1;
				swap(&array[j], &array[j - 1]);
				}
			}
		// If no exchanges last pass, data is now sorted.
		if (swapped == 0) break;
		}
	return ctr;
}

//*******************Quick Sort**************************

int partition(int* a, int left, int right, int* swaps)
{
	int i = left;
	int j = right - 1;
	int pivot_index = left + (right - left) / 2;
	int pivot = a[pivot_index];
	swap(&a[right], &a[pivot_index]);
	while (i < j) {
		while (a[i] < pivot) i++;
		while (a[j] > pivot) j--;
		if (i <= j) { swap(&a[i], &a[j]); i++; j--; }
		}
	a[right] = a[i];
	a[i] = pivot;
	return i;
}//partition()


int quickSort(int* a, int left, int right) {
	int swaps = 0;
	if (right - left > 2) {
		int pivot = partition(a, left, right, &swaps);
		quickSort(a, left, pivot - 1);
		quickSort(a, pivot + 1, right);
	} else {
		insertionSortQ(a, left, right);
		}
	return swaps;
}//quickSort()

//*******************Heap Sort**************************

long heapSort(int* a, int n)
{
	Heap* h = heapify2(a, n);
	long swaps = 0;
	int i;
	for (i = n - 1; i > 0; i--) {
		swap(&h->a[0], &h->a[i]);
		h->last--;
		reheapDown(h, 0);
		}
	return swaps;
}

//*******************Merge Sort**************************

void merge(int *a, int start, int middle, int end, int *b)
{
	int i;
	int j = start;
	int k = middle + 1;
	for (i = start; j <= middle && k <= end; i++) {
		if (a[j] < a[k])	{ b[i] = a[j]; j++; }
		else				{ b[i] = a[k]; k++; }
		}
	while (j <= middle)	b[i++] = a[j++];

	while (k <= end)	b[i++] = a[k++];

	for (i = start; i <= end; i++) a[i] = b[i];
}
//*******************Merge Sort**************************

void mergeSortR(int* a, int start, int end, int* b) {
    int   middle;
	if (start >= end) return;

	middle = start + (end - start) / 2;
	mergeSortR(a, start, middle, b);
	mergeSortR(a, middle + 1, end, b);
	merge(a, start, middle, end, b);
}

long mergeSort(int* a, int n) {
	int* b = malloc(sizeof(int) * n);
	int i;
	for (i = 0; i < n; i++) { b[i] = a[i]; }
	mergeSortR(a, 0, n - 1, b);
	return 0;
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
}//bucketSort()

//*******************Radix Sort**************************

long radixSort(int *a, int n, int p) {
	int i, j, k;
	for (k = 0; k < p; k++) {
		int count[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		int* tmp = malloc(sizeof(int) * n);
		int* offset = malloc(sizeof(int) * 10);
		for (i = 0; i < n; i++)
			count[(a[i] / (int) pow(10, k)) % 10]++;
		offset[0] = 0;
		for (i = 1; i < 10; i++) {
			offset[i] = 0;
			for (j = 0; j < i; j++) {
				offset[i] += count[j];
				}
			}

		for (i = 0; i < n; i++) {
			tmp[offset[(a[i] / (int) pow(10, k)) % 10]++] = a[i];

			}
		for (i = 0; i < n; i++) { a[i] = tmp[i]; }
		}
	return 0;
}//radixSort()


void initArray(int* a) {
	a[0] = 10;
	a[1] = 24;
	a[2] = 5;
	a[3] = 32;
	a[4] = 1;
	a[5] = 84;
	a[6] = 19;
}

void resetData(int* a, int* m, int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = m[i];
    }
}

int main() {
	int n = 5000000;
	int	*a;
    int* master;
	int		i;
	clock_t  start, end;
	printf("Enter the size of the array:");
	scanf("%d", &n);
	srand(time(NULL));
    for (int j = 0; j < 5; j++)
    {
        a = malloc(sizeof(int) * n);
        master = malloc(sizeof(int) * n);
        for (i = 0; i < n; i++) {
            int r = rand();
            master[i] = a[i] = r;
        }
        printf("**No limitation on data:\n");
        start = clock();
        quickSort(a, 0, n - 1);
        end = clock();
        printf("Quicksort: \tn=%d Elapsed time: \t\t%.2f seconds\n", n, (end - start) / (double)(CLOCKS_PER_SEC));

        resetData(a, master, n);
        start = clock();
        mergeSort(a, n);
        end = clock();
        printf("Merge: \t\tn=%d Elapsed time: \t\t%.2f seconds\n", n, (end - start) / (double)(CLOCKS_PER_SEC));

        resetData(a, master, n);
        start = clock();
        heapSort(a, n);
        end = clock();
        printf("Heap: \t\tn=%d Elapsed time: \t\t%.2f seconds\n", n, (end - start) / (double)(CLOCKS_PER_SEC));
        
        // Doing the mod data
        for (int x = 1; x < 3; x++)
        {
            int m = pow(10, x);
            printf("Sort data is mod %d:\n", m);

            for (i = 0; i < n; i++) {
                int r = rand() % m;
                master[i] = a[i] = r;
            }

            resetData(a, master, n);
            start = clock();
            quickSort(a, 0, n - 1);
            end = clock();
            printf("Quicksort: \tn=%d Elapsed time: \t\t%.2f seconds\n", n, (end - start) / (double)(CLOCKS_PER_SEC));


            resetData(a, master, n);
            start = clock();
            radixSort(a, n, 2);  // 2 => we are mod 10 or 100 to max 2 digits
            end = clock();
            printf("RadixSort: \tn=%d Elapsed time: \t\t%.2f seconds\n", n, (end - start) / (double)(CLOCKS_PER_SEC));
        }
        free(a);
        free(master);
        n += 5000000;
    }
	return 0;
}

