#include "graph.h"

/********************************adjacencyNode**********************************/
adjacencyNode::adjacencyNode(int src, int des, float edge)
{
	this->srce_id = src;
	this->dest_id = des;
	this->edge_wt = edge;
	this->next = NULL;
}

adjacencyNode::~adjacencyNode()				//destructor (default)
{

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
graphNode<T>::graphNode()
{
}

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

template<class T>
void graphNode<T>::setNullHeadNeighbor()		//Get head of neighbors 
{
	this->neighbors = NULL;
}

template<class T>
void graphNode<T>::setHeadNeighbor(adjacencyNode* head)	//Set head of neighbors 
{
	this->neighbors = head;
}

template <class T>
void graphNode<T>::InsertNeighbor(int src, int des, float wt)	//Insert a new neighbor at the head of neighbor
{
	adjacencyNode* newNeigh = new adjacencyNode(src, des, wt);
	newNeigh->next = this->neighbors;
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
	map <int, graphNode<int>>::iterator it;
	adjacencyNode* iter;
	adjacencyNode* temp;
	for (it = structure.begin(); it != structure.end(); it++)
	{
		iter = it->second.getHeadNeighbor();
		while (iter != NULL)
		{
			temp = iter;
			iter = iter->next;
			delete temp;
		}
	}
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
		return 0;
	}
	
	cout << endl << "One of the nodes is not found!";
	return -1;
}

int intGraph::deleteNode(int id)
{
	map <int, graphNode<int>>::iterator it;
	adjacencyNode* head;
	adjacencyNode* temp;
	adjacencyNode* prev;
	adjacencyNode* curr;
	adjacencyNode* tmp2;

	int dest_id;
	it = structure.find(id);
	head = it->second.getHeadNeighbor();
	it->second.setNullHeadNeighbor();
	while (head != NULL) // delete all links in this graphNode
	{
		temp = head;
		head = head->next;
		delete temp;
		
	}
	structure.erase(it);

	//remove all links with id as dest_id
	for (it = structure.begin(); it != structure.end(); it++)
	{
		prev = NULL;
		head = it->second.getHeadNeighbor();
		curr = head;
		while (curr != NULL && curr->get_dest_id() == id)
		{
			it->second.setHeadNeighbor(curr->next);
			temp = curr;
			curr = curr->next;
			delete temp;
		}
		it->second.setHeadNeighbor(curr);
		if(curr!= NULL)
		{
			prev = curr;
			curr = prev->next;
			while (curr != NULL)
			{
				if (curr->get_dest_id() == id)
				{
					temp = curr;
					curr = curr->next;
					prev->next = curr;
					delete temp;
				}
				else
				{
					prev = curr;
					curr = curr->next;		
				}
			}
		}
	}
	return 0;
}

int intGraph::deleteLink(int sr, int de)				// Delete a link given the srce and dest node ids
{
	map<int,graphNode<int>>::iterator iter = structure.find(sr);
	adjacencyNode* curr = iter->second.getHeadNeighbor();
	adjacencyNode* tmp2;
	adjacencyNode* prev;

	if (curr!=NULL && curr->get_dest_id() == de)
	{
		tmp2 = curr->next;
		delete curr;
		iter->second.setHeadNeighbor(tmp2);
	}
	else if(curr!=NULL)
	{
		prev = curr;
		curr = prev->next;
		while (curr != NULL)
		{
			if (curr->get_dest_id() == de)
			{
				tmp2 = curr->next;
				delete curr;
				prev->next = tmp2;
			}
			prev = prev->next;
			curr = prev->next;
		}
	}
	return 0;
}

int intGraph::displayAdj()						// Display the adjacency list of the graph
{
	adjacencyNode* iter;
	cout << endl << endl;
	for (auto it = structure.begin(); it != structure.end(); it++)
	{
		cout << endl << endl << "The edges and its weights for source node id = " << it->first;
		iter = it->second.getHeadNeighbor();
		
		while (iter != NULL)
		{
			cout << endl << "Source id = " << iter->get_srce_id();
			cout << endl << "Destination id = " << iter->get_dest_id();
			cout << endl << "Edge weight = " << iter->get_edge_wt()<<endl;
			iter = iter->next;
		}
	}
	return 0;
}

int intGraph::displayNodes()						// Display the nodes present in the graph
{
	cout << endl<<endl;
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
	gTest.insertLink(1, 2, 3.7);
	gTest.insertLink(1, 4, 7.6);
	gTest.insertLink(3, 4, 4.7);
	gTest.insertLink(7, 4, 5.5);
	gTest.insertLink(11, 4, 0.5);
	gTest.insertLink(8, 7, 5.3);
	gTest.insertLink(8, 2, 6.7);
	gTest.insertLink(7, 2, 4.2);
	gTest.insertLink(2, 7, 4.2);
	
	cout << endl << endl << "Original graph";
	gTest.displayAdj();
	
	cout << endl << endl << "Deleting 2 links";
	gTest.deleteLink(1, 4);
	gTest.deleteLink(5, 4);
	gTest.displayAdj();

	int n_id = 7;
	cout << endl << endl <<
		"After deleting node " << n_id;
	gTest.deleteNode(n_id);
	gTest.displayAdj();
}