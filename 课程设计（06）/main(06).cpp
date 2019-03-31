#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h> 
#include<algorithm>
#define INF 999999
using namespace std;
//�Զ���ṹ�� 
typedef struct arcnode
{
	int weight;		//�ߵ�Ȩֵ
	struct arcnode *next;
	int index;	//�ڽӵ�����
	int mintree;	//���·���ϵı� 
}AR;
typedef struct MyGraph
{
	int type;//0��ʾ����ͼ��1��ʾ����ͼ
	int arcnum,vexnum;//ͼ�бߵĸ����Ͷ���ĸ���
	char (*vexname)[20];//��Ŷ������ֵĶ�ά��̬����������ָ�룩 
	AR *N;//�������ͷ�ڵ������������̬���飩
}GH;
struct edge			//�ߵĶ��� 
{
	int u,v,w;
	bool operator<(edge &e)	//����sort���� 
	{
		return w < e.w;
	}
};

//ȫ�ֱ���
char filename[30];
edge *e;	//�߼����� 
int *f;		//���鼯 

//�������� 
void PrintGraph(GH *G); 			//��ӡ����ͼ 
void CreateGraph(GH *&G,int type);	//����ͼ 
int FindIndex(GH *G,char *name);	//���ض������ƶ�Ӧ����� 
void Prim(GH *G);		//prim�㷨
void Kruskal(GH *G);	//kruskal�㷨 
void dfs(GH *G,int i);	//���������С������ 
void bfs(GH *G,int s);	//���������С������ 

//������ 
int main()
{
	GH *G = NULL;
	CreateGraph(G,0);
	PrintGraph(G);
	Prim(G);
	cout<<endl;
	Kruskal(G);
	cout<<"bfs:\n";
	dfs(G,0);
	cout<<"dfs:\n";
	bfs(G,0);
	system("pause");
	return 0;
}

int FindIndex(GH *G,char *name)
{
	for(int i = 0;i<G->vexnum;i++)
		if(strcmp(G->vexname[i],name) == 0)
			return i;
	return -1;
}

void CreateGraph(GH *&G,int type)
{
	cout<<"�������ļ�����";
	cin>>filename;
	ifstream fin;
	fin.open(filename,ios::in);
	if(fin.fail())
	{
		cout<<"δ�ҵ����ļ�"<<endl;
		exit(0);
	}
	G = new GH;
	G->type = type;
	G->arcnum = 0;
	fin>>G->vexnum;
	G->N = new AR[G->vexnum];
	G->vexname = new char[G->vexnum][20];
	char vname[20];
	for(int i = 0;i<G->vexnum;i++)
	{
		fin>>vname;
		strcpy(G->vexname[i],vname);
		G->N[i].next = NULL;
	}
	if(type == 1)
	{
		char u[20],v[20];
		int w;
		arcnode *t;
		while(fin>>u>>v>>w)
		{
			int i = FindIndex(G,u);
			int j = FindIndex(G,v);
			if(i!=-1 && j!=-1)
			{
				G->arcnum++;
				t = new arcnode;
				t->index = j;
				t->next = G->N[i].next;
				t->weight = w;
				G->N[i].next = t;
			}
		}
	}
	else
	{
		char u[20],v[20];
		int w;
		arcnode *t;
		while(fin>>u>>v>>w)
		{
			int i = FindIndex(G,u);
			int j = FindIndex(G,v);
			if(i!=-1 && j!=-1)
			{
				G->arcnum++;
				//����ӱ� 
				t = new arcnode;
				t->index = j;
				t->next = G->N[i].next;
				t->weight = w;
				G->N[i].next = t;
				//����ӱ� 
				t = new arcnode;
				t->index = i;
				t->next = G->N[j].next;
				t->weight = w;
				G->N[j].next = t;
			}
		}
	}
	
	fin.close();
}
void PrintGraph(GH *G)
{
	if(!G) return;
	cout<<"�����ͼΪ��"<<endl;
	for(int i = 0;i<G->vexnum;i++)
	{
		cout<<G->vexname[i]<<" ";
		arcnode *t = G->N[i].next;
		while(t)
		{
			cout<<G->vexname[t->index]<<" ";
			t = t->next;
		}
		cout<<endl;
	}
}
void Prim(GH *G)
{
	cout<<"Prim�㷨��������\n";
	bool *book;						//���ڻ��ּ���S�ͣ�S 
	int n = G->vexnum;
	int i,j,min,u,v,w;
	arcnode *t;
	book = new bool[n];
	for(i =0;i<n;i++)book[i] = false;		//��ʼ�� 
	book[0] = true;
	for(i = 0;i< n - 1;i++)		//��ѡȡn-1���� 
	{
		min = INF;
		for(j = 0;j<n;j++)			//�������б�����С�ı�(x,y)������x����S��y������S
		if(book[j])
		{
			t = G->N[j].next;
			while(t)
			{
				if(!book[t->index] && t->weight < min)
				{
					u = j;v = t->index;w = t->weight;
					min = w;
				}
				t = t->next;
			}
		}
		book[v] = true;		//��y����S 
		t = G->N[u].next;
		while(t)
		{
			if(t->index == v) {t->mintree = 1;break;}
			t = t->next;
		}
		cout<<G->vexname[u]<<" "<<G->vexname[v]<<" "<<w<<endl;	//��������� 
	}
	delete book; 
}
int find(int x)		//Ԫ��x���ڵļ��� 
{
	if(f[x] == x) return x;
	return f[x] = find(f[x]); 
}
void Union(int x,int y)//�ϲ�x,y���ڵļ��� 
{
	x = find(x);
	y = find(y);
	f[x] = y;
}
void Kruskal(GH *G)
{
	cout<<"Kruskal�㷨��������\n";
	int num = 0,leave,u,v;
	arcnode *t;
	e = new edge[2 * G->arcnum + 1];
	f = new int[G->vexnum + 1];
	leave = G->vexnum - 1; 
	for(int j = 0;j<G->vexnum;j++)	//�����б�ͳ������ 
	{
		f[j] = j;
		t = G->N[j].next;
		while(t)
		{
			e[num].u = j;
			e[num].v = t->index;
			e[num].w = t->weight;
			num++;
			t = t->next;
		}
	}
	sort(e,e + num);		//�Ա߽����������� 
	while(leave)			//ѡ��n-1���߼��˳� 
	for(int i = 0;i<num;i++)	//�������б� 
	{
		u = e[i].u;v = e[i].v;
		if(find(u) != find(v))	//���������ͬһ������ϲ�������ñ� 
		{
			Union(u,v);
			leave--;
			cout<<G->vexname[u]<<" "<<G->vexname[v]<<" "<<e[i].w<<endl;
		}
	}
	delete e;
	delete f;
} 
void dfs(GH *G,int i)	//���������С������ (����Ҫ����Ƿ��Ѿ����ʹ� ��Ϊ��С������������ʱ�ǵ������û�л�)
{
	arcnode *t = G->N[i].next;
	while(t)
	{
		if(t->mintree)
		{
			cout<<G->vexname[i]<<" "<<G->vexname[t->index]<<" "<<t->weight<<endl;
			dfs(G,t->index);
		}
		t = t->next;
	} 
} 
void bfs(GH *G,int s)	//���������С������ 
{
	int *q = new int[G->vexnum + 2];
	int h = 0,r = 0;
	q[r++] = s;
	arcnode *t;
	while(h<r)
	{
		t = G->N[q[h]].next;
		while(t)
		{
			if(t->mintree)
			{
				cout<<G->vexname[q[h]]<<" "<<G->vexname[t->index]<<" "<<t->weight<<endl;
				q[r++] = t->index;
			}
			t = t->next;
		}
		h++;
	}
	delete q;
} 


