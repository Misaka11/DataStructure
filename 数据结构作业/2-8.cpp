#include<iostream>
#include<time.h>
#include<stdlib.h>

#define N 15
using namespace std;

int Arr1[N],Arr2[N],Arr[N];
int n,m,InitN,InitM;

struct node
{
	int data;
	node *next;
};
node *head1,*head2,*head;

//数组函数
void InitArr(int *a,int n);	
void PrintArr(int *a,int n);
int QuChongArr(int *a,int n);
void SortArr(int *a,int n);
int JiaoArr(int *a,int *b,int *c,int n,int m);
//链表函数
node* InitList(int n);
void PrintList(node *head);
int QuChongList(node *head, int n);
void SortList(node *head,int n);
node* JiaoList(node *h1,node *h2);

void SwapInt(int &a,int &b)
{
	int t = a; a = b; b = t;
}

int main()
{
	srand(time(0));
	cout<<"请输入两个顺序表的元素个数n和m：";
	cin>>InitN>>InitM;
	//数组处理
	n = InitN; m = InitM;
	cout<<"以下为数组的操作：\n";
	InitArr(Arr1,n);
	InitArr(Arr2,m);
	cout<<"原来的数组元素为:";
	PrintArr(Arr1,n);
	PrintArr(Arr2,m);
	cout<<"\n去重后的数组元素为：";
	n = QuChongArr(Arr1,n);
	m = QuChongArr(Arr2,m);
	PrintArr(Arr1,n);
	PrintArr(Arr2,m);
	cout<<"\n排序后的数组元素为：";
	SortArr(Arr1,n);
	SortArr(Arr2,m);
	PrintArr(Arr1,n);
	PrintArr(Arr2,m);
	cout<<"\n求交集后的数组元素为：";
	PrintArr(Arr,JiaoArr(Arr1,Arr2,Arr,n,m));
	//链表处理
	n = InitN; m = InitM;
	cout<<"\n\n以下为链表的操作：\n";
	head1 = InitList(n);
	head2 = InitList(m);
	cout<<"原来的链表元素为:";
	PrintList(head1);
	PrintList(head2);
	cout<<"\n去重后的链表元素为：";
	n = QuChongList(head1,n);
	m = QuChongList(head2,m);
	PrintList(head1);
	PrintList(head2);
	cout<<"\n排序后的链表元素为：";
	SortList(head1,n);
	SortList(head2,m);
	PrintList(head1);
	PrintList(head2);
	cout<<"\n求交集后的链表元素为：";
	head = JiaoList(head1,head2);
	PrintList(head);

	getchar();getchar();
	return 0;
}

void InitArr(int *a,int n)
{
	for(int i = 0;i<n;i++)
		a[i] = rand() % 15;
}

void PrintArr(int *a,int n)
{
	cout<<endl;
	for(int i = 0;i<n;i++)
		cout<<a[i]<<" ";
}

int QuChongArr(int *a,int n)
{
	if(n == 0 || n==1) return n;
	int p,i;
	for(p = 1;p < n;)
	{
		for(i = 0;;i++)
			if(a[i] == a[p]) break;
		if(i != p) 
		{
			SwapInt(a[p],a[n-1]);
			n--;
			continue;
		}
		p++;
	}
	return n;
}

void SortArr(int *a,int n)
{
	for(int i = n - 1;i >= 0;i--)
	{
		bool k = true;
		for(int j = 0;j < i;j++)
			if(a[j] > a[j+1])
				{
					SwapInt(a[j],a[j+1]);
					k = false;
				}
		if(k) break;
	}
}

int JiaoArr(int *a,int *b,int *c,int n,int m)
{
	int ap = 0,bp = 0,cp = 0;
	while(ap < n && bp < m)
	{
		if(a[ap] < b[bp]) ap++;
		else if(a[ap] > b[bp]) bp++;
		else 
		{
			c[cp++] = a[ap];
			ap++;bp++;
		}
	}
	return cp;
}

node* InitList(int n)
{
	node *t,*head;
	head = new node;
	head->next = 0;
	for(int i = 0;i<n;i++)
	{
		t = new node;
		t->data = rand() % 15;
		t->next = head->next;
		head->next = t;
	}
	return head;
}

void PrintList(node *head)
{
	node *t = head->next;
	cout<<endl;
	while(t!=0)
	{
		cout<<t->data<<" ";
		t = t->next;
	}
}

int QuChongList(node *head, int n)
{
	node *p = head->next,*pp = head->next;	//pp为p的前驱
	if(p==0 || p->next==0) return n; 
	for(p = p->next;p!=0;)
	{
		node *t;
		for(t = head->next;;t = t->next)
			if(t->data == p->data) break;
		if(t != p)
		{
			pp->next = p->next;
			free(p); n--;
			p = pp->next;
			continue;
		}
		pp = p;
		p = p->next;
	}
	return n;
}

void SortList(node *head,int n)
{
	while(1)
	{
		bool k = true;
		node *p = head->next;
		while(p->next != 0)
		{
			if(p->data > p->next->data)
			{
				int t = p->data;
				p->data = p->next->data;
				p->next->data = t;
				k = false;
			}
			p = p->next;
		}
		if(k) break;
	}
}

node* JiaoList(node *h1,node *h2)
{
	node *p1 = h1->next,*p2 = h2->next,*q,*t;
	node *h = new node;
	h->next = 0;
	q = h;
	while(p1 && p2)
	{
		if(p1->data < p2->data) p1 = p1->next;
		else if(p1->data > p2->data) p2 = p2->next;
		else 
		{
			t = new node;
			t->data = p1->data;
			t->next = 0;
			q->next = t;
			q = q->next;
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	return h;
}
