/*
	Binary Search Tree

	A BST is a binary tree which satisfies the Binary Search Tree property

	Binary Search Tree property:
		For all nodes n in the tree:
		the value of n is greater than all values in it's left sub-tree
		AND
		the value of n is less than all values in it's right sub-tree.

		 k
	   /   \
	  k'    k''

	  k' <= k <= k''

	implements the main Dictionary operations:
		- insertion
		- deletion
		- search
*/

#pragma once

#include "variant.h"

/*****************************************************************************************************************/

typedef struct { int x; } *bst_t;

/*
	Initialize an empty binary search tree
*/
bst_t init_bst(variant_comp_f comparator);

/*
	Free a binary search tree
*/
void free_bst(bst_t bst);

/*****************************************************************************************************************/

/*
	Insert a value into the binary search tree
*/
void bst_insert(bst_t bst, variant_t value);

/*
	Remove a value from the binary search tree
*/
void bst_remove(bst_t bst, variant_t value);

/*
	Checks if the binary search tree contains a value
*/
bool bst_contains(bst_t bst, variant_t value);

/*
	Get the maximum value in the BST
*/
variant_t bst_max(bst_t bst);

/*
	Get the minimum value in the BST
*/
variant_t bst_min(bst_t bst);

/*****************************************************************************************************************/
