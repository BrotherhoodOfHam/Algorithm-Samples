/*
	Tree implementation
*/

#include "tree.h"
#include "vector.h"

#include "assert.h"

/*****************************************************************************************************************/

typedef struct _impl_node
{
	variant_t value;
	vector_t children;

} impl_node;


#define IMPL(t) ((impl_node*)t)

impl_node* alloc_node(variant_t v)
{
	impl_node* node = malloc(sizeof(impl_node));
	node->children = init_vector();
	node->value = v;
	return node;
}

void free_node(impl_node* node)
{
	if (node != NULL)
	{
		for (index_t i = 0; i < get_vector_size(node->children); i++)
		{
			free_node((impl_node*)get_node_child((tree_node_t)node, i));
		}

		free_vector(node->children);

		free(node);
	}
}

/*****************************************************************************************************************/

tree_node_t init_tree(variant_t value)
{
	return (tree_node_t)alloc_node(value);
}

void free_tree(tree_node_t tree)
{
	free_node((impl_node*)tree);
}

/*****************************************************************************************************************/

bool is_node_leaf(tree_node_t node)
{
	assert(node != NULL);
	return is_vector_empty(IMPL(node)->children);
}

bool is_node_branch(tree_node_t node)
{
	return !is_node_leaf(node);
}

void set_node_value(tree_node_t node, variant_t value)
{
	assert(node != NULL);
	IMPL(node)->value = value;
}

variant_t get_node_value(tree_node_t node)
{
	assert(node != NULL);
	return IMPL(node)->value;
}

tree_node_t add_node_child(tree_node_t node, variant_t value)
{
	assert(node != NULL);
	tree_node_t c = (tree_node_t)alloc_node(value);
	add_vector_element(IMPL(node)->children, D_CAST(c));
	return c;
}

tree_node_t get_node_child(tree_node_t node, size_t n)
{
	assert(node != NULL);
	variant_t v = get_vector_element(IMPL(node)->children, n);
	return V_CAST(tree_node_t, v);
}

size_t get_node_child_count(tree_node_t node)
{
	assert(node != NULL);
	return get_vector_size(IMPL(node)->children);
}

void clear_node_children(tree_node_t n)
{
	impl_node* node = IMPL(n);

	for (index_t i = 0; i < get_node_child_count((tree_node_t)node); i++)
	{
		free_node((impl_node*)get_node_child((tree_node_t)node, i));
	}

	clear_vector(node->children);
}

/*****************************************************************************************************************/
