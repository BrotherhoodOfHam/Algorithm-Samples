/*
	Test function
*/

#include <stdio.h>

#include "vector.h"
#include "sorting.h"

int main(int argc, char** argv)
{
	init_debug();

	vector_t vec = init_vector();

	add_vector_element(vec, 14);
	add_vector_element(vec, 13);
	add_vector_element(vec, 12);
	add_vector_element(vec, 11);

	insert_vector_element(vec, 0, 9);
	insert_vector_element(vec, 3, 99);

	//remove_vector_element(vec, 1);
	//remove_vector_element(vec, 4);

	msort(vec, &integer_comparator);

	for (size_t i = 0; i < get_vector_size(vec); i++)
	{
		printf("vec[%d] = %d\n", i, (uint32_t)get_vector_element(vec, i));
	}

	free_vector(vec);

	return 0;
}
