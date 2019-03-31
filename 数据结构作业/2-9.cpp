#include<iostream>
#include<stdlib.h>
using namespace std;

#define N 15
#define Step 6

struct node
{
	int data;
	node *next;
};
void PrintList(node *head)
{
	node *t = head->next;
	cout<<head->data<<" ";
	while(t!=head)
	{
		cout<<t->data<<" ";
		t = t->next;
	}
	cout<<endl;
}

node *head,*q,*t,*p;
int count;

int main()
{
	//建立循环链表 
	head = new node;
	head->data = 1;
	head->next = 0;
	q = head;
	for(int i = 2;i<=N;i++)
	{
		t = new node;
		t->data = i;
		t->next = 0;
		q->next = t;
		q = t;
	}
	q->next = head;
	PrintList(head); 
	//开始删除
	p = q;
	count = 1;
	while(p->next != p)
	{
		count++;
		p = p->next;
		if(count == Step)
		{
			t = p->next;
			p->next = t->next;
			cout<<t->data<<" ";
			free(t);
			count = 1;
		}
	} 
	cout<<p->data;
	return 0;
}
