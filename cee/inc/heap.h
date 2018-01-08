/*
	Binary heap

	A binary heap is a complete binary tree where the heap property is satisfied.

	Heap property:
		For every node N, the value of N is greater than the values of it's children.

	Operations:
		- top	returns the element at the top of the heap    O(1)
		- pop   removes the top element                       O(log n)     
		- push	add a new element                             O(log n)

	Heap can either be a min heap or max heap depending on the comparator specified

	Example:

           10
         /    \
	    7      5
       / \    /
      2   1  4
*/

#pragma once

#include "variant.h"
#include "vector.h"

/*****************************************************************************************************************/

typedef struct { int x; } *heap_t;

/*
	Initialize an empty heap
*/
heap_t init_heap(variant_comp_f comparator);

/*
	Initialize a heap from a vector of elements
*/
heap_t make_heap(vector_t elements, variant_comp_f comparator);

/*
	Free a heap
*/
void free_heap(heap_t heap);

/*
	Clear a heap of it's elements
*/
void clear_heap(heap_t heap);

/*
	Is heap empty
*/
bool is_heap_empty(heap_t heap);

/*****************************************************************************************************************/

/*
	Return the top element of a heap

	Either largest/smallest depending on comparator
*/
variant_t heap_top(heap_t heap);

/*
	Delete the top element of a heap and return it
*/
variant_t heap_pop(heap_t heap);

/*
	Add a new element to a heap
*/
void heap_push(heap_t heap, variant_t element);

/*****************************************************************************************************************/

void print_heap(heap_t heap);
