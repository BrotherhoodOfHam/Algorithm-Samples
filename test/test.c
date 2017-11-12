/*
	Test function
*/

#include <stdio.h>

#include "vector.h"
#include "sorting.h"
#include "stack.h"
#include "queue.h"

int main(int argc, char** argv)
{
	init_debug();

	/*
		Test vector
	*/
	vector_t vec = init_vector();

	add_vector_element(vec, 14);
	add_vector_element(vec, 13);
	add_vector_element(vec, 12);
	add_vector_element(vec, 11);

	insert_vector_element(vec, 0, 9);
	insert_vector_element(vec, 3, 99);

	remove_vector_element(vec, 1);
	remove_vector_element(vec, 4);

	msort(vec, &integer_comparator);

	for (size_t i = 0; i < get_vector_size(vec); i++)
	{
		printf("vec[%d] = %d\n", i, (uint32_t)get_vector_element(vec, i));
	}

	free_vector(vec);

	/*
		Test stack
	*/
	stack_t st = init_stack();

	push_stack(st, 101);
	push_stack(st, 102);
	push_stack(st, 103);
	push_stack(st, 104);

	printf("top(stack) = %d\n", (uint32_t)top_stack(st));
	pop_stack(st);
	printf("top(stack) = %d\n", (uint32_t)top_stack(st));

	free_stack(st);

	/*
		Test queue
	*/
	queue_t q = init_queue();
	push_queue(q, 16);
	push_queue(q, 64);
	push_queue(q, 2);

	while (!is_queue_empty(q))
	{
		printf("pop(queue) = %d\n", (uint32_t)get_queue_front(q));
		pop_queue(q);
	}

	push_queue(q, 1024);

	free_queue(q);

	return 0;
}
