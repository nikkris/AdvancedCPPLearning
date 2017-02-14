#include "linearlinkedlist.h"

node::node(int data)
{
	this->data = data;
	next = NULL;
}
node::~node()
{

}

node* linkedlist::gettop()
{
	return top;
}

int linkedlist::pushtop(int data)
{
	node* newnode = new node(data); 
	newnode->next = top; 
	top = newnode;
	if(tail == NULL)
		tail = top;
	return 0;
}

int linkedlist::pushtail(int data)
{
	node* newnode = new node(data); 
	tail->next = newnode; 
	tail = newnode;
	if(top ==NULL)
		top = tail;
	return 0;
}

int linkedlist::pushafter(node*prev, int data)
{
	if(prev == NULL)
		return -1;//prev cannot be NULL
	node* newnode = new node(data);
	newnode->next = prev->next;
	prev->next = newnode;
	return 0;
}

int linkedlist::pushafterpos(int loc, int data)
{
	node* curr_node = top;
	while(loc > 0)
	{
		loc--;
		if(curr_node->next == NULL)
		{
			return -1;//list is not large enough
		}
		curr_node = curr_node->next;
	}

	if(curr_node != NULL)
	{
		pushafter(curr_node,data);
		return 0;
	}
	return -1;
}

int linkedlist::deletetop()
{
	if(top == NULL)
		return -1;
	if(top->next == NULL)
		tail = NULL;
	node* temp = top;
	top = top->next;
	delete temp;
	return 0;
}

int linkedlist::deletetail()
{
	if(top == NULL)
		return -1;
	if(top->next == NULL)
	{
		delete tail;
		tail = NULL;
		top = NULL;
		return 0;
	}
	node* tail_prev = top;
	node* tail = top->next;
	node* tail_next = top->next->next;
	while (tail_next != NULL)
	{
		tail_prev = tail;
		tail = tail_next;
		tail_next = tail_next->next;
	}
	tail_prev->next = NULL;
	delete tail;
	return 0;
}

int linkedlist::deletekey(int key)
{
	node* iter_prev = NULL;
	node* iter = top;
	if(iter == NULL)
		return -1;
	node* iter_next = iter->next;
	if((iter->data == key)&&(iter_next == NULL))
	{
		delete iter;
		top  = NULL;
		tail = NULL;
		return 0;
	}
		
	while(iter!=NULL)
	{
		iter_next = iter->next;
		if(iter->data == key)
		{
			iter_prev->next = iter_next;
			delete iter;
			if(iter_next == NULL)
				tail = iter_prev;
			return 0;
		}
		iter_prev = iter;
		iter = iter_next;
	}
	return -1;

}

int linkedlist::deletepos(int loc)
{
	node* prev_node = NULL;
	node* curr_node = top;
	if(loc == 0)
	{
		if (curr_node == NULL)
			return -1;
		if(top == tail)
			tail = NULL;
		top = curr_node->next;
		delete curr_node;
		return 0;
	}

	while(loc > 0)
	{
		loc--;
		prev_node = curr_node;
		curr_node = curr_node->next;
		if(curr_node == NULL)
		{
			return -1;//list is not large enough
		}
	}

	if(curr_node != NULL)
	{
		prev_node->next = curr_node->next;
		delete curr_node;
		return 0;
	}
	return -1;
}

int linkedlist::length()
{
	/*
	int count = 0;
	node* iter = top;
	while(iter != NULL)
	{
		count++;
		iter = iter->next;
	}
	return count;
	*/

	return getcount(top);
}

int linkedlist::getcount(node* curr)
{
	if(curr == NULL)
		return 0;
	else
		return (1+getcount(curr->next));
}

int linkedlist::swap(int key1, int key2)
{
	if (key1 == key2) // no swap
		return -1;

	node* prev_key1 = NULL;
	node* prev_key2 = NULL;
	node* curr_key1 = NULL;
	node* curr_key2 = NULL;
	node* run_prev = top;
	node* run_curr = top->next;
	node* next_tmp = NULL;

	//find two points to swap
	if (top->data == key1)
	{
		prev_key1 = NULL;
		curr_key1 = top;
	}

	if (top->data == key2)
	{
		prev_key2 = NULL;
		curr_key2 = top;
	}
	while ((run_curr != NULL) && ((curr_key1 == NULL)||(curr_key2 == NULL)))
	{
		// assuming unique key
		if(run_curr->data == key1)
		{
			prev_key1 = run_prev;
			curr_key1 = run_curr;
		}
		else if(run_curr->data == key2)
		{
			prev_key2 = run_prev;
			curr_key2 = run_curr;
		}
		run_prev = run_curr;
		run_curr = run_curr->next;
	}

	if((curr_key1 == NULL)||(curr_key2 == NULL))
		return -1;// did not find both keys

	//swap
	if (prev_key1 == NULL)
	{
		top = curr_key2;
		prev_key2->next = curr_key1;
		
	}
	else if (prev_key2 == NULL)
	{
		top = curr_key1;
		prev_key1->next = curr_key2;
	}
	else
	{
		prev_key1->next = curr_key2;
		prev_key2->next = curr_key1;
	}
	next_tmp = curr_key1->next;
	curr_key1->next = curr_key2->next;
	curr_key2->next = next_tmp;

	if(curr_key1->next == NULL)
		tail = curr_key1;
	else if(curr_key2->next == NULL)
		tail = curr_key2;

	return 0;
}

int linkedlist::reverse()
{
	node* prev = NULL;
	node* curr = top;
	node* post = NULL;
	while (curr != NULL)
	{
		post = curr->next;
		curr->next = prev;
		prev = curr;
		curr = post;
		
	}
	tail = top;
	top = prev;

	return 0;
}

int linkedlist::sort()
{
	top = mergesort(top);
	tail = top;
	while(tail->next != NULL)
	{
		tail = tail->next;
	}
	return 0;
}

node* linkedlist::mergesort(node* start)	
{
	if(start->next != NULL)
	{
		node* middle = findmidpoint(start);
		node* sort1 = mergesort(start);
		node* sort2 = mergesort(middle);
		return merge(sort1,sort2);

	}
	else
	{
		return start;
	}
}

node* linkedlist::findmidpoint(node* speed1)		
{
	node* speed2 = speed1->next;
	while(speed2 != NULL)
	{
		speed2 = speed2->next;
		if(speed2 != NULL)
		{
			speed1 = speed1->next;
			speed2 = speed2->next;
		}
	}
	node* mid = speed1->next;
	speed1->next = NULL;
	return mid;
}

node* linkedlist::merge(node* s1,node* s2)
{
	node* curr;
	node* merge_top;
	if(s1 == NULL)
		return s2;
	else if(s2 == NULL)
		return s1;
	else
	{
		if((s1->data) < (s2->data))
		{
			merge_top = s1;
			s1 = s1->next;
			
		}
		else
		{
			merge_top = s2;
			s2 = s2->next;
		}
		curr = merge_top;
		while((s1!=NULL)&&(s2!=NULL))
		{
			if(s1->data < s2->data)
			{
				curr->next = s1;
				s1 = s1->next;
			}
			else
			{
				curr->next = s2;
				s2 = s2->next;
			}
			curr = curr->next;
		}
		if(s1 == NULL)
		{
			curr->next = s2;
		}
		else
		{
			curr->next = s1;
		}
		return merge_top;
	}
}


int linkedlist::display()
{
	node* curr = top;
	while(curr!=NULL)
	{
		printf("%d \n",curr->data);
		curr = curr->next;
	}
	return 0;
}