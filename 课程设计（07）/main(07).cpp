
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h> 
#include<algorithm>
#include<stack>
#define INF 999999
using namespace std;
//自定义结构体 
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
	char (*vexname)[20];//存放顶点名字的二维动态数组名（行指针） 
	AR *N;//存放链表头节点的数组名（动态数组）
}GH;

//全局变量
char filename[30];
stack<int> T;
int *ve,*vl;

//函数声明 
void PrintGraph(GH *G); 			//打印整张图 
void CreateGraph(GH *&G,int type);	//创建图 
int FindIndex(GH *G,char *name);	//返回顶点名称对应的序号 
bool TopologicalOrder(GH *G,stack<int> &T);//拓扑排序，并计算最早开始时间 
bool CriticalPath(GH *G);			//关键路径 

//主函数 
int main()
{
	GH *G = NULL;
	CreateGraph(G,1);
//	PrintGraph(G);
	CriticalPath(G);
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
	cout<<"请输入文件名：";
	cin>>filename;
	ifstream fin;
	fin.open(filename,ios::in);
	if(fin.fail())
	{
		cout<<"未找到该文件"<<endl;
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
				//正向加边 
				t = new arcnode;
				t->index = j;
				t->next = G->N[i].next;
				t->weight = w;
				G->N[i].next = t;
				//反向加边 
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
bool TopologicalOrder(GH *G,stack<int> &T)
{
	int *indegree,count = 0;
	indegree = new int[G->vexnum + 1];	//统计入度的数组 
	ve = new int[G->vexnum + 1];	//最早开始时间的数组 
	for(int i = 0;i<G->vexnum;i++) indegree[i] = ve[i] = 0;
	for(int i = 0;i<G->vexnum;i++)	//遍历图，统计入度 
	{
		arcnode *t = G->N[i].next;
		while(t)
		{
			indegree[t->index]++;
			t = t->next;
		}
	}
	stack<int> s;	//拓扑排序 
	for(int i = 0;i<G->vexnum;i++)	//入度为0入栈 
		if(!indegree[i])s.push(i); 
	while(!s.empty())		//栈不为空 
	{
		int j = s.top();
		T.push(j);
		s.pop();
		count++;
		for(arcnode *t = G->N[j].next;t;t = t->next)
		{
			if(--indegree[t->index] == 0) s.push(t->index);	//删除栈顶的点，重新计算入度并入栈 
			if(ve[j] + t->weight > ve[t->index]) ve[t->index] = ve[j] + t->weight;//计算最早开始时间 
		}
	}
	if(count<G->vexnum)return false;	//如果拓扑排序的节点不足总节点数，则存在回路 
	return true;
}
bool CriticalPath(GH *G)
{
	if(!TopologicalOrder(G,T)) return false;	//如果拓扑排序失败则返回 
	int ee,el;
	vl = new int[G->vexnum + 1];	//最晚开始时间数组 
	//最晚开始时间都等于最后节点的最早开始时间 
	for(int i = 0;i<G->vexnum;i++) vl[i] = ve[G->vexnum-1];	
	while(!T.empty())		//逆拓扑顺序 
	{
		int j = T.top();
		T.pop();
		for(arcnode *t = G->N[j].next;t;t = t->next)	//计算最晚开始时间 
		{
			if(vl[t->index] - t->weight < vl[j]) vl[j] = vl[t->index] - t->weight; 
		}
	}
	for(int i = 0;i<G->vexnum;i++)		//对于每条边，看其最早和最晚开始时间是否相等 
	{
		for(arcnode *t = G->N[i].next;t;t = t->next)
		{
			ee = ve[i];el = vl[t->index] - t->weight;
			cout<<G->vexname[i]<< " "<<G->vexname[t->index]<<" "<<t->weight<<" "
				<<ee<<" "<<el<<" "<<(ee==el?'*':' ')<<endl;	//输出*代表此条边是关键路径 
		}
	}
	return true; 
}



