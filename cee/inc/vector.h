/*
	A dynamic array of integers

	C++ style vector so capacity is doubled when size limit is reached
*/

#pragma once

#include "common.h"

#include <stdint.h>
#include <stdbool.h>

#include "variant.h"

/*****************************************************************************************************************/

typedef struct { int x; } *vector_t;

typedef size_t index_t;

#define VECTOR_NSIZE ((size_t)-1)

/*
	Allocate an empty vector
*/
vector_t init_vector();

/*
	Allocate a vector of a given size, with all elements initialized to zero
*/
vector_t alloc_vector(size_t size);

/*
	Free a vector from memory
*/
void free_vector(vector_t v);

/*
	Assign the value of v1 to v0
*/
void move_vector(vector_t v0, vector_t v1);

/*
	Copy a given vector into a new vector
*/
vector_t clone_vector(vector_t v);

/*****************************************************************************************************************
	Operations:
/*****************************************************************************************************************/

bool is_vector_empty(vector_t v);

size_t get_vector_size(vector_t v);

size_t get_vector_capacity(vector_t v);


variant_t get_vector_element(vector_t v, index_t idx);

void set_vector_element(vector_t v, index_t idx, variant_t value);

void add_vector_element(vector_t v, variant_t value);

variant_t remove_vector_element(vector_t v, index_t idx);

void insert_vector_element(vector_t v, index_t idx, variant_t value);

void clear_vector(vector_t v);

/*****************************************************************************************************************/
