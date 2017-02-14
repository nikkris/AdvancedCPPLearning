#ifndef LLL
#define LLL

/*

author: Nikhil Krishnan



*/


#include <stdio.h>

class node
{
	
private:
	int data;
	node* next;		//

	node(int);		//constructor
	~node();

	friend class linkedlist;
};

class linkedlist
{
	//linear singly linked list
private:
	// here a double pointer is not necessary
	// as we are not passing the top or tail as parameters to an outside function
	node* top; 
	node* tail;
public:
	linkedlist(): top(NULL), tail(NULL)
	{

	}
	~linkedlist()
	{
		printf("%s \n", "destructor");
		node* next = NULL;
		while(top!=NULL)
		{
			next = top->next;
			delete top;
			top = next;
		}
	}
	node* gettop();				// get top pointer
	int pushtop(int);			// push new node to start of linked list
	int pushtail(int);			// push new node to end of linked list
	int pushafter(node*, int);	//insert new node after the given node
	int pushafterpos(int, int);	//insert new node after given location
	int deletetop();			// delete top pointer
	int deletetail();			// delete last entry
	int deletekey(int);			// delete given key
	int deletepos(int);			// delete node at given position
	int length();				// find length of linkedlist
	int getcount(node*);		// find length of linkedlist from the given position
	int swap(int, int);			// swap two elements identified by keys given
	int sort();					// sort elements in the linear linkedlist
	node* mergesort(node*);		// sort the linkedlist 
	node* findmidpoint(node*);	// returns the middle pointer of a linear linked list
	node* merge(node*,node*);	// merge two sorted linked list
	int reverse();
	
	int display();				// prints out all the elements in the linked list
	};

#endif