#include<iostream>
#include<fstream>
#include<string.h> 
using namespace std;

typedef struct arcnode
{
	int weight;		//�ߵ�Ȩֵ
	struct arcnode *next;
	int index;	//�ڽӵ�����
}AR;
typedef struct MyGraph
{
	int type;//0��ʾ����ͼ��1��ʾ����ͼ
	int arcnum,vexnum;//ͼ�бߵĸ����Ͷ���ĸ���
	char **vexname;//��Ŷ������ֵĶ�ά��̬����������ָ�룩
	AR *N;//�������ͷ�ڵ������������̬���飩
}GH;

int FindIndex(GH *G,char *name)
{
	for(int i = 0;i<G->vexnum;i++)
		if(strcmp(G->vexname[i],name) == 0)
			return i;
	return -1;
}

GH *CreateGraph(char *filename)
{
	GH *G;
	ifstream fin;
	fin.open(filename,ios::in);
	if(fin.fail())
	{
		cout<<"δ�ҵ����ļ�"<<endl;
		exit(0);
	}
	G = new GH;
	G->type = 1;
	G->arcnum = 0;
	fin>>G->vexnum;
	G->N = new AR[G->vexnum];
	G->vexname = new char*[G->vexnum];
	char vname[20];
	for(int i = 0;i<G->vexnum;i++)
	{
		fin>>vname;
		G->vexname[i] = new char[strlen(vname) + 1];
		strcpy(G->vexname[i],vname);
		G->N[i].next = NULL;
	}
	
	char u[20],v[20];
	arcnode *t;
	while(fin>>u>>v)
	{
		t = new arcnode;
		int i = FindIndex(G,u);
		int j = FindIndex(G,v);
		if(i!=-1 && j!=-1)
		{
			G->arcnum++;
			t->index = j;
			t->next = G->N[i].next;
			t->weight = 1;
			G->N[i].next = t;
		}
	}
	fin.close();
	return G;
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
//���� 
void FindPath(GH *G,int index)
{
	if(index == -1) return;
	//�˹�ջ 
	struct 
	{
		int index;
		arcnode *t;
	}stack[50];
	int top = -1;
	bool visit[50];
	for(int i = 0;i<50;i++)visit[i] = 0;
	stack[++top].index = index;
	stack[top].t = G->N[index].next;
	visit[index] = 1;
	while(top >= 0)
	{
		arcnode *t = stack[top].t;
		//��ǰ�ڵ��޿���·��ʱ��ջ 
		if(!t)
		{
			visit[stack[top].index] = 0;
			top--;
			continue;
		}
		stack[top].t = stack[top].t->next;
		if(!visit[t->index])			//����û���ʹ��Ľڵ�ѹջ 
		{
			stack[++top].index = t->index;
			stack[top].t = G->N[t->index].next;
			visit[t->index] = 1;
		}
		else
			if(t->index == index)	//�ѷ��ʹ��Ľڵ��ж��Ƿ����յ� 
			{
				for(int i = 0;i<=top;i++)
					cout<<G->vexname[stack[i].index]<<" ";
				cout<<G->vexname[index]<<endl; 
			}
	}
	
}

int main()
{
	char filename[30];
	cout<<"�������ļ�����";
	cin>>filename;
	GH *G = CreateGraph(filename);
	PrintGraph(G);
	cout<<"����v2�����л�·Ϊ��\n";
	FindPath(G,FindIndex(G,"v2"));
	system("pause");
	return 0;
}
