/*
	Tree implementation

	Using linked representation
*/

#pragma once

#include "common.h"
#include "variant.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/*****************************************************************************************************************/

typedef struct { int x; } *tree_node_t;

/*
	Allocate a tree with one root node
*/
tree_node_t init_tree(variant_t rootvalue);

/*
	Free a tree and all it's nodes
*/
void free_tree(tree_node_t tree);

/*****************************************************************************************************************
	Node operations:
/*****************************************************************************************************************/

/*
	Does a node not have any children
*/
bool is_node_leaf(tree_node_t node);

/*
	Does a node have at least one child
*/
bool is_node_branch(tree_node_t node);


/*
	Set a given node's value
*/
void set_node_value(tree_node_t node, variant_t value);

/*
	Get a given node's value
*/
variant_t get_node_value(tree_node_t node);


/*
	Create a child node and initialize it to a given value
*/
tree_node_t add_node_child(tree_node_t node, variant_t value);

/*
	Get a child of a given node at a specified index
*/
tree_node_t get_node_child(tree_node_t node, size_t n);

/*
	Get numbe of child nodes of a given node
*/
size_t get_node_child_count(tree_node_t node);


/*
	Free all child nodes of a given node
*/
void clear_node_children(tree_node_t node);

/*****************************************************************************************************************/