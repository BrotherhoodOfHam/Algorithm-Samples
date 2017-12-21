/*
	Tree tester
*/

#include <stdio.h>
#include "tree.h"

static void print_tree(tree_node_t tree, uint32_t level)
{
	printf("%*d\n", level * 3, (uint32_t)get_node_value(tree));

	for (size_t i = 0; i < get_node_child_count(tree); i++)
	{
		print_tree(get_node_child(tree, i), level + 1);
	}
}

int test_tree()
{
	tree_node_t root = init_tree(0);

	tree_node_t n1 = add_node_child(root, 1);
	tree_node_t n2 = add_node_child(root, 1);
	tree_node_t n3 = add_node_child(root, 1);

	add_node_child(n1, 2);
	add_node_child(n1, 2);

	add_node_child(n3, 3);
	add_node_child(n3, 3);

	print_tree(root, 0);

	free_tree(root);

	return 0;
}
