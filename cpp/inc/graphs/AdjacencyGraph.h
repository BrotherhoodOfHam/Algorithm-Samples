/*
	Graph class

	Implementation of a directed graph using the Adjacency List representation
*/

#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include "../util/Range.h"

namespace ag
{
	/*
		AdjacencyGraph class
	*/
	template<typename ValueType>
	class AdjacencyGraph
	{
	public:

		class VertexImpl;

		using VertexRef = VertexImpl*;
		using VertexList = std::vector<VertexRef>;
		using EdgeList = std::vector<VertexRef>;

		/*
			Graph Vertex
		*/
		class VertexImpl
		{
		private:

			//Value
			ValueType m_value;
			//Adjacent vertices
			EdgeList m_edges;

		public:

			/*
				Default constructor
			*/
			VertexImpl() {}

			/*
				Construct vertex with given value
			*/
			VertexImpl(ValueType value) :
				m_value(value)
			{}

			/*
				Get vertex value
			*/
			const ValueType& value() const { return m_value; }
			ValueType& value() { return m_value; }

			/*
				Set vertex value
			*/
			void setValue(ValueType value) { m_value = std::move(value); }

			/*
				Get edge list
			*/
			const EdgeList& getEdges() const { return m_edges; }

			/*
				Add an edge between two vertices
			*/
			void addEdge(VertexRef vtx)
			{
				using namespace std;
				
				//If edge doesn't already exist
				if (find(m_edges.begin(), m_edges.end(), vtx) == m_edges.end())
				{
					//Create a new edge
					m_edges.push_back(vtx);
				}
			}
		};

		/*
			Create a new vertex in the graph
			And initialize it to a given value.
		*/
		VertexRef addVertex(ValueType val)
		{
			m_vertices.emplace_back(new VertexImpl(val));
			return m_vertices.back().get();
		}

		//Owning list of vertex pointers
		using VertexPool = std::vector<std::unique_ptr<VertexImpl>>;

		/*
			Vertex adapter iterator
		*/
		class Iterator : public VertexPool::const_iterator
		{
		public:

			using Base = typename VertexPool::const_iterator;

			using pointer = VertexRef;
			using reference = VertexRef;

			Iterator(const Base& base) : Base(base) {}

			//Operators
			reference operator*() { return get(); }
			pointer operator->() { return get(); }
			Iterator operator+(size_t diff) { return (Base::operator+(diff)); }

		private:

			reference get() { return (Base::operator*()).get(); }
		};

		/*
			Return list of all vertices in graph
		*/
		Range<Iterator> getVertices() const
		{
			return Range<Iterator>(m_vertices.cbegin(), m_vertices.cend());
		}

		/*
			Returns number of vertices in graph
		*/
		size_t getVertexCount() const
		{
			return m_vertices.size();
		}

		/*
			Returns total number of edges in graph
		*/
		size_t getEdgeCount() const
		{
			size_t e = 0;

			for (const auto& vtx : m_vertices)
			{
				e += vtx->m_edges.size();
			}

			return e;
		}

	private:

		//vertex list
		VertexPool m_vertices;
	};


}

