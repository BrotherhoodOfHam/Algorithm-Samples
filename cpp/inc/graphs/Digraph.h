/*
	Digraph class

	Implementation of a directed graph using the Adjacency List representation
*/

#pragma once

#include <vector>
#include <memory>
#include <algorithm>

namespace ag
{
	/*
		Digraph class
	*/
	template<typename ValueType>
	class Digraph
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

		/*
			Get a vertex pointer by index in the graph's vertex list
			Nullptr if index is out of range
		*/
		VertexRef getVertex(size_t idx) const
		{
			if (idx < m_vertices.size())
			{
				return m_vertices.at(idx).get();
			}

			return nullptr;
		}

		//Owning list of vertex pointers
		using VertexPool = std::vector<std::unique_ptr<VertexImpl>>;

		/*
			Vertex iterator
		*/
		class Iterator : public VertexPool::const_iterator
		{
		public:

			using Base = typename VertexPool::const_iterator;

			using pointer = VertexRef;
			using reference = VertexRef;

			Iterator(const Base& base) : Base(base) {}

			reference operator*() const { return (Base::operator*()).get(); }
			pointer const operator->() const { return (Base::operator*()).get(); }
		};

		/*
			Range helper class
		*/
		class VertexRange
		{
		private:

			Iterator m_begin;
			Iterator m_end;

		public:

			VertexRange(const VertexPool& pool) :
				m_begin(pool.cbegin()),
				m_end(pool.cend())
			{}

			Iterator begin() const { return m_begin; }
			Iterator end() const { return m_end; }
		};

		/*
			Return list of all vertices in graph
		*/
		VertexRange getVertices() const
		{
			return VertexRange(m_vertices);
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

