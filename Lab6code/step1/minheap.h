// MINHEAP.C [161101]
// This code is provided to students in ELEC278 for use in Lab 5.
// History:
// 161101	HF	First release by Hisham Farahat
// 171102	DA	Minor edits

#include <stdio.h>
#include <stdlib.h>

// Heap data structure.  Heap contains pointer to an array of size
// maxSize.  See initHeap() for details on heap instance creation.
typedef struct Heap {
	int	*a;			// pointer to array containing heap elements
	int	last;		// index of last used location in array
	int maxSize;	// size of array (note maxSize = maxIndex + 1)
} Heap;


// Useful shorthand.
// Left child of node i is at (2*i) +1, right child is at (2*i)+2
#define LeftChild(i)	((2 * i) + 1)
#define	RiteChild(i)	((2 * i) + 2)
#define Parent(i)		((i-1)/2)
#define	NOTREE			(-1)


Heap* initHeap(int size)
// Create an instance of a heap. Parameter size is size of array to
// allocate.  Returns pointer to newly created heap storage if memory
// was obtained; NULL if there was any failure to obtain memory.
{
	Heap	*h = malloc(sizeof(Heap));
	if (h != NULL)	{
		h->a = malloc(sizeof(int) * size);
		if (h->a == NULL)	{
			// Didn't get memory for the array - give up completely
			free (h);
			h = NULL;
		} else	{
			h->last = NOTREE;	// so far, nothing in heap
			h->maxSize = size;	// so we know how many can be stored
			}
		}
	return h;		
}//initHeap()


void swapH(int* heap, int i, int j)
// Swap elements at locations i and j in heap.
{
	int t = heap[i];		// save element i in temporary location
	heap[i] = heap[j];		// copy element j into location i
	heap[j] = t;			// copy saved element i into location j
}//swap()


void reheapUp(Heap* heap, int index)
{
	if (index <= 0)
		return;
	else	{
		int parent_index = Parent(index);
		if (heap->a[index] < heap->a[parent_index])
			swapH(heap->a, index, parent_index);
		else
			return;
		reheapUp(heap, parent_index);
		}
}//reheapUp()


long reheapDown(Heap* heap, int i)
{
	int left, right, smallest, smallestIndex;
    long swap = 0;

	if (LeftChild(i) <= heap->last) {
		left = heap->a[LeftChild(i)];
		if (RiteChild(i) <= heap->last) {
			right = heap->a[RiteChild(i)];
		} else {
			right = NOTREE;
			}
		if (left < right || right == NOTREE) {
			smallest = left;
			smallestIndex = LeftChild(i);
		} else {
			smallest = right;
			smallestIndex = RiteChild(i);
			}
		if (heap->a[i] > smallest) {
			swapH(heap->a, i, smallestIndex);
            swap += reheapDown(heap, smallestIndex) + 1;
			}
		}
    return swap;
}//reheapDown()


int withdrawMin(Heap* h)
// Smallest value in heap is at the top of the tree - index 0 in the array
// used to store the tree.  Save that value, then fix the heap.
{
	int min = h->a[0];			// save smallest value
	h->a[0] = h->a[h->last];	// move last element in array to top
	h->last--;					// indicate heap is one smaller
	reheapDown(h,0);			// turn tree into heap by moving top
								// element down to correct position
	return min;					// return smallest value in heap
}


void insert(Heap* h, int x)
// Add new value x to heap
{
	// Is there room?
	if (h->last == h->maxSize - 1)	return;
	h->a[++h->last] = x;
	reheapUp(h, h->last);
}//insert()


int findMin(Heap* h)
// Tell caller smallest value in heap but do not remove value from heap
{
    return ((h != NULL) && (h->last != NOTREE)) ? h->a[0] : NOTREE;
}//findMin()


Heap* copyHeap(Heap* h)
// Make copy of existing heap
{
    Heap* newH = initHeap(h->maxSize);
    int i;
    for(i=0;i<=h->last;i++){
        newH->a[i] = h->a[i];
    	}
    newH->last = h->last;
    return newH;
}


int findkth(Heap* h, int k)
// Finds the kth smallest item in heap, by removing k items, if possible.
{
	Heap* newH = copyHeap(h);
	int min = NOTREE;
	while(k--){
		min = withdrawMin(newH);
	}
	return min;
}


Heap* heapify(int a[], int size)
// Given data in an array, turn it into a heap
{
	int		i;
	Heap* h = malloc(sizeof(Heap));
	h->last = 0;
	h->maxSize = size;
	h->a = a;

	for(i=0;i<size;i++){
		reheapUp(h,h->last);
		//print(h);
		h->last++;
	}
	h->last--;
	return h;
}



