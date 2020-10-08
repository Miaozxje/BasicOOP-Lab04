#include <iostream>
#include <string>
#include <string>
#include <cmath>
#include <bitset>
using namespace std;
struct Node
{
	int info;
	Node* pNext;
};
class LinkedList
{
private:
	Node* pHead, * pTail;
public:
	LinkedList() 
	{
		pHead = NULL;
		pTail = NULL;
	}
	Node* CreateNode(const int& n)
	{
		Node* p = new Node();
		if (p == NULL)
		{
			cout << "Don't have enough memory";
			return NULL;
		}
		p->info = n;
		p->pNext = NULL;
		return p;
	}
	Node* AddHead(const int& n)
	{
		Node* p = CreateNode(n);
		if (pHead == NULL)
		{
			pHead = p;
			pTail = p;
			return pHead;
		}
		p->pNext = pHead;
		pHead = p;
		return pHead;
	}
	Node* AddTail(const int& n)
	{
		Node* p;
		if (pHead == NULL)
		{
			pHead = CreateNode(n);
			return pHead;
		}
		p = pHead;
		while (p->pNext != NULL)
			p = p->pNext;
		p->pNext = CreateNode(n);
		pTail = p->pNext;
		return pTail;
	};
	Node* RemoveHead()
	{
		Node* p = pHead;
		if (pHead == NULL)
			return NULL;
		pHead = pHead->pNext;
		delete p;
		return NULL;
	}
	Node* RemoveTail()
	{
		Node* pre;
		if (pHead == NULL)
			return NULL;
		Node* p;
		p = pre = pHead;
		while (p->pNext != NULL)
		{
			pre = p;
			p = p->pNext;
		}
		delete p;
		pre->pNext = NULL;
		pTail = pre;
		return NULL;
	}
	friend ostream& operator<<(ostream& os, const LinkedList& P)
	{
		if (P.pHead == NULL)
		{
			os << "";
			return os;
		}
		Node* p;
		for (p = P.pHead; p != NULL; p = p->pNext)
			os << p->info << "\t";
		return os;
	}
	int& operator[](const int& pos)
	{
		if (pos < 0) return pHead->info;
		Node* p =pHead;
		for (int i = 0; i < pos; i++)
		{
			if (p->pNext == NULL)
				return pTail->info;
			p = p->pNext;
		}
		return p->info;
	}
	~LinkedList()
	{
		if (pHead == NULL)
			return;
		while (pHead != NULL)
		{
			Node* p = pHead;
			pHead = pHead->pNext;
			delete p;
		}
		cout <<"Removed Linked List\n";
	}
};
void main()
{
	srand(1234);
	LinkedList l;
	for (int i = 0; i < 10; ++i)
	{
		if (rand() % 2 == 0)
		{
			l.AddHead(rand() % 1001);
		}
		else
		{
			l.AddTail(rand() % 1001);
		}
	}
	cout << l << endl;
	
	l.RemoveHead();
	l.RemoveTail();
	l[-1] = 9000;
	l[4] = 2000;
	l[100] = 10000;
	cout << l << endl;
}