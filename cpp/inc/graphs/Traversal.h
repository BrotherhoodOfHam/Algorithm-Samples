/*
	Graph Traversal Algorithms

	Implements Depth-First-Search and Breadth-First-Search generically.
*/

#pragma once

#include <functional>
#include <unordered_map>
#include <stack>
#include <queue>

#include "Digraph.h"

namespace ag
{
	//Visitor delegate
	template<typename GraphType>
	using GraphVisitor = std::function<void(typename GraphType::VertexRef)>;

	//Spanning tree - maps a vertex to it's parent
	template<typename GraphType>
	using SpanningTree = std::unordered_map<typename GraphType::VertexRef, typename GraphType::VertexRef>;

	namespace details
	{
		template<typename GraphType>
		using Stack = std::stack<typename GraphType::VertexRef>;

		template<typename GraphType>
		using Queue = std::queue<typename GraphType::VertexRef>;
	}

	/*
		BFS graph traversal.

		The adjancent vertices are discovered first.

		Returns a breadth-first spanning tree.
	*/
	template<typename GraphType>
	SpanningTree<GraphType> breadthFirstSearch(
		const GraphType& graph,
		typename GraphType::VertexRef start,
		GraphVisitor<GraphType> visitor = [](auto) {}
	)
	{
		using namespace std;

		//Spanning tree of graph
		SpanningTree<GraphType> span;
		//Vertex queue - stores adjacent vertices
		details::Queue<GraphType> q;

		//Initialize spanning tree to null
		for (auto vtx : graph.getVertices())
		{
			//Set each vertex as undiscovered
			span[vtx] = nullptr;
		}

		q.push(start);

		while (!q.empty())
		{
			//Fetch next vertex
			auto u = q.front();
			q.pop();

			//For each adjacent vertex v
			for (auto v : u->getEdges())
			{
				//If v is undiscovered
				if (span[v] == nullptr)
				{
					span[v] = u;
					q.push(v);
				}
			}

			//Visit vertex
			visitor(u);
		}

		return span;
	}

	/*
		Depth first search a given vertex
	*/
	template<typename GraphType>
	void depthFirstSearch(
		typename GraphType::VertexRef vertex,
		SpanningTree<GraphType>& span,
		GraphVisitor<GraphType> visitor
	)
	{
		//vertex discovered

		for (auto edge : vertex->getEdges())
		{
			//If edge is undiscovered
			if (span[edge] == nullptr)
			{
				//Set parent vertex of edge
				span[edge] = vertex;
				//Search edge recursively
				depthFirstSearch<GraphType>(edge, span, visitor);
			}
		}

		//visit current vertex
		visitor(vertex);

		//vertex finished
	}

	/*
		DFS graph traversal

		The furthest vertices of the graph are discovered first

		Returns a depth-first spanning forest
	*/
	template<typename GraphType>
	SpanningTree<GraphType> depthFirstSearch(
		const GraphType& graph,
		GraphVisitor<GraphType> visitor = [](auto){}
	)
	{
		using namespace std;

		//Spanning tree of graph
		SpanningTree<GraphType> span;

		auto vertexList = graph.getVertices();

		//Initialize precedence map
		for (auto u : vertexList)
		{
			//Set each vertex as undiscovered
			span[u] = nullptr;
		}

		//For each undiscovered vertex
		for (auto u : vertexList)
		{
			if (span[u] == nullptr)
			{
				//Visit recursively
				depthFirstSearch<GraphType>(u, span, visitor);
			}
		}

		return span;
	}
}
