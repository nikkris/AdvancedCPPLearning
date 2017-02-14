#pragma once

#include <map>
#include <iostream>
using namespace std;

// Represents the neighbors of 
class adjacencyNode
{
	int srce_id;					//source node (redundant information if used with graphNode)
	int dest_id;					//destination node
	float edge_wt;					//edge weight from base to this node;
	adjacencyNode* next;			//points to another neighbor of srce_id

public:

	adjacencyNode(int,int, float);	//constructor
	~adjacencyNode();				//destructor (default)
	int get_srce_id();				//source node need to be read only
	int get_dest_id();				//destination node need to be read only
	float get_edge_wt();				//getter for edge weight
	void set_edge_wt(float);		//setter for edge weight

};

template <class T>
class graphNode
{
	int node_id;							//Graph node identifier
	T data;									//Data of the node 
	adjacencyNode* neighbors;				//List of neighbors to the current node

public:
	graphNode(int);							//Constructor
	~graphNode();							//Destructor
	T getData();							//Get data
	void setData(T data);					//Set data
	adjacencyNode* getHeadNeighbor();		//Get head of neighbors 
	void InsertNeighbor(int, int, float);	//Insert a new neighbor at the head of neighbor
};

// undirected graph with data node begin of int type
class intGraph
{
	map <int, graphNode<int>> structure;
public:
	intGraph();								// Construct an empty graph
	intGraph(int);							// Construct a graph with V nodes
	~intGraph();							// Destrutor
	int createGraph(int);					// Create graph with V nodes
	int insertNode(int);					// Insert a vertex with given nodeId
	int insertLink(int, int, float);    // Insert an edge in the given vertex in the graph
	int deleteNode(int);					// Delete a node with given nodeId
	int displayAdj();						// Display the adjacency list of the graph
	int displayNodes();						// Display the nodes present in the graph
};

void graphDemo();