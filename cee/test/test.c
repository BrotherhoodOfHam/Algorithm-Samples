/*
	Test function
*/

#include <stdio.h>
#include <assert.h>

#include "common.h"
#include "vector.h"
#include "sorting.h"
#include "stack.h"
#include "queue.h"
#include "tree.h"

int test_vector();
int test_stack();
int test_queue();
int test_tree();
int test_heap();

int main(int argc, char** argv)
{
#ifdef WIN32
	init_debug();
#endif

	printf("~~~~~~~~~ vector ~~~~~~~~~\n");
	assert(test_vector() == 0);
	printf("~~~~~~~~~ stack ~~~~~~~~~\n");
	assert(test_stack() == 0);
	printf("~~~~~~~~~ queue ~~~~~~~~~\n");
	assert(test_queue() == 0);
	printf("~~~~~~~~~ tree ~~~~~~~~~\n");
	assert(test_tree() == 0);
	printf("~~~~~~~~~ heap ~~~~~~~~~\n");
	assert(test_heap() == 0);


	return 0;
}
