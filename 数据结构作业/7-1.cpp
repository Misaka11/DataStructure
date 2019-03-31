#include<iostream>
#include<fstream>
#include<string.h> 
using namespace std;

typedef struct arcnode
{
	int weight;		//边的权值
	struct arcnode *next;
	int index;	//邻接点的序号
}AR;
typedef struct MyGraph
{
	int type;//0表示无向图，1表示有向图
	int arcnum,vexnum;//图中边的个数和顶点的个数
	char **vexname;//存放顶点名字的二维动态数组名（行指针）
	AR *N;//存放链表头节点的数组名（动态数组）
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
		cout<<"未找到该文件"<<endl;
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
	cout<<"读入的图为："<<endl;
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
//深搜 
void FindPath(GH *G,int index)
{
	if(index == -1) return;
	//人工栈 
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
		//当前节点无可走路径时弹栈 
		if(!t)
		{
			visit[stack[top].index] = 0;
			top--;
			continue;
		}
		stack[top].t = stack[top].t->next;
		if(!visit[t->index])			//遇到没访问过的节点压栈 
		{
			stack[++top].index = t->index;
			stack[top].t = G->N[t->index].next;
			visit[t->index] = 1;
		}
		else
			if(t->index == index)	//已访问过的节点判断是否是终点 
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
	cout<<"请输入文件名：";
	cin>>filename;
	GH *G = CreateGraph(filename);
	PrintGraph(G);
	cout<<"经过v2的所有回路为：\n";
	FindPath(G,FindIndex(G,"v2"));
	system("pause");
	return 0;
}
