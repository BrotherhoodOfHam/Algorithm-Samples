/*
	Binary search tree tester
*/

#include "bst.h"
#include "sorting.h"
#include "assert.h"

#include <stdio.h>

int test_bst()
{
	bst_t b = init_bst(integer_comparator);

	bst_insert(b, 4);
	bst_insert(b, 3);
	bst_insert(b, 8);
	bst_insert(b, 1);
	bst_insert(b, 1);

	assert(bst_contains(b, 8));
	assert(bst_contains(b, 1));
	assert(bst_contains(b, 3));

	assert(!bst_contains(b, 128));
	assert(!bst_contains(b, 2));
	assert(!bst_contains(b, 10));

	assert(bst_min(b) == 1);
	assert(bst_max(b) == 8);

	bst_remove(b, 8);
	assert(!bst_contains(b, 8));
	bst_remove(b, 3);
	assert(!bst_contains(b, 3));

	bst_remove(b, 1);
	assert(bst_contains(b, 1));

	printf("inserting random elements...\n");

	srand(23648273);

	//add random elements
	for (int i = 0; i < 1024; i++)
	{
		bst_insert(b, rand() % 1024);
	}

	srand(11929834);

	for (int i = 0; i < 10; i++)
	{
		const int r = rand() % 1024;
		printf("contains(%d) = %d\n", r, bst_contains(b, r));
	}

	free_bst(b);

	return 0;
}