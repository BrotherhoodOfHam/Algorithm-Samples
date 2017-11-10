/*
	Insertion sort implementation
*/

#include "sorting.h"

#include <assert.h>

/*****************************************************************************************************************/

/*
	Insert an element into an already sorted vector
*/
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

void isort(vector_t vec, variant_comp_f comparator)
{
	assert(comparator != NULL);

	vector_t buffer = init_vector();

	//For each element
	//Insert into the sorted vector
	for (size_t i = 0; i < get_vector_size(vec); i++)
	{
		insert(buffer, get_vector_element(vec, i), comparator);
	}

	move_vector(vec, buffer);
}

void msort(vector_t vec, variant_comp_f comparator)
{
}

void qsort(vector_t vec, variant_comp_f comparator)
{
}

/*****************************************************************************************************************/
