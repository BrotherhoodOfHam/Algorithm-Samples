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
		typename ValueType,
		template<typename T> class Graph_t
	>
	std::vector<ValueType> topologicalSort(const Graph_t<ValueType>& g)
	{
		using namespace std;

		vector<ValueType> values;
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
	template<typename GraphType>
	bool isAcyclic(const GraphType& g)
	{
		//Construct depth first forest
		SpanningTree<GraphType> span = depthFirstSearch(g);

		using Vtx_t = typename GraphType::VertexRef;

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
	template<typename GraphType>
	using Path = std::vector<std::pair<typename GraphType::VertexRef, typename GraphType::VertexRef>>;

	/*
		Compute the shortest Path between two vertices in a given graph
	*/
	template<typename GraphType>
	Path<GraphType> shortestPath(
		const GraphType& g,
		typename GraphType::VertexRef a,
		typename GraphType::VertexRef b
	)
	{
		using namespace std;

		Path<GraphType> path;

		//Compute bfs spanning tree
		SpanningTree<GraphType> span = breadthFirstSearch(g, a);

		//If vertex b is reachable from a
		if (span.find(b) != span.end())
		{
			//Current vertex
			typename GraphType::VertexRef cur = b;

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
	template<typename GraphType>
	GraphType transpose(const GraphType& graph)
	{
		using namespace std;

		using VtxType = typename GraphType::VertexRef;

		unordered_map<VtxType, VtxType> vertexMap;

		//Resulting transposed graph
		GraphType tgraph;

		//Preallocate new vertices in transposed graph
		for (VtxType vtx : graph.getVertices())
		{
			//Map old vertex -> transposed vertex
			vertexMap.insert(make_pair(vtx, tgraph.addVertex(vtx->value())));
		}

		//For each vertex pair
		for (auto pair : vertexMap)
		{
			VtxType old = pair.first;
			VtxType cur = pair.second;

			//For each edge in old vertex
			for (VtxType edge : old->getEdges())
			{
				vertexMap[edge]->addEdge(cur);
			}
		}

		return tgraph;
	}

	/*
		Checks if all vertices are reachable from some vertex
	*/
	template<typename GraphType>
	bool isConnected(const GraphType& g)
	{
		using Vtx_t = typename GraphType::VertexRef;

		//Get any vertex
		Vtx_t start = g.getVertices()[0];

		//Compute spanning tree
		SpanningTree<GraphType> span = breadthFirstSearch(g, start);

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
	template<typename GraphType>
	bool isStronglyConnected(const GraphType& g)
	{
		return isConnected(g) && isConnected(transpose(g));
	}
}
