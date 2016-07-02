#ifndef VERTEX_LINKED_LIST
#define VERTEX_LINKED_LIST

#include <iostream>
#include <stdlib.h>

using namespace std;

struct vertexNode
{
	int vertexName;
	vertexNode* prior;
	vertexNode* next;
};

class VertexLinkedQueue
{
private:
	vertexNode* vertices;
	int vertex_n;
	vertexNode* head_p;
	vertexNode* tail_p;
public:
	VertexLinkedQueue(int v_n)
	{
		vertex_n = v_n;
		try
		{
			vertices = new vertexNode[vertex_n + 2];
		}
		catch(std::bad_alloc& ba)
		{
			cout << "memory unavailable, when allocating space for vertices" << endl;
			cerr << "bad_alloc caught: " << ba.what() << endl;
		}
		vertexNode* p = vertices + 1;
		vertexNode* p_end = vertices + vertex_n;
		int v = 1;
		while(p <= p_end)
		{
			p->vertexName = v;
			p->prior = NULL;
			p->next = NULL;
			p++; v++;
		}
		try
		{
			head_p = new vertexNode;
		}
		catch(std::bad_alloc& ba)
		{
			cout << "memory unavailable, when allocating space for head node" << endl;
			cerr << "bad_alloc caught: " << ba.what() << endl;
		}
		try
		{
			tail_p = new vertexNode;
		}
		catch(std::bad_alloc& ba)
		{
			cout << "memory unavailable, when allocating space for tail node" << endl;
			cerr << "bad_alloc caught: " << ba.what() << endl;
		}
		head_p->vertexName = 0;
		head_p->prior = NULL;
		head_p->next = tail_p;
		tail_p->vertexName =0;
		tail_p->next = NULL;
		tail_p->prior = head_p;
	}
	~VertexLinkedQueue()
	{
		delete[] vertices;
		delete head_p;
		delete tail_p;
	}
	void clear()
	{
		vertexNode* p = vertices + 1;
		vertexNode* p_end = vertices + vertex_n;
		while(p <= p_end)
		{
			p->prior = NULL;
			p->next = NULL;
			p++;
		}
		head_p->prior = NULL;
		head_p->next = tail_p;
		tail_p->next = NULL;
		tail_p->prior = head_p;		
	}
	int get_head_v()
	{
		return head_p->next->vertexName;
	}
	void insertVertexNodeToQueue(int v)
	{
		vertexNode* vertex_p = vertices + v;
		vertexNode* p = tail_p->prior;
		p->next = vertex_p;
		vertex_p->prior = p;
		tail_p->prior = vertex_p;
		vertex_p->next = tail_p;
	}
	void deleteVertexNode(int v)
	{
		vertexNode* vertex_p = vertices + v;
		vertexNode* q = vertex_p->prior;
		vertexNode* r = vertex_p->next;
		q->next = r;
		r->prior = q;
	}
};
#endif
