/*
	Queue implementation

	FIFO
*/

#pragma once

#include "common.h"
#include "variant.h"

#include <stdint.h>
#include <stdbool.h>

/*****************************************************************************************************************/

typedef struct { int x; } *queue_t;

/*
	Allocate empty queue
*/
queue_t init_queue();

/*
	Free a queue
*/
void free_queue(queue_t q);

/*
	Add an element to the queue
*/
void push_queue(queue_t q, variant_t e);

/*
	Remove element from queue
*/
void pop_queue(queue_t q);

/*
	Return if queue is empty
*/
bool is_queue_empty(queue_t q);

/*
	Return size of queue
*/
size_t get_queue_size(queue_t q);

/*
	Return front of queue
*/
variant_t get_queue_front(queue_t q);

/*****************************************************************************************************************/
