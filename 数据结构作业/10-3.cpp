#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string.h>
using namespace std;
#define MAX_NUM_OF_KEY 8	//�ؼ������������ֵ 
#define RADIX 10			//�ؼ��ֻ�������ʱ��ʮ���������Ļ��� 
#define MAX_SPACE 10000		//��������� 

//�Զ���ṹ��
typedef struct
{
	int keys[MAX_NUM_OF_KEY];
	int key_data;
	int next;
} SLCell;					//��̬����Ľ������ 
typedef struct
{
	SLCell r[MAX_SPACE];	//��̬����Ŀ����ÿռ䣬r[0]Ϊͷ��� 
	int keynum;				//��¼�ĵ�ǰ�ؼ��ָ��� 
	int recnum;				//��̬����ĵ�ǰ���� 
}SLList;					//��̬�������� 

//�������� 
void RadixSort(SLList &L);
void Collect(SLCell *r, int i, int *f, int *e);
void Distribute(SLCell *r, int i, int *f, int *e);
void Create(SLList &L);
void Print(SLList &L);

//������
int main()
{
	SLList L;
	Create(L);
	cout << "�������Ϊ��\n";
	Print(L);
	cout << "������������������Ϊ��\n";
	RadixSort(L);
	Print(L); 
	return 0;
}

//�������� 
void Create(SLList &L)
{
	srand(time(0));
	cout << "�������ݸ���N = ";
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
	L.r[L.recnum].next = 0;				//��L����Ϊ��̬����
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
//10-3.ʵ�ֻ�������

