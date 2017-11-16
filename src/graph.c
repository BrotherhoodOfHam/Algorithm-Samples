/*
	Graph source
*/

#include "graph.h"
#include "vector.h"

#include <assert.h>

/*****************************************************************************************************************/

typedef struct _graph_vtx
{
	vector_t edges;
	variant_t value;

} graph_vtx;

typedef struct _graph_impl
{
	vector_t vertices;

} graph_impl;

#define GIMPL(g) ((graph_impl*)g)
#define VIMPL(v) ((graph_vtx*)v)

/*****************************************************************************************************************/

graph_t init_graph()
{
	graph_impl* g = GIMPL(malloc(sizeof(graph_impl)));

	g->vertices = init_vector();

	return g;
}

void free_graph(graph_t g)
{
	assert(g != NULL);

	for (index_t i = 0; i < get_vector_size(GIMPL(g)->vertices); i++)
	{
		graph_vtx* vtx = VIMPL(get_vector_element(GIMPL(g)->vertices, i));
		
		free_vector(vtx->edges);

		if (vtx != NULL)
		{
			free(vtx);
		}
	}

	free_vector(GIMPL(g)->vertices);

	free(g);
}

graph_vtx_t add_graph_vertex(graph_t g, variant_t value)
{
	assert(g != NULL);
	
	graph_vtx* vtx = VIMPL(malloc(sizeof(graph_vtx)));
	vtx->edges = init_vector();
	vtx->value = value;
	add_vector_element(GIMPL(g)->vertices, D_CAST(vtx));

	return vtx;
}

void add_graph_edge(graph_vtx_t a, graph_vtx_t b)
{
	assert(a != NULL && b != NULL);
	assert(a != b);

	//Undirected edge
	add_vector_element(VIMPL(a)->edges, D_CAST(b));
	add_vector_element(VIMPL(b)->edges, D_CAST(a));
}

graph_vtx_t get_graph_edge(graph_vtx_t v, size_t i)
{
	assert(v != NULL);
	return (graph_vtx_t)(get_vector_element(VIMPL(v)->edges, i));
}

size_t get_graph_edge_count(graph_vtx_t v)
{
	assert(v != NULL);
	return get_vector_size(VIMPL(v)->edges);
}

variant_t get_graph_vertex_value(graph_vtx_t v)
{
	assert(v != NULL);
	return VIMPL(v)->value;
}

/*****************************************************************************************************************/
