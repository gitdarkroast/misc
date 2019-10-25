// AVL.H - ELEC278 Lab exercise 4 - Fall 2019
//
// HISTORY:
// 14xxxx	MM	First release
// 161003	DFA	Minor comments added
// 181008	DFA	More comments added; changed date.

#include <stdlib.h>
#include <stdio.h>

// Some typedefs just to make it slightly easier to read
typedef int Key;
typedef struct _node	Node;	// actual _node definition follows.
typedef struct _tree	Tree;	// actual _tree definition follows.

// Node in tree has key and pointer to value associated with key.
// Also contains structural components - two pointers to left and
// right subtrees, and the node's height.
struct _node	{
	Key		key;
	void	*value;
	Node	*leftChild, *rightChild;
    int		height;
	};

// Tree description is basically pointer to top node in tree. In other
// implementations, it might make sense to store more information
// in the Tree data structure.
struct _tree	{
	Node	*root;
	};


// Prototypes for functions found in AVL.C

// Create new node with key = k and value = v 
Node *initNode (Key k, void *v);

// Set up new tree. Allocates memory for Tree structure,
// then initializes root pointer to NULL.
Tree *initTree(void);

// Find node with key k in tree. Returns NULL if not found. Returns
// pointer to node if found
Node *find( Key k, Node *root );

// Create new node with key=k, value=v and insert it into tree. Returns 1 on
// success, 0 on failure
Node* insertNode(Key k, void *v, Node *root);

// Create new node with key=k, value=v and insert it into tree 
// Returns 1 upon success 0 otherwise 
void insert(Key k, void *v, Tree *t);

// Print text representation of tree
void printTree (Node* root);
void printTree2 (Node* root);	// alternate to printTree()

// Traverse tree inorder, printing information as it proceeds
void inOrderT(Node* root);

// Returns Maximum of two numbers 
int maxint (int a, int b);

// Find parent of node n where n->key = k; returns NULL if not found
Node* findParent(Key k, Node* root);


// ***** FUNCTIONS YOU IMPLEMENT AS PART OF LAB ******

// Return the height of the tree (height of the root)
//int height(Node *root);

// Helper function for findParent
Node* findParentHelper(Key k, Node* root);

// Rotate to right - return new root pointer
Node	*rotateRight(Node* root);

// Rotate to left - return new root pointer
Node	*rotateLeft(Node* root);

// Get balance factor for node - difference between left and right
// subtree heights
int		getBalanceFactor(Node* root);

// Calculate height of node, from the heights of left and right subtrees.
int		calcHeight(Node* root);
