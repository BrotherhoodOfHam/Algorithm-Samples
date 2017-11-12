/*
	Stack tester
*/

#include <stdio.h>
#include "stack.h"

int test_stack()
{
	stack_t st = init_stack();

	push_stack(st, 101);
	push_stack(st, 102);
	push_stack(st, 103);
	push_stack(st, 104);

	printf("top(stack) = %d\n", (uint32_t)top_stack(st));
	pop_stack(st);
	printf("top(stack) = %d\n", (uint32_t)top_stack(st));

	free_stack(st);

	return 0;
}
