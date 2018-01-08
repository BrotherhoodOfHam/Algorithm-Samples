/*
	Heap data structure implementation

	Internally uses a flat binary tree stored as a vector
*/

#include "heap.h"
#include <assert.h>

/*****************************************************************************************************************
	Heap implementation
******************************************************************************************************************/

typedef struct _impl_heap
{
	variant_comp_f comp;
	vector_t data;
} impl_heap;

#define IMPL(heap) ((impl_heap*)heap)

/*
	References to nodes in the binary heap are essentially indices
*/
typedef index_t nodeview_t;

/*
	Ensure heap property is satisfied

	Using bottom-up heapification

	Linear in the height of the tree
*/
void heapify_parent(heap_t heap, nodeview_t node);

/*
	Ensure heap property is satisfied

	Using top-down heapification

	Linear in the height of the tree
*/
void heapify_children(heap_t heap, nodeview_t node);

/*
	Takes two nodes and returns the node with the largest value
*/
nodeview_t max_node(heap_t heap, nodeview_t a, nodeview_t b);

/*
	Binary tree operations
*/
nodeview_t parent(nodeview_t idx);
nodeview_t rchild(nodeview_t idx);
nodeview_t lchild(nodeview_t idx);

/*
	Swap two values
*/
void swap(vector_t elements, nodeview_t a, nodeview_t b);

/*****************************************************************************************************************/

heap_t init_heap(variant_comp_f comparator)
{
	heap_t h = malloc(sizeof(impl_heap));
	IMPL(h)->comp = comparator;
	IMPL(h)->data = init_vector();
	return h;
}

heap_t make_heap(vector_t elements, variant_comp_f comparator)
{
	heap_t h = init_heap(comparator);

	for (nodeview_t i = 0; i < get_vector_size(elements); i++)
	{
		heap_push(h, get_vector_element(elements, i));
	}

	return h;
}

void free_heap(heap_t heap)
{
	assert(heap != NULL);
	free_vector(IMPL(heap)->data);
	free(heap);
}

void clear_heap(heap_t heap)
{
	assert(heap != NULL);
	clear_vector(IMPL(heap)->data);
}

bool is_heap_empty(heap_t heap)
{
	assert(heap != NULL);
	return is_vector_empty(IMPL(heap)->data);
}

/*****************************************************************************************************************
	Heap operations
******************************************************************************************************************/

variant_t heap_top(heap_t heap)
{
	assert(heap != NULL);
	assert(!is_heap_empty(heap));
	//return front element
	return get_vector_element(IMPL(heap)->data, 0);
}

variant_t heap_pop(heap_t heap)
{
	assert(heap != NULL);
	assert(!is_heap_empty(heap));

	//Top value
	variant_t top = heap_top(heap);

	vector_t elements = IMPL(heap)->data;

	//Set top value to be the last value
	nodeview_t last = get_vector_size(elements) - 1;
	set_vector_element(elements, 0, get_vector_element(elements, last));
	//And then trim the last value
	shrink_vector(elements, 1);

	heapify_children(heap, 0);

	return top;
}

void heap_push(heap_t heap, variant_t element)
{
	assert(heap != NULL);

	impl_heap* h = IMPL(heap);

	//Insert in level order
	add_vector_element(h->data, element);

	//Ensure heap property holds for new element
	heapify_parent((heap_t)h, get_vector_size(h->data) - 1);
}

/*****************************************************************************************************************
	Heapification
*****************************************************************************************************************/

//Get element at vector - helper function
#define GETVAL(node) get_vector_element(elements, node)

void heapify_parent(heap_t heap, nodeview_t node)
{
	assert(heap != NULL);

	vector_t elements = IMPL(heap)->data;
	variant_comp_f comp = IMPL(heap)->comp;
	
	assert(node < get_vector_size(elements));

	nodeview_t curNode = node;
	nodeview_t parentNode = 0;

	//While current node isn't the root
	while (curNode != 0)
	{
		parentNode = parent(curNode);

		//If current value greater than parent value
		if (comp(GETVAL(curNode), GETVAL(parentNode)) > 0)
		{
			//Swap values of both nodes
			swap(elements, curNode, parentNode);
		}

		//Parent is next node
		curNode = parentNode;
	}
}

void heapify_children(heap_t heap, nodeview_t node)
{
	vector_t elements = IMPL(heap)->data;
	variant_comp_f comp = IMPL(heap)->comp;

	//Fetch largest child node
	nodeview_t child = max_node(heap, lchild(node), rchild(node));

	//If node is valid
	if (child < get_vector_size(elements))
	{
		//Compare current node against largest child
		if (comp(GETVAL(node), GETVAL(child)) < 0)
		{
			//If the child is larger swap values
			swap(elements, node, child);

			//Recursively heapify children
			heapify_children(heap, child);
		}
	}
}

nodeview_t max_node(heap_t heap, nodeview_t a, nodeview_t b)
{
	vector_t elements = IMPL(heap)->data;
	variant_comp_f comp = IMPL(heap)->comp;

	//If a doesn't exist return b
	if (a >= get_vector_size(elements))
	{
		return b;
	}

	//If b doesn't exist return a
	if (b >= get_vector_size(elements))
	{
		return a;
	}

	return (comp(GETVAL(a), GETVAL(b)) > 0) ? a : b;
}

nodeview_t parent(nodeview_t idx)
{
	return (idx - 1) / 2;
}

nodeview_t lchild(nodeview_t idx)
{
	return (2 * idx) + 1;
}

nodeview_t rchild(nodeview_t idx)
{
	return (2 * idx) + 2;
}

void swap(vector_t elements, nodeview_t a, nodeview_t b)
{
	variant_t val = get_vector_element(elements, a);
	set_vector_element(elements, a, get_vector_element(elements, b));
	set_vector_element(elements, b, val);
}

/*****************************************************************************************************************/

#include <stdio.h>
void print_heap(heap_t heap)
{
	vector_t vec = IMPL(heap)->data;

	if (!is_vector_empty(vec))
	{
		printf("%lld", get_vector_element(vec, 0));

		for (nodeview_t i = 1; i < get_vector_size(vec); i++)
		{
			printf(", %lld", get_vector_element(vec, i));
		}
	}

	printf("\n");
}
