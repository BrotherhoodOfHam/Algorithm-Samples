/*
	vector implementation
*/

#include "vector.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

/*****************************************************************************************************************
	Vector implementation
******************************************************************************************************************/

typedef struct _impl_vector
{
	size_t capacity;
	size_t size;
	variant_t* data;
} impl_vector;

#define IMPL(vec) ((impl_vector*)vec)

#define MIN_VECTOR_CAPACITY 16
#define VECTOR_RESIZE_SCALE 2

/*****************************************************************************************************************
	Internal functions
******************************************************************************************************************/

//grow internal capacity
void resize_vector(impl_vector* v, size_t c)
{
	//Allocate new buffer
	void* b = malloc(sizeof(variant_t) * c);

	//If data already exists
	if (v->data != NULL)
	{
		//Copy old into new buffer
		memcpy(b, v->data, v->size * sizeof(variant_t));
		free(v->data);
	}

	v->data = b;
	v->capacity = c;
}

//scale internal capacity
void scale_vector(impl_vector* v)
{
	resize_vector(v, max(v->capacity * VECTOR_RESIZE_SCALE, MIN_VECTOR_CAPACITY));
}

/******************************************************************************************************************/

vector_t init_vector()
{
	//Allocate vector header
	impl_vector* v = malloc(sizeof(impl_vector));
	v->capacity = 0;
	v->size = 0;
	v->data = NULL;

	return (vector_t)v;
}

vector_t alloc_vector(size_t size)
{
	impl_vector* v = (impl_vector*)init_vector();
	
	//Resize capacity
	resize_vector(v, max(size, MIN_VECTOR_CAPACITY));
	//Update size attribute
	v->size = size;

	return (vector_t)v;
}

void free_vector(vector_t v)
{
	assert(v != NULL);

	//free data
	if (!is_vector_empty(v))
	{
		free(IMPL(v)->data);
	}

	//free vector header itself
	free(v);
}

void move_vector(vector_t v0, vector_t v1)
{
	//Free v0's data
	if (IMPL(v0)->data != NULL)
	{
		free(IMPL(v0)->data);
	}

	//Move v1 to v0
	IMPL(v0)->data = IMPL(v1)->data;
	IMPL(v0)->size = IMPL(v1)->size;
	IMPL(v0)->capacity = IMPL(v1)->capacity;

	IMPL(v1)->data = NULL;
	IMPL(v1)->size = 0;
	IMPL(v1)->capacity = 0;

	//Free v1
	free_vector(v1);
}

vector_t clone_vector(vector_t v)
{
	vector_t clone = alloc_vector(get_vector_size(v));

	for (size_t i = 0; i < get_vector_size(v); i++)
	{
		set_vector_element(clone, i, get_vector_element(v, i));
	}

	return clone;
}

/*****************************************************************************************************************
	Operations:
/*****************************************************************************************************************/

bool is_vector_empty(vector_t v)
{
	return get_vector_size(v) == 0;
}

size_t get_vector_size(vector_t v)
{
	assert(v != NULL);
	return IMPL(v)->size;
}

size_t get_vector_capacity(vector_t v)
{
	assert(v != NULL);
	return IMPL(v)->capacity;
}

variant_t get_vector_element(vector_t v, index_t idx)
{
	assert(get_vector_size(v) > idx);
	return IMPL(v)->data[idx];
}

void set_vector_element(vector_t v, index_t idx, variant_t value)
{
	assert(get_vector_size(v) > idx);
	IMPL(v)->data[idx] = value;
}

void add_vector_element(vector_t v, variant_t value)
{
	assert(v != NULL);
	impl_vector* iv = IMPL(v);

	//Check if there is space for one more element
	if (iv->size >= iv->capacity)
	{
		//Otherwise increase capacity
		scale_vector(iv);
	}

	//At last element
	iv->data[iv->size] = value;
	iv->size++;
}

variant_t remove_vector_element(vector_t v, index_t idx)
{
	assert(v != NULL);
	assert(idx < get_vector_size(v)); //in range

	impl_vector* iv = IMPL(v);

	variant_t val = iv->data[idx];

	//Shift all elements to the left
	for (size_t i = idx; i < get_vector_size(v); i++)
	{
		iv->data[i] = iv->data[i + 1];
	}

	//Decrement size
	iv->size--;

	return val;
}

void insert_vector_element(vector_t v, index_t idx, variant_t value)
{
	assert(v != NULL);
	assert(idx < get_vector_size(v)); //in range
	
	impl_vector* iv = IMPL(v);

	//Check if there is space for one more element
	if (iv->size >= iv->capacity)
	{
		//Otherwise increase capacity
		scale_vector(iv);
	}

	//Shift all elements from idx onwards by one
	for (int32_t i = (get_vector_size(v) - 1); i >= (int32_t)idx; i--)
	{
		iv->data[i + 1] = iv->data[i];
	}

	//update value at idx
	iv->data[idx] = value;
	//Increment size
	iv->size++;
}

void clear_vector(vector_t v)
{
	assert(v != NULL);
	IMPL(v)->size = 0;
}

/*****************************************************************************************************************/
