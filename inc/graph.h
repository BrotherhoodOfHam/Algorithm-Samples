/*
	Graph:

	Basic graph implementation,
	
	- Undirected
	- Uses adjancency list representation
	- Edges aren't weighted
	- Vertices hold values
	- Disallows self loops
*/

#pragma once

#include "variant.h"

/*****************************************************************************************************************/

typedef struct { int x; } *graph_t;
typedef struct { int x; } *graph_vtx_t;

/*
	Create an empty graph
*/
graph_t init_graph();

/*
	Deallocate an empty graph
*/
void free_graph(graph_t g);

/*
	Create a vertex with a given value
*/
graph_vtx_t add_graph_vertex(graph_t g, variant_t value);

/*
	Add a undirected edge between two vertices

	a <-> b
*/
void add_graph_edge(graph_vtx_t a, graph_vtx_t b);

/*
	Get edge from v
*/
graph_vtx_t get_graph_edge(graph_vtx_t v, size_t i);

/*
	Get number of edges from v
*/
size_t get_graph_edge_count(graph_vtx_t v);

/*
	Get vertex value
*/
variant_t get_graph_vertex_value(graph_vtx_t v);

/*****************************************************************************************************************/
