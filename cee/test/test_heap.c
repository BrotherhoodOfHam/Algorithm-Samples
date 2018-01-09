/*
	Test heap
*/

#include "heap.h"
#include "sorting.h"

#include "assert.h"

int test_heap()
{
	heap_t heap = init_heap(integer_comparator);
	
	heap_push(heap, 2);
	heap_push(heap, 15);
	heap_push(heap, 3);
	heap_push(heap, 4);
	heap_push(heap, 34);
	heap_push(heap, 4);
	heap_push(heap, 10);

	print_heap(heap);

	assert(heap_pop(heap) == 34);
	assert(heap_pop(heap) == 15);
	assert(heap_pop(heap) == 10);

	heap_push(heap, 100);
	assert(heap_pop(heap) == 100);

	free_heap(heap);

	return 0;
}
