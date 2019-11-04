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


void swap(int* heap, int i, int j)
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
			swap(heap->a, index, parent_index);
		else
			return;
		reheapUp(heap, parent_index);
		}
}//reheapUp()


void reheapDown(Heap* heap, int i)
{
	int left, right, smallest, smallestIndex;

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
			swap(heap->a, i, smallestIndex);
			reheapDown(heap, smallestIndex);
			}
		}
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


void print(Heap* heap)
// Print array holding the heap.  Does not make levels obvious.
{
	int	i;
	printf("Heap: ");
	for (i = 0; i <= heap->last; i++) {
		printf("%d, ", heap->a[i]);
		}
	printf("\n");
}//print()


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


// Two versions of main() - the first performs a static test; the second
// is for production.

#define TESTING

#ifdef TESTING
int main() {
	/*
    int a[] = { 23, 7, 92, 6, 12, 14, 40, 44, 20, 21 };
	Heap* h = heapify(a, 10);
	int  temp1, temp2;
	print(h);
	temp1 = withdrawMin(h);
	print(h);
	temp2 = withdrawMin(h);
	print(h);
	insert (h, temp1+temp2);
	print (h);
	withdrawMin(h);
	print(h);
    */

    // Using data set from Jessie challenge - slightly changed
    // int a[] = {12, 10, 3, 9, 2, 1 };
    int n = 4;
    int a[4] = { 52, 96, 13, 37 };
    Heap* h = heapify(a, n);
    print(h);
    

    // Minimum sweetness
    int k = 1000;
    int ctr = 0;

    // Some edge cases:
    // 1. no cookies -> -1
    // 2. 1 cookie and it is less than k -> -1
    // 3. 1 cookie and it is more than k -> 0
    // 4. More than 1 cookie - general algorithm
    if (0 == n)
    {
        ctr = -1;
    }
    
    if (1 == n)
    {
        if (k > findMin(h))
        {
            ctr = -1;
        }

        if (k <= findMin(h))
        {
            ctr = 0;
        }
    }
    else
    {
        // While the least sweet cookie is less than the sweetness
        // threshold AND the heap is not empty
        while ((NOTREE != findMin(h)) && (k > findMin(h)))
        {
            int leastSweet = withdrawMin(h);
            int secondleastSweet = withdrawMin(h);
            // Place the new combined cokkie in the heap
            insert(h, leastSweet + (2 * secondleastSweet));
            ctr++;
        }
    }
    
 
    // print(h);
    ctr = ((NOTREE == findMin(h))) ? -1 : ctr;
    printf("Number of operations: %d\n", ctr);
	/*
	Alternate test code
	 Heap* h = initHeap(32);
	 insert(h, 10);
	 print(h);
	 insert(h, 2);
	 print(h);
	 insert(h, 4);
	 print(h);
	 insert(h, 1);
	 print(h);
	 insert(h, 5);
	 print(h);
	 insert(h, 3);
	 print(h);
	 while(h->last!=NOTREE){
	 printf("%d is withdrawn\n",withdrawMin(h));
	 print(h);
	 }
	 */
}

#else


int main()
{
	int		i, n, ctr;
    long    k;
    int		*a;
	Heap	*h;

	// First input gives you two parameters
    scanf("%d %d",&n,&k);
    a = malloc(sizeof(int)*n);
    // Second collection of input gives you all the data
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
   
	// *** Your code goes here ***
	// You need to make the array of data into a heap, then you need
	// to apply Jesse's algorithm on the data.
	// ---<SNIP>--- 
    h = heapify(a, n);
    ctr = 0;
 
    // Some edge cases:
    // 1. no cookies -> -1
    // 2. 1 cookie and it is less than k -> -1
    // 3. 1 cookie and it is more than k -> 0
    // 4. More than 1 cookie - general algorithm
    if (0 == n)
    {
        ctr = -1;
    }

    if (1 == n)
    {
        if (k > findMin(h))
        {
            ctr = -1;
        }

        if (k <= findMin(h))
        {
            ctr = 0;
        }
    }
    else
    {
            // While the least sweet cookie is less than the sweetness
            // threshold.
            while ((NOTREE != findMin(h)) && (k > findMin(h)))
            {
                int leastSweet = withdrawMin(h);
                int secondleastSweet = withdrawMin(h);
                // Place the new combined cokkie in the heap
                insert(h, leastSweet + (2 * secondleastSweet));
                ctr++;
            }
    }
    ctr = ((NOTREE == findMin(h))) ? -1 : ctr;
	// ---<SNIP>---
    printf("%d\n",ctr);
    return 0;
}

#endif

