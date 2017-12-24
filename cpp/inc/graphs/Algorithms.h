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
		auto span = depthFirstSearch(g, [&](auto vtx){
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
		//Construct depth first forest
		SpanningTree<Graph_t> span = depthFirstSearch(g);

		using Vtx_t = typename Graph_t::Vertex*;

		//Foreach vertex
		for (Vtx_t vtx : g.getVertices())
		{
			Vtx_t cur = vtx;

			//Detect back edges in the spanning tree
			do
			{
				cur = span[cur];

				if (cur == vtx)
				{
					return false;
				}

			} while (cur != nullptr);
		}

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
		SpanningTree<Graph_t> span = breadthFirstSearch(g, a);

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


	/*
		Return a graph where all edge directions are reversed
	*/
	template<typename Graph_t>
	Graph_t transpose(const Graph_t& graph)
	{
		using namespace std;

		using Vtx_t = typename Graph_t::Vertex*;

		unordered_map<Vtx_t, Vtx_t> vertexMap;

		//Resulting transposed graph
		Graph_t tgraph;

		//Preallocate new vertices in transposed graph
		for (Vtx_t vtx : graph.getVertices())
		{
			//Map old vertex -> transposed vertex
			vertexMap.insert(make_pair(vtx, tgraph.createVertex(vtx->value())));
		}

		//For each vertex pair
		for (auto pair : vertexMap)
		{
			Vtx_t old = pair.first;
			Vtx_t cur = pair.second;

			//For each edge in old vertex
			for (Vtx_t edge : old->getEdges())
			{
				vertexMap[edge]->addEdge(cur);
			}
		}

		return tgraph;
	}

	/*
		Checks if all vertices are reachable from some vertex
	*/
	template<typename Graph_t>
	bool isConnected(const Graph_t& g)
	{
		using Vtx_t = typename Graph_t::Vertex*;

		//Get any vertex
		Vtx_t start = g.getVertex(0);

		//Compute spanning tree
		SpanningTree<Graph_t> span = breadthFirstSearch(g, start);

		//The graph is connected if all vertices are reachable from start
		for (Vtx_t vtx : g.getVertices())
		{
			Vtx_t parent = span[vtx];

			//If vertex in spanning tree has no parent and isn't the start vertex
			if (parent == nullptr && parent != start)
			{
				//It is not reachable from the start vertex
				return false;
			}
		}

		return true;
	}

	/*
		Checks if a graph is strongly connected
	*/
	template<typename Graph_t>
	bool isStronglyConnected(const Graph_t& g)
	{
		return isConnected(g) && isConnected(transpose(g));
	}
}
