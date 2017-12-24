/*
	Digraph class

	Implementation of a directed graph using the Adjacency List representation
*/

#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <iterator>

namespace ag
{
	/*
		Digraph class
	*/
	template<typename Value_t>
	class Digraph
	{
	public:

		class Vertex;
		using EdgeList = std::vector<Vertex*>;

		/*
			Graph Vertex
		*/
		class Vertex
		{
		private:

			//Value
			Value_t m_value;
			//Adjacent vertices
			EdgeList m_edges;

		public:

			/*
				Default constructor
			*/
			Vertex() {}

			/*
				Construct vertex with given value
			*/
			Vertex(Value_t value) :
				m_value(value)
			{}

			/*
				Get vertex value
			*/
			const Value_t& value() const { return m_value; }
			Value_t& value() { return m_value; }

			/*
				Set vertex value
			*/
			void setValue(Value_t value) { m_value = std::move(value); }

			/*
				Get edge list
			*/
			const EdgeList& getEdges() const { return m_edges; }

			/*
				Add an edge between two vertices
			*/
			void addEdge(Vertex* vtx)
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
		Vertex* createVertex(Value_t val)
		{
			m_vertices.emplace_back(new Vertex(val));
			return m_vertices.back().get();
		}

		/*
			Get a vertex pointer by index in the graph's vertex list
			Nullptr if index is out of range
		*/
		Vertex* getVertex(size_t idx) const
		{
			if (idx < m_vertices.size())
			{
				return m_vertices.at(idx).get();
			}

			return nullptr;
		}

		/*
			Return list of all vertices in graph
		*/
		std::vector<Vertex*> getVertices() const
		{
			using namespace std;
			vector<Vertex*> vtxs;
			vtxs.reserve(m_vertices.size());

			//Map unique_ptrs to raw ptrs
			transform(
				m_vertices.begin(),
				m_vertices.end(),
				back_inserter(vtxs),
				[](const unique_ptr<Vertex>& v)->Vertex*{ return v.get(); }
			);

			return move(vtxs);
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
		std::vector<std::unique_ptr<Vertex>> m_vertices;
	};


}

