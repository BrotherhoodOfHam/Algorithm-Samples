
#include <iostream>
#include <string>

#include "graphs/Algorithms.h"

using namespace std;
using namespace ag;

//Helper function
//Prints vector as comma separated list
template<typename Type>
void print_vector(const std::vector<Type>& vec)
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

template<typename Graph_t>
void print_path(const Path<Graph_t>& path)
{
	using Value_t = typename Path<Graph_t>::value_type;

	auto print_pair = [](Value_t value)
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
	Digraph<char>::Vertex* vts[] = 
	{
		g.createVertex('A'),	//0: B, E
		g.createVertex('B'),	//1: C, F, G
		g.createVertex('C'),	//2: 
		g.createVertex('D'),	//3: 
		g.createVertex('E'),	//4: B, F
		g.createVertex('F'),	//5: 
		g.createVertex('G'),	//6: C, D
		g.createVertex('H')		//7:
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

	cout << "Topological sorting of g:\n";
	print_vector(topologicalSort(g));

	cout << "Shortest path A -> D:\n";
	print_path<Digraph<char>>(shortestPath<Digraph<char>>(g, vts[0], vts[3]));

	Digraph<char> h;
	auto vA = h.createVertex('A');
	auto vB = h.createVertex('B');
	auto vC = h.createVertex('C');
	auto vD = h.createVertex('D');
	vA->addEdge(vB);
	vB->addEdge(vC);
	vC->addEdge(vA);
	vC->addEdge(vD);
	vD->addEdge(vC);
	//cout << boolalpha << isAcyclic(h) << endl;

	return 0;
}
