/*
	Stack implementation
*/

#include "stack.h"
#include "vector.h"
#include "assert.h"

/*****************************************************************************************************************/

#define IMPL(s) ((vector_t)s)

/*****************************************************************************************************************/

stack_t init_stack()
{
	return (stack_t)init_vector();
}

void free_stack(stack_t s)
{
	assert(s != NULL);
	free_vector(IMPL(s));
}

void move_stack(stack_t s0, stack_t s1)
{
	move_vector(IMPL(s0), IMPL(s1));
}

stack_t clone_stack(stack_t s)
{
	return clone_vector(IMPL(s));
}

variant_t top_stack(stack_t s)
{
	assert(s != NULL);
	assert(!is_stack_empty(s));
	return get_vector_element(IMPL(s), get_stack_size(s) - 1);
}

void push_stack(stack_t s, variant_t e)
{
	assert(s != NULL);
	add_vector_element(IMPL(s), e);
}

void pop_stack(stack_t s)
{
	assert(s != NULL);
	assert(!is_stack_empty(s));
	remove_vector_element(IMPL(s), get_stack_size(s) - 1);
}

bool is_stack_empty(stack_t s)
{
	return get_stack_size(s) == 0;
}

size_t get_stack_size(stack_t s)
{
	return get_vector_size(IMPL(s));
}

void clear_stack(stack_t s)
{
	clear_vector(IMPL(s));
}

/*****************************************************************************************************************/
