/*
	Queue implementation
*/

#include "queue.h"

#include <assert.h>

/*****************************************************************************************************************/

typedef struct _queue_link
{
	struct _queue_link* next;
	variant_t value;
} queue_link;

typedef struct _impl_queue
{
	queue_link* first;
	queue_link* last;
} impl_queue;

#define IMPL(q) ((impl_queue*)q)


static queue_link* alloc_link(queue_link* next, variant_t value)
{
	queue_link* link = (queue_link*)malloc(sizeof(queue_link));
	link->next = next;
	link->value = value;
	return link;
}

static void free_link(queue_link* q)
{
	if (q != NULL)
	{
		free_link(q->next);
		free(q);
	}
}

/*****************************************************************************************************************/

queue_t init_queue()
{
	impl_queue* q = IMPL(malloc(sizeof(impl_queue)));
	q->first = NULL;
	q->last = NULL;
	return (queue_t)q;
}

void free_queue(queue_t q)
{
	assert(q != NULL);

	if (!is_queue_empty(q))
	{
		free_link(IMPL(q)->first);
	}

	free(q);
}

/*****************************************************************************************************************
	Operations:
/*****************************************************************************************************************/

void push_queue(queue_t q, variant_t e)
{
	impl_queue* iq = IMPL(q);

	if (is_queue_empty(q))
	{
		iq->first = alloc_link(NULL, e);
		iq->last = iq->first;
	}
	else
	{
		iq->last->next = alloc_link(NULL, e);
		iq->last = iq->last->next;
	}
}

void pop_queue(queue_t q)
{
	assert(!is_queue_empty(q));

	impl_queue* iq = IMPL(q);

	queue_link* next = iq->first->next;
	iq->first->next = NULL;
	free_link(iq->first);
	iq->first = next;

	//If first is now null
	if (iq->first == NULL)
	{
		//reset last
		iq->last = NULL;
	}
}

bool is_queue_empty(queue_t q)
{
	assert(q != NULL);
	return IMPL(q)->first == NULL;
}

size_t get_queue_size(queue_t q)
{
	assert(q != NULL);

	if (is_queue_empty(q))
	{
		return 0;
	}

	size_t depth = 1;
	impl_queue* iq = IMPL(q);
	queue_link* cur = iq->first;

	while (cur != iq->last)
	{
		cur = cur->next;
		depth++;
	}

	return depth;
}

variant_t get_queue_front(queue_t q)
{
	assert(q != NULL);
	return IMPL(q)->first->value;
}

/*****************************************************************************************************************/
