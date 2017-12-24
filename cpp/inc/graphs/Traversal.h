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
	template<typename Graph_t>
	using GraphVisitor = std::function<void(typename Graph_t::Vertex*)>;

	//Spanning tree - maps a vertex to it's parent
	template<typename Graph_t>
	using SpanningTree = std::unordered_map<typename Graph_t::Vertex*, typename Graph_t::Vertex*>;

	namespace details
	{
		template<typename Graph_t>
		using Stack = std::stack<typename Graph_t::Vertex*>;

		template<typename Graph_t>
		using Queue = std::queue<typename Graph_t::Vertex*>;
	}

	/*
		BFS graph traversal.

		The adjancent vertices are discovered first.

		Returns a breadth-first spanning tree.
	*/
	template<typename Graph_t>
	SpanningTree<Graph_t> breadthFirstSearch(
		const Graph_t& graph,
		typename Graph_t::Vertex* start,
		GraphVisitor<Graph_t> visitor = [](auto) {}
	)
	{
		using namespace std;

		//Spanning tree of graph
		SpanningTree<Graph_t> span;
		//Vertex queue - stores adjacent vertices
		details::Queue<Graph_t> q;

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
	template<typename Graph_t>
	void depthFirstSearch(
		typename Graph_t::Vertex* vertex,
		SpanningTree<Graph_t>& span,
		GraphVisitor<Graph_t> visitor
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
				depthFirstSearch<Graph_t>(edge, span, visitor);
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
	template<typename Graph_t>
	SpanningTree<Graph_t> depthFirstSearch(
		const Graph_t& graph,
		GraphVisitor<Graph_t> visitor = [](auto){}
	)
	{
		using namespace std;

		//Spanning tree of graph
		SpanningTree<Graph_t> span;

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
				depthFirstSearch<Graph_t>(u, span, visitor);
			}
		}

		return span;
	}
}
