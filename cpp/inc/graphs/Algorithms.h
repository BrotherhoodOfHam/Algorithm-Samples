/*
	Common graph algorithms
*/

#pragma once

#include <vector>
#include <stack>
#include "Traversal.h"

namespace ag
{
	/*
		Returns a partial order of vertices.

		Such that for every edge (u,v): u appears before v in the list.
	*/
	template<
		typename Value_t,
		template<typename T> class Graph_t
	>
	std::vector<Value_t> topologicalSort(const Graph_t<Value_t>& g)
	{
		using namespace std;

		vector<Value_t> values;
		values.reserve(g.getVertexCount());

		//The order that the vertices are discovered is the topological sorting
		depthFirstSearch(g, [&](auto vtx){
			values.push_back(vtx->value());
		});

		//reverse(values.begin(), values.end());

		return move(values);
	}

	/*
		Checks if a given graph doesn't contain cycles
	*/
	template<typename Graph_t>
	bool isAcyclic(const Graph_t& g)
	{
		auto sort = topologicalSort(g);
		//todo: implement
		return true;
	}

	/*
		Path through a graph

		Represented by a list of pairs of vertices
	*/
	template<typename Graph_t>
	using Path = std::vector<std::pair<typename Graph_t::Vertex*, typename Graph_t::Vertex*>>;

	/*
		Compute the shortest Path between two vertices in a given graph
	*/
	template<typename Graph_t>
	Path<Graph_t> shortestPath(
		const Graph_t& g,
		typename Graph_t::Vertex* a,
		typename Graph_t::Vertex* b
	)
	{
		using namespace std;

		Path<Graph_t> path;

		//Compute bfs spanning tree
		SpanningTree<Graph_t> span = breadthFirstSearch(g, a, [](auto){});

		//If vertex b is reachable from a
		if (span.find(b) != span.end())
		{
			//Current vertex
			typename Graph_t::Vertex* cur = b;

			while (cur != a)
			{
				auto parent = span[cur];
				//Append to path
				path.push_back(make_pair(parent, cur));
				//Set next vertex
				cur = parent;
			}

			reverse(path.begin(), path.end());
		}

		return move(path);
	}
}
