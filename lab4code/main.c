// MAIN.C - ELEC278 Lab exercise 4 - Fall 2019
//
// *** DO NOT EDIT THIS CODE ***
//
// See instructions in the lab handout.  You will be adding code
// to avl.c.  This code is intended to verify that your code works.
//
// HISTORY:
// 14xxxx	MM	First release
// 161003	DFA	Minor comments added
// 171016	DFA	Changed date
// 181008	DFA	Rewrote - turned sequence into loop.
// 191003	DFA Changed date, tweaked a comment


#include <stdio.h>
#include "avl.h"

int main(void)
{
	int		datavalues [10] = {10, 3, 1, 7, 20, 15, 18, 17, 16, 22 };
	int		v1 = 1;
	int		dt;
	Tree *t = initTree();

	// Insert each data value from the array datavalues, and after
	// inserting, display the tree using in-order traversal.
	for (dt = 0; dt < 10; dt++)	{
		insert(datavalues[dt], &v1, t);
		printf("Inorder: ");
		inOrderT(t->root);
		printf("\n-------\n");
		}
	return 0;
}//main()
