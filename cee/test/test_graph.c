/*
	Graph tester
*/

#include <stdio.h>
#include "graph.h"

void print_vertex(graph_vtx_t v)
{
	printf("%c: ", (char)get_graph_vertex_value(v));

	for (size_t i = 0; i < get_graph_edge_count(v); i++)
	{
		printf("%c, ", (char)get_graph_vertex_value(get_graph_edge(v, i)));
	}

	printf("\n");
}

int test_graph()
{
	graph_t g = init_graph();
	
	graph_vtx_t a = add_graph_vertex(g, 'a');
	graph_vtx_t b = add_graph_vertex(g, 'b');
	graph_vtx_t c = add_graph_vertex(g, 'c');
	graph_vtx_t d = add_graph_vertex(g, 'd');
	graph_vtx_t e = add_graph_vertex(g, 'e');
	graph_vtx_t f = add_graph_vertex(g, 'f');

	add_graph_edge(a, b);
	add_graph_edge(a, c);
	add_graph_edge(b, d);
	add_graph_edge(e, c);
	add_graph_edge(f, a);
	add_graph_edge(f, c);

	print_vertex(a);
	print_vertex(b);
	print_vertex(c);
	print_vertex(d);
	print_vertex(e);
	print_vertex(f);
	
	free_graph(g);
	
	return 0;
}
