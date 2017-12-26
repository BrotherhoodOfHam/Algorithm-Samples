/*
	Graph class

	Implementation of a graph using the matrix representation
*/

#pragma once

namespace ag
{
	template<typename ValueType>
	class MatrixGraph
	{
	private:

		/*
			Edges are stored in a |V|x|V| matrix

			where |V| is number of vertices in the graph
		*/
		std::vector<bool> m_matrix;
		std::vector<ValueType> m_values;

	public:

		//using VertexRef = size_t;
		//using VertexList = ;
		//using EdgeList = ;

		class VertexIterator
		{
			
		};

		class EdgeIterator
		{

		};

		/*
			Create a matrix graph with a given vertex count
		*/
		MatrixGraph(size_t vertexCount)
		{

		}

		size_t getVertexCount() const
		{
			return m_values.size();
		}

		size_t getEdgeCount() const
		{
			return -1;
		}
	};
}
