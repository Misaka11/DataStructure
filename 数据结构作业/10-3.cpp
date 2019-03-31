#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string.h>
using namespace std;
#define MAX_NUM_OF_KEY 8	//关键字项数的最大值 
#define RADIX 10			//关键字基数，此时是十进制整数的基数 
#define MAX_SPACE 10000		//最大数据数 

//自定义结构体
typedef struct
{
	int keys[MAX_NUM_OF_KEY];
	int key_data;
	int next;
} SLCell;					//静态链表的结点类型 
typedef struct
{
	SLCell r[MAX_SPACE];	//静态链表的可利用空间，r[0]为头结点 
	int keynum;				//记录的当前关键字个数 
	int recnum;				//静态链表的当前长度 
}SLList;					//静态链表类型 

//函数声明 
void RadixSort(SLList &L);
void Collect(SLCell *r, int i, int *f, int *e);
void Distribute(SLCell *r, int i, int *f, int *e);
void Create(SLList &L);
void Print(SLList &L);

//主函数
int main()
{
	SLList L;
	Create(L);
	cout << "随机数据为：\n";
	Print(L);
	cout << "经过基数排序后的数据为：\n";
	RadixSort(L);
	Print(L); 
	return 0;
}

//函数定义 
void Create(SLList &L)
{
	srand(time(0));
	cout << "输入数据个数N = ";
	cin >> L.recnum;
	L.keynum = 4;
	for (int i = 1; i <= L.recnum; i++)
	{
		int data = rand() % 10000;
		L.r[i].key_data = data;
		for (int k = 0; k<L.keynum; k++)
		{
			L.r[i].keys[k] = data % 10;
			data /= 10;
		}
	}
	for (int i = 0; i<L.recnum; i++)L.r[i].next = i + 1;
	L.r[L.recnum].next = 0;				//将L改造为静态链表
}
void RadixSort(SLList &L)
{
	int f[RADIX], e[RADIX];
	for (int i = 0; i<L.keynum; i++)
	{
		Distribute(L.r, i, f, e);
		Collect(L.r, i, f, e);
	}
}
void Distribute(SLCell *r, int i, int *f, int *e)
{
	int j, p;
	for (j = 0; j<RADIX; j++) f[j] = 0;
	for (p = r[0].next; p; p = r[p].next)
	{
		j = r[p].keys[i];
		if (!f[j]) f[j] = p;
		else r[e[j]].next = p;
		e[j] = p;
	}
}
void Collect(SLCell *r, int i, int *f, int *e)
{
	int j, t = 0;
	for (j = 0; j < RADIX; j++)
		if (f[j])
		{
			r[t].next = f[j]; t = e[j];
		}
	r[t].next = 0;
}
void Print(SLList &L)
{
	for (int k = L.r[0].next; k; k = L.r[k].next)
	{
		cout << L.r[k].key_data << " ";
	}
	cout << endl;
}
//10-3.实现基数排序；

