/*
	Queue tester
*/

#include <stdio.h>
#include "queue.h"

int test_queue()
{
	queue_t q = init_queue();
	push_queue(q, 16);
	push_queue(q, 64);
	push_queue(q, 2);

	while (!is_queue_empty(q))
	{
		printf("pop(queue) = %d\n", (uint32_t)get_queue_front(q));
		pop_queue(q);
	}

	push_queue(q, 1024);

	free_queue(q);

	return 0;
}
