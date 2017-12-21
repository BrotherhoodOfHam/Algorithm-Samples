/*
	Merge sort implementation
*/

#include "sorting.h"

/*****************************************************************************************************************/

static vector_t subvector(vector_t a, index_t lower, index_t upper)
{
	vector_t r = alloc_vector(upper - lower);

	for (index_t i = lower; i < upper; i++)
	{
		set_vector_element(r, i - lower, get_vector_element(a, i));
	}

	return r;
}

static void insert(vector_t vec, variant_t value, variant_comp_f comparator)
{
	index_t insertionIdx = 0;

	for (size_t i = 0; i < get_vector_size(vec); i++)
	{
		if (comparator(get_vector_element(vec, i), value) > 0)
		{
			break;
		}

		insertionIdx++;
	}

	if (insertionIdx < get_vector_size(vec))
	{
		insert_vector_element(vec, insertionIdx, value);
	}
	else
	{
		add_vector_element(vec, value);
	}
}

static vector_t merge(vector_t a, vector_t b, variant_comp_f comp)
{
	vector_t temp = init_vector();
	move_vector(temp, a);

	for (index_t i = 0; i < get_vector_size(b); i++)
	{
		insert(temp, get_vector_element(b, i), comp);
	}

	free_vector(b);

	return temp;
}

static vector_t merge_sort(vector_t input, variant_comp_f comp)
{
	size_t n = get_vector_size(input);

	if (n == 0)
	{
		return init_vector();
	}
	else if (n == 1)
	{
		return input;
	}
	else
	{
		vector_t v = merge(merge_sort(subvector(input, 0, n / 2), comp), merge_sort(subvector(input, n / 2, n), comp), comp);
		free_vector(input);
		return v;
	}
}

void msort(vector_t vec, variant_comp_f comparator)
{
	move_vector(vec, merge_sort(clone_vector(vec), comparator));
}

/*****************************************************************************************************************/