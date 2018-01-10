/*
	Binary Search Tree implementation
*/

#include "bst.h"
#include "assert.h"

/*****************************************************************************************************************
	Binary Tree implementation
******************************************************************************************************************/

/*
	Binary tree node
*/
typedef struct _bs_node
{
	variant_t value;
	struct _bs_node* parent;
	struct _bs_node* left;
	struct _bs_node* right;
} bs_node;

/*
	Binary tree structure
*/
typedef struct _bs_tree
{
	variant_comp_f comparator;
	bs_node* root;
} bs_tree;

#define IMPL(b) ((bs_tree*)b)

/*
	Binary tree functions
*/
static bs_node* alloc_node(variant_t value, bs_node* parent, bs_node* left, bs_node* right);
static void free_node(bs_node* node);

static bs_node* search_nodes(bs_node* node, variant_t value, variant_comp_f comparator);
static void swap_nodes(bs_node* a, bs_node* b);

static bs_node* max_node(bs_node* node);
static bs_node* min_node(bs_node* node);
static bs_node* next_node(bs_node* node);
static bs_node* pred_node(bs_node* node);

static void detach_node(bs_node* node);
static void transplant_node(bs_tree* tree, bs_node* child, bs_node* newchild);

/*****************************************************************************************************************/

bst_t init_bst(variant_comp_f comparator)
{
	bs_tree* tree = (bs_tree*)malloc(sizeof(bs_tree));
	tree->comparator = comparator;
	tree->root = NULL;

	return (bst_t)tree;
}

void free_bst(bst_t bst)
{
	free_node((bs_node*)IMPL(bst)->root);
	free(IMPL(bst));
}

/*****************************************************************************************************************/

void bst_insert(bst_t bst, variant_t value)
{
	bs_tree* tree = IMPL(bst);

	//If root is empty
	if (tree->root == NULL)
	{
		//Insert a new node straight away
		tree->root = alloc_node(value, NULL, NULL, NULL);
	}
	else
	{
		//Search nodes
		bs_node* node = tree->root;

		while (node != NULL)
		{
			//If new value less than current
			if (tree->comparator(value, node->value) <= 0)
			{
				//Go left
				if (node->left == NULL)
				{
					//Insert node at new position
					node->left = alloc_node(value, node, NULL, NULL);
					break;
				}

				node = node->left;
			}
			else
			{
				//Go right
				if (node->right == NULL)
				{
					//Insert node at new position
					node->right = alloc_node(value, node, NULL, NULL);
					break;
				}

				node = node->right;
			}
		}
	}
}

void bst_remove(bst_t bst, variant_t value)
{
	bs_tree* tree = IMPL(bst);

	//Find node to remove
	bs_node* found = search_nodes(tree->root, value, tree->comparator);

	//If value was found
	if (found != NULL)
	{
		/*
			3 cases for deletion of node:

			1. two children
			2. one child
			3. no children
		*/

		if (found->left == NULL)
		{
			transplant_node(tree, found, found->right);
		}
		else if (found->right == NULL)
		{
			transplant_node(tree, found, found->left);
		}
		else
		{
			bs_node* nxt = next_node(found->right);

			if (nxt->parent != found)
			{
				transplant_node(tree, nxt, nxt->right);
				nxt->right = found->right;
				nxt->right->parent = nxt;
			}

			transplant_node(tree, found, nxt);
			nxt->left = found->left;
			nxt->left->parent = nxt;
		}

		free_node(found);
	}

	//no-op
}

bool bst_contains(bst_t bst, variant_t value)
{
	bs_tree* tree = IMPL(bst);

	assert(tree != NULL);

	return search_nodes(tree->root, value, tree->comparator) != NULL;
}

variant_t bst_max(bst_t bst)
{
	return max_node(IMPL(bst)->root)->value;
}

variant_t bst_min(bst_t bst)
{
	return min_node(IMPL(bst)->root)->value;
}

/*****************************************************************************************************************/

bs_node* alloc_node(variant_t value, bs_node* parent, bs_node* left, bs_node* right)
{
	bs_node* node = malloc(sizeof(bs_node));
	node->value = value;
	node->parent = parent;
	node->left = left;
	node->right = right;
	return node;
}

void free_node(bs_node* node)
{
	if (node != NULL)
	{
		//Remove external references to this node
		detach_node(node);

		//recursively free the node and it's children
		free_node(node->left);
		free_node(node->right);
		//free actual memory
		free(node);
	}
}

//swaps node values
void swap_nodes(bs_node* a, bs_node* b)
{
	variant_t val = a->value;
	a->value = b->value;
	b->value = val;
}

//Get node with the maximum value in a given sub-tree
bs_node* max_node(bs_node* node)
{
	bs_node* max = NULL;
	bs_node* cur = node;

	while (cur != NULL)
	{
		max = cur;
		cur = cur->right;
	}

	return max;
}

//Get node with the minimum value in a given sub-tree
bs_node* min_node(bs_node* node)
{
	bs_node* min = NULL;
	bs_node* cur = node;

	while (cur != NULL)
	{
		min = cur;
		cur = cur->left;
	}

	return min;
}

//Get the successor to a given node
bs_node* next_node(bs_node* node)
{
	/*
		If node has a right sub-tree
		then the next node is smallest node in that sub-tree

		    A
		  /   \
		 ...   R
			  /
			 M

		next(A) = min(R) = M
	*/
	if (node->right != NULL)
	{
		return min_node(node->right);
	}

	//otherwise back-track up the tree

	bs_node* parent = node->parent;
	bs_node* cur = node;

	/*
               A
            /
         B
          \
           C
            \
             D

	     next(D) = A
	*/

	//While a parent node exists
	//and
	//The current node is the right node of that parent
	while ((parent != NULL) && (cur == parent->right))
	{
		cur = parent;
		parent = cur->parent;
	}

	return parent;
}

//Get the predecessor to a given node
bs_node* pred_node(bs_node* node)
{
	//similar to next_node()

	if (node->left != NULL)
	{
		return max_node(node->left);
	}

	//otherwise back-track up the tree

	bs_node* parent = node->parent;
	bs_node* cur = node;

	while ((parent != NULL) && (cur == parent->left))
	{
		cur = parent;
		parent = cur->parent;
	}

	return parent;
}

//Search a node's subtrees for a node with a given value
//Returns null if the value could not be found
bs_node* search_nodes(bs_node* node, variant_t value, variant_comp_f comparator)
{
	while (node != NULL)
	{
		if (comparator(value, node->value) == 0)
		{
			//value found
			return node;
		}
		else if (comparator(value, node->value) < 0)
		{
			//Go left
			node = node->left;
		}
		else
		{
			//Go right
			node = node->right;
		}
	}

	return NULL;
}

//Detaches a node and it's entire sub-tree from it's parent
void detach_node(bs_node* node)
{
	if (node != NULL)
	{
		bs_node* parent = node->parent;

		if (parent != NULL)
		{
			//If node is a left child
			if (parent->left == node)
			{
				parent->left = NULL;
			}
			//Or if node is a right child
			else if (parent->right == node)
			{
				parent->right = NULL;
			}
			else
			{
				//Otherwise if node isn't a child of it's parent
				//Do nothing
			}

			node->parent = NULL;
		}
	}
}

/*
	Makes newchild the child of child's parent

	child is left in a detached state
*/
void transplant_node(bs_tree* tree, bs_node* child, bs_node* newchild)
{
	detach_node(newchild);

	bs_node* parent = child->parent;

	//if child is root tree root
	if (parent == NULL)
	{
		tree->root = newchild;
	}
	else if (parent->left == child)
	{
		parent->left = newchild;
	}
	else if (parent->right == child)
	{
		parent->right = newchild;
	}

	if (newchild != NULL)
	{
		newchild->parent = child->parent;
	}

	child->parent = NULL;
}

/*****************************************************************************************************************/
