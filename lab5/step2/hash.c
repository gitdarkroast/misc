// HASH.C
// Program for use with ELEC278 Lab 5 Part 2.
//
// History:
// 161106	HF	First release
// 171102	DA	Minor tweaks


#include <stdio.h>
#include <stdlib.h>
#include "DLL.h"
#include <time.h>
#include <math.h>

typedef struct HashTable {
	LinkedList** a;
	int size;
	int collisions;
} HashTable;


HashTable* initHashTable(int s)
{
	HashTable* h = malloc(sizeof(HashTable));
	int		i;
	h->size = s;
	h->a = malloc(sizeof(LinkedList) * s);
	for(i=0;i<s;i++)
		h->a[i]= init();
	h->collisions = 0;
	return h;
}//initHashTable()


long h(char* x)
// This function computes a hash code for a given string.  Note that hash
// code is unbounded - it needs to be reduced modulo the size of the array
// used to store the data. (You will see another function hash() below that
// completes the index calculation.)
{
	long	sum=0;
	//#########################COMPLETE THIS FUNCTION##########################
	// Requirements given in lab instructions.
	// ---<SNIP>---
    int slen = strlen(x);
    for (int i = 0; i < slen; i++)
    {
        int s = x[i];
        double power = (double)slen - (double)1 - (double)i;
        sum += s * pow(31, power);
    }
	
	// ---<SNIP>---
	return abs(sum);
}//h()


double loadFactor(HashTable* ht)
{
	double nonempty = 0;
	int i;
	// count number of non-empty hash table slots
	for(i=0; i<ht->size; i++)	{
		if (isEmpty(ht->a[i])==0)	nonempty++;
		}
	return nonempty/ht->size*100;
}//loadFactor()


int hash(char* x, int size)
// Index calculation. Function h() computes general hash for the string;
// this function turns the hash into a valid index, given the size of the
// array.
{
	return h(x) % size;
}


void insert(HashTable *ht, char* x)
{
	//#########################COMPLETE THIS FUNCTION##########################
	// ---<SNIP>---
    int size = ht->size;
    int idx = hash(x, size);

    if (1 == find(ht->a[idx], x))
    {
        // we have a collision
        ht->collisions++;
    }
    else
    {
        addFront(ht->a[idx], x);
    }
    
	// ---<SNIP>---
}//insert()

int remove_key(HashTable* ht, char* x)
{
    int ret = 0;

    int idx = hash(x, ht->size);

    if (1 == find(ht->a[idx], x))
    {
        // We found the key
         // 3 cases:
        // 1 key is at the beginning
        // 2 key is at the end
        // 3 key is in the middle
        Node* ptr = ht->a[idx]->head;
        while (ptr != NULL) {
            if (strcmp(ptr->value, x) == 0)
            {
                break;
            }
            ptr = ptr->next;
        }
        // ptr now points to the item we want to delete
        if (ht->a[idx]->head == ptr)
        {
            removeFront(ht->a[idx]);
        }
        else if (ht->a[idx]->tail == ptr)
        {
            removeEnd(ht->a[idx]);
        }
        else
        {
            // somewhere in the middle
            ptr->next->prev = ptr->prev;
            ptr->prev->next = ptr->next;
        }
        // free(ptr);
        ret = 1;
    }   

    return ret;
}//remove_key()


int findInTable(HashTable *ht, char* x)
{
	//#########################COMPLETE THIS FUNCTION##########################
	// ---<SNIP>---

    // First find the hash code for the string x
    int hcode = hash(x, ht->size);

    // Using find(...) determine if it exists in the hash code location
    return find(*(ht[hcode].a), x);


	// ---<SNIP>---	
}


void printTable(HashTable *ht)
{
	int i;
	printf("----------\n");
	for (i = 0; i < ht->size; i++)	{
		printf("%d --> ", i);
		print(ht->a[i]);
		}
	printf("# of Collisions=%d\n", ht->collisions);
	printf("Load Factor %%=%.2f\n----------", loadFactor(ht));
}


int main() {
	//FILE *fp;
	//fp = fopen("words.txt","w+");
	int i=0;
	HashTable* h = initHashTable(101);


	// Generate a set of random strings (given the way this works, everyone
	// gets the same set of random strings!) insert each into the hash table
	// and then print the table.

    /* Comment this section out.  RFeplace with reading from file
	for(i=0;i<100;i++){
		int x = rand()%5+1;
		char *p = malloc(sizeof(char)*x);
		int j=0;
		for(j=0;j<x;j++)
			p[j] = rand()%26 + 97;
		p[j]='\0';
		insert(h,p);
	}
    */
    FILE* fptr;
    char* fname = "c:\\workspace\\words2.txt";

    // Open file in read only mode.
    fptr = fopen(fname, "r");
    if (NULL == fptr)
    {
        printf("Unable to open file: %s", fname);
        exit(1);
    }


    char word[256]; // buffer to hold the word

    // Get string until we reach end of file
    while (NULL != fgets(word, 256, fptr))
    {
        // fgets also reds the newline character, lets get rid of it
        word[strcspn(word, "\n")] = '\0';
        // now insert the word in the hash table.
        insert(h, word);
    }
    
    fclose(fptr);


	printTable(h);

    char* key = "eee";
    // eee is one key
    if (remove_key(h, key))
    {
        printf("Key: %s, removed successfully\n", key);
    }
    else
    {
        printf("Key: %s, not found\n", key);
    }
    // knife is in words2 middle word - hash id 65
    key = "knife";
    if (remove_key(h, key))
    {
        printf("Key: %s, removed successfully\n", key);
    }
    else
    {
        printf("Key: %s, not found\n", key);
    }
    // goodbye is in words2 end word - hash id 43
    key = "goodbye";
    if (remove_key(h, key))
    {
        printf("Key: %s, removed successfully\n", key);
    }
    else
    {
        printf("Key: %s, not found\n", key);
    }
    // omnibus is in words2 first word - hash id 49
    key = "omnibus";
    if (remove_key(h, key))
    {
        printf("Key: %s, removed successfully\n", key);
    }
    else
    {
        printf("Key: %s, not found\n", key);
    }
    // IDontExist is in neither file
    key = "IDontExist";
    if (remove_key(h, key))
    {
        printf("Key: %s, removed successfully\n", key);
    }
    else
    {
        printf("Key: %s, not found\n", key);
    }
    printTable(h);
	return 0;
}
