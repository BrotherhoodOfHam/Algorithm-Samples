/*
	Quicksort implementation
*/

#include <stdlib.h>
#include "assert.h"
#include "sorting.h"

/*****************************************************************************************************************/

/*
	Seed random number sequence
*/
void init_rand()
{
	time_t t;
	srand((uint32_t)time(&t));
}

/*
	Choose a random pivot index in the sub-array p->r
	and place it at the end of a given vector
*/
void place_pivot(vector_t vec, index_t p, size_t r)
{
	assert(r > p);

	const size_t len = (r - p);

	//Choose random index to be pivot
	const index_t i = p + (rand() % len);

	//Place pivot value at end of array
	swap_vector_element(vec, i, r-1);
}

/*
	Partitions a sub-array such that:
		- left partition is less than the pivot value x
		- right partition is greater than the pivot value x
	
	returns the partition boundary index

	runs in linear time

	-left--right---pivot
	p    q       j   r
	[ ... | ... |...|x]
	  >=x   >x
*/
static index_t partition(vector_t vec, const index_t p, const size_t r, variant_comp_f comp)
{
	//Only arrays with at least two elements can be partitioned
	assert((p + 1) < r);

	//Pick a random pivot value and set it as the last element
	place_pivot(vec, p, r);

	//Set the partition index to start of sub-array
	index_t q = p;

	//Fetch the pivot value
	const variant_t x = get_vector_element(vec, r - 1);

	//For each element in the sub-array
	//(excluding the pivot value)
	for (index_t j = p; j < (r - 1); j++)
	{
		//Fetch current value
		const variant_t v = get_vector_element(vec, j);
		
		//If current value is less than x
		if (comp(v, x) <= 0)
		{
			//Move current value into the left partition
			swap_vector_element(vec, q, j);
			//Increment partition index
			q++;
		}
	}

	//Move pivot value (at end of sub-array) to partition boundary
	//So that all elements to the left are less than the pivot value
	//And all elements to the right are greater than the pivot value
	swap_vector_element(vec, q, r - 1);

	//Return index of partition boundary
	return q;
}

/*
	Sort sub-array p->r
*/
static void sort(vector_t vec, index_t p, size_t r, variant_comp_f comp)
{
	//Check if subarray indices are in range
	assert(p >= 0);
	assert(p <= r);
	assert(r <= get_vector_size(vec));
	
	const size_t len = (r - p);

	//Subarray of length 1 or 0 is already sorted
	//otherwise sort recursively
	if (len > 1)
	{
		const index_t q = partition(vec, p, r, comp);
		
		//Check if partition index is in range
		assert(p <= q);
		assert(q < r);

		sort(vec, p, q, comp);
		sort(vec, q+1, r, comp);
	}
}

/*
	Quick sort implementation
*/
void quicksort(vector_t vec, variant_comp_f comparator)
{
	assert(vec != NULL);

	//Seed random number generator
	init_rand();

	//Recursively sort initial subarray, 0 -> N-1
	sort(vec, 0, get_vector_size(vec), comparator);
}

/*****************************************************************************************************************/
