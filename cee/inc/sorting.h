/*
	Sorting algorithms
*/

#pragma once

#include "vector.h"

static int32_t integer_comparator(variant_t a, variant_t b)
{
	if (a == b)
	{
		return 0;
	}
	else if (a < b)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

/*****************************************************************************************************************
	Sorting functions:
/*****************************************************************************************************************/

/*
	Insertion sort

	Worst-case: O(n^2)
*/
void isort(vector_t vec, variant_comp_f comparator);

/*
	Merge sort

	Worst-case: O(nlogn)
*/
void msort(vector_t vec, variant_comp_f comparator);

/*
	Quick sort
*/
//void qsort(vector_t vec, variant_comp_f comparator);

/*****************************************************************************************************************/