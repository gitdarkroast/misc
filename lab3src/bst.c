// BST.C [140916]
// 
// Code for ELEC278 Lab 3.  Some code has already been implemented.
// You will develop your own code - look for the comments.
// History:
//	14xxxx			Original
//	161013	DFA		Corrected initNode()
//	171002	DFA		Corrected some syntax, logic errors
//

#include <stdlib.h>
#include <stdio.h>
#include "bst.h"


Node *initNode (Key k, void *v)
// Allocate memory for new node and initialize fields.
// Returns pointer to node created.
{
	Node *n = malloc(sizeof(Node));
	// initialize node if memory obtained
	if (n != NULL)	{
		n->key = k;
		n->value = v;
		n->leftChild = NULL;
		n->rightChild = NULL;
		}
	return n;
}//initNode()


/*
Tree *initTree(Key k, void *v)
// Set up new tree. Allocates memory for Tree structure, then
// calls initNode() to allocate first node.
{
	Tree* t = malloc(sizeof(Tree));
	if (t != NULL)
		t->root = initNode(k,v);
	return t;
}//initTree()
*/
Tree *initTree()
// Set up new tree. Allocates memory for Tree structure.  Initially
// it is an empty tree - no nodes
{
	Tree* t = malloc(sizeof(Tree));
    // for this excercise we assume no memory allocation
    // issue.  Otherwise we should check if t is valid.
	return t;
}//initTree()

void printTreeExplanation (void)
// Prints hint to reader what to expect on screen
{
	static int done = 0;
	if (!done)	{
		printf ("First time explanation of tree display:\n");
		printf ("Every node is displayed as a comma-separated pair within brackets:");
		printf (" (kk,vv)\n");
		printf ("A tree starts with a { and ends with a }.  An empty tree will be {}\n");
		printf ("A tree with no children will be { (kk,vv),{},{} }\n");
		printf ("If either subtree is populated, it will be shown using the same ");
		printf ("technique\n============\n\n");
		done = 1;
		}
}//printTreeExplanation()


void printTree (Node* root)
// Print whole tree. We cannot make it look pretty graphically, so we add some
// characters to make it a little easier to understand.  We also don't really
// know what the value field is - it is declared to be a void pointer - so we
// treat it as though it points to an integer.
{
	// assume printTree magically know the types in the tree node
	printTreeExplanation();
	// start of this tree
	printf("{");
	// values in the root node (assuming value is pointing to an integer)
	printf("(%ld,%d),", root->key, *(int*)root->value);
	
	// Now show left subtree or {} if there is no left subtree
	if (root->leftChild != NULL)	printTree(root->leftChild);
	else							printf("{}");
	// Marker between left and right subtrees		
	printf(",");
	// Now show right subtree or {} if there is no right subtree
	if (root->rightChild != NULL)	printTree(root->rightChild);
	else							printf("{}");
	// Close display of this tree with closing curly bracket	
	printf("}");
}//printTree()


Node *find (Key k, Node *root)
// Function locates node with key value equal to parameter k. Parameter
// root holds pointer to root node of tree. Function returns immediately
// if either root pointer is null, or the node that root points to has
// key value sought.  If neither of those conditions is true, then the
// function calls itself with a pointer to either the left or right
// subtree.
{
	// termination conditions - either true, search is ended
	if ((root == NULL) || (root->key == k))	return root;
	// search continues.  Since this is a search tree, we know that
	// every key in the right subtree is bigger than the key in the tree's
	// root, and every key in the left subtree is smaller than the key in
	// the tree's root.  That allows us to choose the appropriate subtree
	// to search.
	if (k > root->key)
		// Key value sought is larger than current node key, so search right
		// subtree
		return find(k,root->rightChild);
	else
		// Key value sought is smaller than current node key (the equal case
		// was handled as a termination condition in the first line), so
		// search left subtree
		return find(k,root->leftChild);	
}//find()



int insert(Key k, void *v, Node *root)
// Function inserts a new node into the tree, with key k and value pointed to
// by v. Parameter root points to root node of tree.
{
	int result = 0;
	// this if statement can only be true with the first root (root of whole tree)
	if (root == NULL)	{
		Node *n = initNode(k,v);
		root = n;
		return 1;
		}
	
	// already exists in tree ==> can't insert
	if (root->key == k)
		result = 0;
	else if (k < root->key) {
		// key value less than key value in root node - try to insert into left
		// subtree, if it exists.
		if (root->leftChild != NULL)
			// there is a left subtree - insert it
			result = insert(k, v, root->leftChild);
		else {
			// new Node becomes the left subtree
			Node *n = initNode(k,v);
			root->leftChild = n;
			result = 1;
			}
	} else if (k > root->key) {			// test actually redundant
		// key is greater than this nodes key value, so value goes into right
		// subtree, if it exists
		if (root->rightChild != NULL)
			// there is a right subtree - insert new node
			result = insert(k,v,root->rightChild);
		else {
			// no right subtree - new node becomes right subtree
			Node*n = initNode(k,v);
			root->rightChild = n;
			result = 1;
			}
		}
	return result;	
}//insert()


int intmax(int a, int b)
// YOU WILL USE THIS FUNCTION WHEN YOU IMPLEMENT HEIGHT() !!
// Useful function - returns the greater value of two integers.
// Called intmax, not max, because max already exists.
// It is a chance to see the conditional value in C - a value that is the
// first one (after the ?) if the condition is true, or the second one (after
// the :) if the condition is false.
{
	return (a>=b) ? a : b;
}//intmax()


int height(Node *root)
// Height definition:
// Height of an empty tree is -1.  Height of a leaf node is 0. Height of other
// nodes is 1 more than bigger height of node's two subtrees.
{ 
	// your code goes here  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// ---<SNIP>----
	
	// if the root is empty OR the root has no children then we are done
	if((NULL == root) || ((NULL == root->leftChild) && (NULL == root->rightChild)))
	{
		return 0;
	}
	// Otherwise we recurse the left side and then the right side and get the max height
	return(intmax(height(root->leftChild), height(root->rightChild)) + 1);
	// ---<SNIP>----
	// return -1;   // <<<  Remove this !!!
}//height()


Node *findParentHelper (Key k, Node *root)
// Help find parent of node with key == k. Parameter root is node with
// at least one child (see findParent()).
{
	// your code goes here  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// ---<SNIP>----
    if(NULL == root)
    {
        return root;
    }
    if(k < root->key)
    {
        // Make sure a left child exists and if so check the key
        // if it matches we have the parent!
        if((NULL != root->leftChild) && (k == root->leftChild->key))
        {
            return root;
        }
        // Otherwise we recurse down the left side - this is why 
        // we checked if k was less than the key
        return findParentHelper(k, root->leftChild);
    }

    if(k > root->key)
    {
        // Make sure a right child exists and if so check the key
        // if it matches we have the parent!
        if((NULL != root->rightChild) && (k == root->rightChild->key))
        {
            return root;
        }
        // Otherwise we recurse down the right side - this is why 
        // we checked if k was greater than the key
        return findParentHelper(k, root->rightChild);
    }
	// ---<SNIP>----
	// return NULL;  // <<<< Remove this !!
}//findparenthelper()


Node* findParent(Key k, Node* root)
{
	// Deal with special special cases which could only happen for root
	// of whole tree
	if (root == NULL)	return root;	
	// real root doesn't have parent so we make it parent of itself
	if (root->key == k)	return root;	
	// root has no children
	if ((root->leftChild == NULL) && (root->rightChild == NULL)) 
			return NULL;
	
	// Deal with cases where root has at least one child
	return findParentHelper(k, root);
}//findParent()


void delete (Node* p, Node *n)
// Delete node pointed to by n.
// Parameters:
//	n	- points to node to be deleted
//	p	- points to parent of node to be deleted.
{
	// your code goes here  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// ---<SNIP>----
    // We have parent p and node n.  What we need to know is if n is the left child
    // or the right child.
    int isRightChild = 0;    // assume it is left
    if(p->rightChild->key == n->key)
    {
        isRightChild = 1;
    }
    // Case #1: Node to delete has no children
    if((NULL == n->leftChild) && (NULL == n->rightChild))
    {
        printf("Node to delete has no children.\n");
        // Need to update parent to point to NULL
        if(isRightChild)
        {
            p->rightChild = NULL;
        }
        else
        {
            p->leftChild = NULL;
        }
        // delete trhe node
        free(n);
    } // Case 2a: Node to delete has one child on the right
    else if(NULL == n->leftChild)
    {
        printf("Node to delete has one child on the right.\n");
        // Node to delete has one child on the right
        if(isRightChild)
        {
            p->rightChild = n->rightChild;
        }
        else
        {
            p->leftChild = n->rightChild;
        }
        free(n);
    } // Case 2b: Node to delete has one child on the left
    else if(NULL == n->rightChild)
    {
        printf("Node to delete has one child on the left.\n");
        // Node to delete has one child on the left
        if(isRightChild)
        {
            p->rightChild = n->leftChild;
        }
        else
        {
            p->rightChild = n->rightChild;
        }
        free(n);

    }
    else // Case #3: Node to delete has twp children
    {
        printf("Node to delete has two chilren, not implemented yet.\n");
    }

	// ---<SNIP>----
}//delete()


int withdraw(Key k, Node* root, Node* n)
// Withdraw does two things:
//	return a copy of the node with key k (and value v)
//	Delete the node with key k from the tree while ensuring the tree remains valid
{
	Node *p, *m;
	m = find(k, root);
	
	if (m != NULL)	{
		// create a copy of the node with the same key and value
		n = initNode(m->key,m->value);
		p = findParent(k,root);
		// can delete the node
		delete(p,m);
		return 1;
	}
	
	return 0;	
}//withdraw()

































