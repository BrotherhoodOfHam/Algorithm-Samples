/*
	Test vector
*/

#include <stdio.h>
#include <assert.h>

#include "vector.h"
#include "sorting.h"

typedef void(*sorting_func)(vector_t, variant_comp_f);

bool is_sorted(vector_t vec)
{
	variant_t prev = get_vector_element(vec,0);

	for (size_t i = 0; i < get_vector_size(vec); i++)
	{
		if (prev > get_vector_element(vec, i))
		{
			return false;
		}

		prev = get_vector_element(vec, i);
	}

	return true;
}

bool test_sorting_func(vector_t v, sorting_func func, variant_comp_f comp)
{
	//Clone input vector because we want to preserve the original vector
	vector_t copy = clone_vector(v);

	func(copy, comp);
	bool result = is_sorted(copy);

	free_vector(copy);

	return result;
}

int test_vector()
{
	vector_t vec = init_vector();

	//test vector operations
	add_vector_element(vec, 14);
	add_vector_element(vec, 13);
	add_vector_element(vec, 12);
	add_vector_element(vec, 11);

	insert_vector_element(vec, 0, 9);
	insert_vector_element(vec, 3, 99);

	remove_vector_element(vec, 1);
	remove_vector_element(vec, 4);

	//add random elements
	for (int i = 0; i < 1024; i++)
	{
		add_vector_element(vec, rand());
	}

	//test sorting functions
	printf("insertionSort()\n");
	assert(test_sorting_func(vec, insertionsort, integer_comparator));
	printf("mergeSort()\n");
	assert(test_sorting_func(vec, mergesort, integer_comparator));
	printf("quickSort()\n");
	assert(test_sorting_func(vec, quicksort, integer_comparator));

	free_vector(vec);

	return 0;
}

