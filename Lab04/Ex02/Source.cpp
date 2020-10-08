#include <iostream>
#include <string>
using namespace std;
struct Node
{
	char letter;
	Node* next;
};
int CountNode(Node* head)
{
	int t = 0;
	while (head != NULL)
	{
		t++;
		head = head->next;
	}
	return t;
}
class BigInt
{
private:
	Node* head;
public:
	BigInt()
	{
		head = CreateNode(NULL);
	};
	Node* CreateNode(char P)
	{
		Node* p = new Node();
		if (p == NULL)
		{
			cout << "Don't have enough memory\n";
			return NULL;
		}
		p->letter = P;
		p->next = NULL;
		return p;
	}
	void AddFirst(Node *&head, char P)
	{
		Node* p = CreateNode(P);
		if (head == NULL)
		{
			head = p;
			return;
		}
		p->next = head;
		head = p;
	}
	void AddLast(Node*& head, char P)
	{
		Node* p;
		if (head == NULL)
		{
			head = CreateNode(P);
			return;
		}
		p = head;
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = CreateNode(P);
	}
	void DeleteFirst(Node*& head)
	{
		Node* p = head;
		if (head == NULL)
			return;
		head = head->next;
		delete p;
	}
	void DeleteLast(Node*& head)
	{
		Node* p;
		Node* prev;
		if (head == NULL)
			return;
		p = prev = head;
		while (p->next != NULL)
		{
			prev = p;
			p = p->next;
		}
		delete p;
		prev->next = NULL;
	}
	Node* ReverseList(Node* head)
	{
		Node* temp = NULL;
		Node* p = head;
		while (p != NULL)
		{
			AddFirst(temp, p->letter);
			p = p->next;
		}
		return temp;
	}
	BigInt(int value)
	{
		string temp = to_string(value);
		while (!temp.empty())
		{
			AddLast(head, temp[0]);
			temp.erase(0, 1);
		}
	}
	BigInt(int value, int n)
	{
		string temp;
		for (int i = 0; i < n; i++)
			temp += to_string(value);
		while (!temp.empty())
		{
			AddLast(head, temp[0]);
			temp.erase(0, 1);
		}
	}
	BigInt operator+(int &n)
	{
		BigInt a;
		a = *this;
		BigInt* Result = new BigInt();
		DeleteFirst(Result->head);
		BigInt b(n);
		Node* p1 = ReverseList(a.head);
		Node* p2 = ReverseList(b.head);
		bool flag = false;
		int n1 = CountNode(p1);
		int n2 = CountNode(p2);
		if (n1 > n2)
			for (int i = 0; i < n1 - n2; i++)
				AddLast(p2, '0');
		else
			for (int i = 0; i < n2 - n1; i++)
				AddLast(p1, '0');
		while (p1 != NULL && p2 != NULL)
		{
			int t1 = p1->letter - 48;
			int t2 = p2->letter - 48;
			int temp = t1 + t2;
			if (flag) temp++;
			if (temp < 10)
			{
				AddFirst(Result->head, temp + 48);
				flag = false;
			}
			else
			{
				temp -= 10;
				AddFirst(Result->head, temp + 48);
				flag = true;
			}
			p1 = p1->next;
			p2 = p2->next;
		}
		return *Result;
	}
	BigInt operator+(BigInt &b)
	{
		BigInt a;
		a = *this;
		BigInt* Result = new BigInt();
		DeleteFirst(Result->head);
		Node* p1 = ReverseList(a.head);
		Node* p2 = ReverseList(b.head);
		bool flag = false;
		int n1 = CountNode(p1);
		int n2 = CountNode(p2);
		if (n1 > n2)
			for (int i = 0; i < n1 - n2; i++)
				AddLast(p2, '0');
		else
			for (int i = 0; i < n2 - n1; i++)
				AddLast(p1, '0');
		while (p1 != NULL && p2 != NULL)
		{
			int temp = p1->letter + p2->letter - 96;
			if (flag) temp++;
			if (temp < 10)
			{
				 AddFirst(Result->head, temp + 48);
				flag = false;
			}
			else
			{
				temp -= 10;
				AddFirst(Result->head, temp + 48);
				flag = true;
			}
			p1 = p1->next;
			p2 = p2->next;
		}
		if (flag) AddFirst(Result->head, '1');
		return *Result;
	}
	BigInt operator*(BigInt &b)
	{
		BigInt a;
		a = *this;
		BigInt* Result = new BigInt();
		DeleteFirst(Result->head);
		Node* p1 = ReverseList(a.head);
		Node* p2 = ReverseList(b.head);
		bool flag = false;
		int n1 = CountNode(p1);
		int n2 = CountNode(p2);
		if (n1 > n2)
			for (int i = 0; i < n1 - n2; i++)
				AddLast(p2, '0');
		else
			for (int i = 0; i < n2 - n1; i++)
				AddLast(p1, '0');
		int count = 0;
		while (p2 != NULL)
		{
			BigInt temp;
			DeleteFirst(temp.head);
			int t = p2->letter - 48;
			for (int i = 0; i < t; i++)
				temp = temp + a;
			for (int i = 0; i < count; i++)
				AddLast(temp.head, '0');
			*Result = *Result + temp;
			count++;
			p2 = p2->next;
		}
		return *Result;
	}
	BigInt operator-(BigInt &b)
	{
		BigInt a; 
		a =  *this;
		BigInt *Result = new BigInt();
		DeleteFirst(Result->head);

		Node* p1 = ReverseList(a.head);
		Node* p2 = ReverseList(b.head);

		int n1 = CountNode(p1);
		int n2 = CountNode(p2);
		if (n2 > n1)
		{
			BigInt S(0);
			return S;
		}
		else if (n1 == n2)
		{
			Node* t1 = ReverseList(p1);
			Node* t2 = ReverseList(p2);
			while (t1 != NULL && t2 != NULL)
			{
				int temp = t1->letter - t2->letter;
				if (temp < 0)
				{
					BigInt S(0);
					return S;
				}
				t1 = t1->next;
				t2 = t2->next;
			}
		}
		else
			for (int i = 0; i < n1 - n2; i++)
				AddLast(p2, '0');
		bool flag = false;
		while (p1 != NULL && p2 != NULL)
		{
			int temp = p1->letter - p2->letter;
			if (flag) temp--;
			if (temp >= 0)
			{
				char P = temp + 48;
				AddFirst(Result->head, P);
				flag = false;
			}
			else
			{
				temp += 10;
				char P = temp + 48;
				AddFirst(Result->head, P);
				flag = true;
			}
			p1 = p1->next;
			p2 = p2->next;
		}
		return *Result;
	}
	friend BigInt operator-(int &n, BigInt &b)
	{
		BigInt *a(n) = new BigInt();
		BigInt* Result = new BigInt();
		Result = a - b;
		return *Result;
	}
	BigInt& operator=(const BigInt &b)
	{
		Node* p = b.head;
		DeleteFirst(this->head);
		while (p != NULL)
		{
			char K = p->letter;
			AddLast(this->head, K);
			p = p->next;
		}
		return *this;
	}
	friend ostream& operator<< (ostream& os, const BigInt &A)
	{
		Node* p = A.head;
		if (p->letter == NULL && p->next == NULL)
		{
			os << '0';
			return os;
		}
		while (p != NULL)
		{
			os << p->letter;
			p = p->next;
		}
		return os;
	}
	~BigInt()
	{
		Node* temp;
		while (head != NULL)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
	}
};
void main()
{
	BigInt n1;
	BigInt n2(44667733);
	BigInt n3(5, 9);
	BigInt n4(7, 30);
	BigInt n5 = n3 - n2;
	BigInt n6 = 1098765432 - n2;
	BigInt n7 = n4 - n3 + 123456789;
	BigInt n8 = n2 * n3;
	cout << n1 << endl << n2 << endl << n3 << endl << n4 << endl << n5 << endl << n6 << endl << n7 << endl << n8 << endl;
}