#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h> 
#include<algorithm>
#define INF 999999
using namespace std;
//自定义结构体 
typedef struct arcnode
{
	int weight;		//边的权值
	struct arcnode *next;
	int index;	//邻接点的序号
	int mintree;	//最短路径上的边 
}AR;
typedef struct MyGraph
{
	int type;//0表示无向图，1表示有向图
	int arcnum,vexnum;//图中边的个数和顶点的个数
	char (*vexname)[20];//存放顶点名字的二维动态数组名（行指针） 
	AR *N;//存放链表头节点的数组名（动态数组）
}GH;
struct edge			//边的定义 
{
	int u,v,w;
	bool operator<(edge &e)	//用于sort排序 
	{
		return w < e.w;
	}
};

//全局变量
char filename[30];
edge *e;	//边集数组 
int *f;		//并查集 

//函数声明 
void PrintGraph(GH *G); 			//打印整张图 
void CreateGraph(GH *&G,int type);	//创建图 
int FindIndex(GH *G,char *name);	//返回顶点名称对应的序号 
void Prim(GH *G);		//prim算法
void Kruskal(GH *G);	//kruskal算法 
void dfs(GH *G,int i);	//深搜输出最小生成树 
void bfs(GH *G,int s);	//宽搜输出最小生成树 

//主函数 
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
void Prim(GH *G)
{
	cout<<"Prim算法输出结果：\n";
	bool *book;						//用于划分集合S和！S 
	int n = G->vexnum;
	int i,j,min,u,v,w;
	arcnode *t;
	book = new bool[n];
	for(i =0;i<n;i++)book[i] = false;		//初始化 
	book[0] = true;
	for(i = 0;i< n - 1;i++)		//共选取n-1条边 
	{
		min = INF;
		for(j = 0;j<n;j++)			//遍历所有边找最小的边(x,y)，其中x属于S，y不属于S
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
		book[v] = true;		//将y加入S 
		t = G->N[u].next;
		while(t)
		{
			if(t->index == v) {t->mintree = 1;break;}
			t = t->next;
		}
		cout<<G->vexname[u]<<" "<<G->vexname[v]<<" "<<w<<endl;	//输出该条边 
	}
	delete book; 
}
int find(int x)		//元素x所在的集合 
{
	if(f[x] == x) return x;
	return f[x] = find(f[x]); 
}
void Union(int x,int y)//合并x,y所在的集合 
{
	x = find(x);
	y = find(y);
	f[x] = y;
}
void Kruskal(GH *G)
{
	cout<<"Kruskal算法输出结果：\n";
	int num = 0,leave,u,v;
	arcnode *t;
	e = new edge[2 * G->arcnum + 1];
	f = new int[G->vexnum + 1];
	leave = G->vexnum - 1; 
	for(int j = 0;j<G->vexnum;j++)	//把所有边统计下来 
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
	sort(e,e + num);		//对边进行升序排序 
	while(leave)			//选够n-1条边即退出 
	for(int i = 0;i<num;i++)	//遍历所有边 
	{
		u = e[i].u;v = e[i].v;
		if(find(u) != find(v))	//如果不属于同一集合则合并并输出该边 
		{
			Union(u,v);
			leave--;
			cout<<G->vexname[u]<<" "<<G->vexname[v]<<" "<<e[i].w<<endl;
		}
	}
	delete e;
	delete f;
} 
void dfs(GH *G,int i)	//深搜输出最小生成树 (不需要标记是否已经访问过 因为最小生成树生成树时是单向的且没有环)
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
void bfs(GH *G,int s)	//宽搜输出最小生成树 
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


