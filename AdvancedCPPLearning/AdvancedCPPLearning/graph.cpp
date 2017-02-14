#include "graph.h"

/********************************adjacencyNode**********************************/
adjacencyNode::adjacencyNode(int src, int des, float edge)
{
	this->srce_id = src;
	this->dest_id = des;
	this->edge_wt = edge;
	this->next = NULL;
}

int adjacencyNode::get_srce_id()				//source node need to be read only
{
	return srce_id;
}

int adjacencyNode::get_dest_id()				//destination node need to be read only
{
	return dest_id;
}

float adjacencyNode::get_edge_wt()				//getter for edge weight
{
	return edge_wt;
}

void adjacencyNode::set_edge_wt(float wt)				//setter for edge weight
{
	this->edge_wt = wt;
}

/*******************************graphNode****************************************/
template<class T>
graphNode<T>::graphNode(int id)
{
	this->node_id = id;
	this->data = NULL;
	this->neighbors = NULL;
}

template<class T>
graphNode<T>::~graphNode()							//Destructor
{

}

template<class T>
T graphNode<T>::getData()
{
	return this->data;
}

template<class T>
void graphNode<T>::setData(T data)
{
	this->data = data;
}

template<class T>
adjacencyNode* graphNode<T>::getHeadNeighbor()		//Get head of neighbors 
{
	return this->neighbors;
}

template <class T>
void graphNode<T>::InsertNeighbor(int src, int des, float wt)	//Insert a new neighbor at the head of neighbor
{
	adjacencyNode* newNeigh = new adjacencyNode(src, des, wt);
	adjacencyNode* newNeigh->next = this->neighbors;
	this->neighbors = newNeigh;
}

/*********************************intGraph***************************************/
intGraph::intGraph(	)								// Construct an empty graph
{

}

intGraph::intGraph(int nNodes)						// Construct a graph with V nodes
{
	createGraph(nNodes);
}

intGraph::~intGraph()								// Destrutor
{
	cout << endl << "Destructor called";
	structure.clear();
}

int intGraph::createGraph(int V)					// Create graph with V nodes
{
	if (this->structure.empty())
	{
		for (int i = 0; i < V; i++)
		{
			insertNode(i);	
		}
	}
	return 0;
}

int intGraph::insertNode(int id)					// Insert a vertex with given nodeId
{
	if (structure.find(id)==structure.end())
	{
		graphNode<int> curr(id);
		structure.insert(pair <int, graphNode<int>>(id, curr));
		//structure.insert(pair <int, graphNode<int>> (i, graphNode<int> (i))); // this works as well
	}
	else
	{
		cout << endl << "Node already exist.";
	}
	return 0;
}

int intGraph::insertLink(int src, int des, float wt)		// Insert a new vertex in the graph
{
	//This function allows inserting multiple links between the same source destionation pairs
	//Be careful about insertion
	
	if ((structure.find(src) != structure.end()) && (structure.find(des) != structure.end()))
	{
		structure[src].InsertNeighbor(src, des, wt);
	}
	cout << endl << "One of the nodes is not found!";
	
	return -1;
}

int intGraph::deleteNode(int)
{

	return 0;
}

int intGraph::displayNodes()						// Display the nodes present in the graph
{
	for (auto it = structure.begin(); it != structure.end(); it++)
	{
		cout << endl << it->first;
	}
	return 0;
}


/*********************************graphDemo***************************************/

void graphDemo()
{
	intGraph gTest(10);
	gTest.displayNodes();
	gTest.insertNode(7);
	gTest.displayNodes();
}