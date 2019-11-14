// MAXHEAP.H  [161101]
// Provided for use with ELEC278 Lab 6
//
// History:
// 161101	Hesham Farahat	First Release
// 171111	DA				Minor tinkering, comments

#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
	int* a;
	int last;
	int maxSize;
} Heap;


Heap* initHeap(int size)
// Create new heap with maximum capacity of size integers.
// Returns pointer to new heap, or NULL if something failed.
{
	Heap	*h = malloc(sizeof(Heap));
	if (h != NULL)	{
		// allocate array to hold heap data
		h->a = malloc(sizeof(int) * size);
		if (h->a != NULL)	{
			h->last = -1;
			h->maxSize = size;
		} else	{
			// failed to allocate space for heap array.
			free (h);	// discard heap descriptor
			h = NULL;
			}
		}
	return h;
}//initHeap()


void destroyHeap (Heap *h)
// Discard all memory used to hold heap
{
	free (h->a);
	free (h);
}// destroyHeap()


void swapH(int *parray, int i, int j)
// Swap two locations within heap array.  Note that this function takes
// pointer to an integer array, not a heap.
{
	int t = parray[i];   parray[i] = parray[j];    parray[j] = t;
}//swapH()

#define LEFT(i)	(2*i +1)
#define	RITE(i)	(2*i +2)
#define PARENT(i)	((i-1)/2)

void reheapUp(Heap* heap, int index)
{
	if (index > 0)	{
		int parent_index = PARENT(index);
		if (heap->a[index] > heap->a[parent_index])	{
			swapH(heap->a, index, parent_index);
			reheapUp(heap, parent_index);
			}
		}
	return;
}//reheapUp();


long reheapDown(Heap* heap, int i)
{
	int left, right, largest, largestIndex;
	long swaps = 0;
	if (LEFT(i) <= heap->last) {
		left = heap->a[LEFT(i)];
		if (RITE(i) <= heap->last)	right = heap->a[RITE(i)];
		else						right = -1;

		if (left > right || right == -1) {
			largest = left; largestIndex = LEFT(i);
		} else {
			largest = right; largestIndex = RITE(i);
			}
		if (heap->a[i] < largest) {
			swapH(heap->a, i, largestIndex);
			swaps++;
			reheapDown(heap, largestIndex);
			}
		}
	return swaps;
}//reheapDown()


int withdrawMax(Heap* h)
// Remove largest value stored in heap.
{
	int max = h->a[0];			// Capture copy of largest value in heap
	h->a[0] = h->a[h->last];	// Take last value and store it at root
	h->last--;					// Note heap is one node smaller
	reheapDown(h, 0);			// fix damage done to heap
	return max;
}//withdrawMax()


int insert(Heap* heap, int x)
// Insert new value into existing heap.  Checks if heap already full.
// Returns -1 if insert failed; otherwise returns 0.
{
	int		rslt = -1;			// default return value
	// Room to store new value?
	if (heap->last < heap->maxSize - 1)	{
		heap->a[++heap->last] = x;
		reheapUp (heap, heap->last);
		rslt = 0;
		}
	return rslt;
}//insert()


Heap* heapify(int a[], int size)
{
	int   i;
	Heap* h = malloc(sizeof(Heap));
	h->maxSize = size;
	h->a = a;
	h->last = 0;

	for (i = 1; i < size; i++) {
		h->last++;
		reheapUp(h, h->last);
		}
	return h;
}


Heap* heapify2(int a[], int size) {
	int		i;
	Heap* h = malloc(sizeof(Heap));
	h->maxSize = size;
	h->a = a;
	h->last = size-1;
	for (i = size/2; i >= 0; i--) {
		reheapDown(h, i);
		}
	return h;
}


int findMax(Heap* h)
// Find maximum value stored in heap.  As long as heap not empty, maximum
// value is stored in first location in array.
{
	return (h->last != -1) ? h->a[0]  :  -1;
}
