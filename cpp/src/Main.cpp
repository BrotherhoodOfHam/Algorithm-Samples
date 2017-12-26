
#include <iostream>
#include <string>

#include "graphs/Algorithms.h"

using namespace std;
using namespace ag;

//Print each vertex and it's adjacency list
template<typename GraphType>
void printGraph(const GraphType& g)
{
	for (auto vtx : g.getVertices())
	{
		cout << vtx->value() << ": ";

		for (auto edge : vtx->getEdges())
		{
			cout << edge->value() << ", ";
		}

		cout << "\n";
	}
}

template<typename GraphType>
void printGraphProperties(const GraphType& g)
{
	cout << "\n# Graph properties:";
	cout << boolalpha;
	cout << "\nIs connected => " << isConnected(g);
	cout << "\nIs strongly connected => " << isStronglyConnected(g);
	cout << "\nIs acyclic => " << isAcyclic(g);
	cout << "\n";
}

//Helper function
//Prints vector as comma separated list
template<typename Type>
void printVector(const std::vector<Type>& vec)
{
	//Head
	auto it = vec.begin();
	cout << *it;
	it++;

	//Tail
	while (it != vec.end())
	{
		cout << ", " << *it;
		it++;
	}

	cout << endl;
}

template<typename GraphType>
void printPath(const Path<GraphType>& path)
{
	using ValueType = typename Path<GraphType>::value_type;

	auto print_pair = [](ValueType value)
	{
		cout << "(" << value.first->value() << ", " << value.second->value() << ")";
	};

	//Head
	auto it = path.begin();
	print_pair(*it);
	it++;

	//Tail
	while (it != path.end())
	{
		cout << " -> ";
		print_pair(*it);
		it++;
	}

	cout << endl;
}

int main()
{
	/*
		Digraph g
		
		A-->B-->C   D
		|  ^|\  ^  ^  
		| / | \ | /   
		v/  v  v|/   
		E-->F   G   H

	*/
	Digraph<char> g;
	Digraph<char>::VertexRef vts[] = 
	{
		g.addVertex('A'),	//0: B, E
		g.addVertex('B'),	//1: C, F, G
		g.addVertex('C'),	//2: 
		g.addVertex('D'),	//3: 
		g.addVertex('E'),	//4: B, F
		g.addVertex('F'),	//5: 
		g.addVertex('G'),	//6: C, D
		g.addVertex('H')	//7:
	};

	//A
	vts[0]->addEdge(vts[1]);
	vts[0]->addEdge(vts[4]);
	//B
	vts[1]->addEdge(vts[2]);
	vts[1]->addEdge(vts[5]);
	vts[1]->addEdge(vts[6]);
	//E
	vts[4]->addEdge(vts[1]);
	vts[4]->addEdge(vts[5]);
	//G 
	vts[6]->addEdge(vts[2]);
	vts[6]->addEdge(vts[3]);

	cout << "# Graph g:\n";
	printGraph(g);
	printGraphProperties(g);

	cout << "\n# Topological sorting of g:\n";
	printVector(topologicalSort(g));

	cout << "\n# Shortest path A -> D in g:\n";
	printPath<Digraph<char>>(shortestPath(g, vts[0], vts[3]));

	cout << "\n# Transpose of g\n";
	printGraph(transpose(g));

	/*
		Graph j:

		A - B - C - D
		|   |   |   |
		E - F - G - H
		|   |   |   |
		I - J - K - L
	*/
	cout << "\n# Graph j:\n";

	Digraph<char> j;
	const size_t gridw = 4;             //Grid width
	const size_t gridc = gridw * gridw; //Grid cell count
	Digraph<char>::VertexRef gridvts[gridc];

	//1st pass
	//Allocate vertices
	for (size_t i = 0; i < gridc; i++)
	{
		gridvts[i] = j.addVertex('A' + (char)i);
	}

	//2nd pass
	//Link vertex edges
	for (size_t i = 0; i < gridc; i++)
	{
		const size_t ri = i + 1;     //Index of cell to the right
		const size_t rb = i + gridw; //Index of cell beneath

		//If indices in range
		//Add undirected edge

		if (ri < gridc)
		{
			gridvts[i]->addEdge(gridvts[ri]);
			gridvts[ri]->addEdge(gridvts[i]);
		}

		if (rb < gridc)
		{
			gridvts[i]->addEdge(gridvts[rb]);
			gridvts[rb]->addEdge(gridvts[i]);
		}
	}

	printGraph(j);
	printGraphProperties(j);

	cout << "\n# Shortest path from top-left -> bottom-right in j:\n";
	printPath<Digraph<char>>(shortestPath(j, gridvts[0], gridvts[gridc - 1]));

	/*
		Simple DAG

		A--->B
		|\  /|
		V vv V
		C--->D
	*/
	cout << "\n# DAG:\n";

	Digraph<char> d;

	auto dA = d.addVertex('A');
	auto dB = d.addVertex('B');
	auto dC = d.addVertex('C');
	auto dD = d.addVertex('D');

	dA->addEdge(dB);
	dA->addEdge(dC);
	dA->addEdge(dD);

	dB->addEdge(dC);
	dB->addEdge(dD);

	dC->addEdge(dD);

	printGraph(d);
	printGraphProperties(d);

	/*
		Simple cyclic graph

		A-->B
		^
		|
		v
		C<->D
	*/
	cout << "\n# Cyclic graph h:\n";

	Digraph<char> h;
	auto vA = h.addVertex('A');
	auto vB = h.addVertex('B');
	auto vC = h.addVertex('C');
	auto vD = h.addVertex('D');
	vA->addEdge(vB);
	vB->addEdge(vC);
	vC->addEdge(vA);
	vC->addEdge(vD);
	vD->addEdge(vC);

	printGraph(h);
	printGraphProperties(h);

	return 0;
}
