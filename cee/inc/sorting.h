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

	Best-case:  O(n)
	Worst-case: O(n^2)
*/
void insertionsort(vector_t vec, variant_comp_f comparator);

/*
	Merge sort

	A divide and conquer sorting algorithm.

	Average-case:  O(nlogn)
	Worst-case:    O(nlogn)
*/
void mergesort(vector_t vec, variant_comp_f comparator);

/*
	Quick sort

	A divide and conquer sorting algorithm.
	Elements are sorted in-place.

	Average-case:  O(nlogn)
	Worst-case:    O(n^2)
*/
void quicksort(vector_t vec, variant_comp_f comparator);

/*****************************************************************************************************************/