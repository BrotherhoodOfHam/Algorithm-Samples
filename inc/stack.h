/*
	Stack implementation
	
	LIFO
*/

#pragma once

#include "common.h"

#include <stdint.h>
#include <stdbool.h>

#include "variant.h"

/*****************************************************************************************************************/

typedef struct { int x; } *stack_t;

/*
	Allocate empty stack
*/
stack_t init_stack();

/*
	Free a stack
*/
void free_stack(stack_t s);

/*
	Return top element of stack
*/
variant_t top_stack(stack_t s);

/*
	Add an element to the stack
*/
void push_stack(stack_t s, variant_t e);

/*
	Remove element from stack
*/
void pop_stack(stack_t s);

/*
	Return if stack is empty
*/
bool is_stack_empty(stack_t s);

/*
	Return size of stack
*/
size_t get_stack_size(stack_t s);

/*****************************************************************************************************************/
