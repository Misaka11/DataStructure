#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h> 
#include<algorithm>
#include<stack>
#define INF 999999
using namespace std;

typedef struct MyGraph
{
	int type;//0表示无向图，1表示有向图
	int arcnum,vexnum;//图中边的个数和顶点的个数
	char (*vexname)[20];//存放顶点名字的二维动态数组名（行指针） 
	int **g; 	//动态二维数组图 
}GH;

//全局变量
char filename[30];

//函数声明 
void PrintGraph(GH *G); 			//打印整张图 
void CreateGraph(GH *&G,int type);	//创建图 
int FindIndex(GH *G,char *name);	//返回顶点名称对应的序号 
void DIJ(GH *G,int s);				//输出起点s到其它所有点的最短路径和长度 
void Floyd(GH *G);					//输出所有两两顶点之间的最短路径以及路径长度 
void PrintPath_DIJ(GH *G,int *path,int j);//递归输出路径 
void PrintPath_Floyd(GH *G,int **path,int i,int j);//递归输出路径 

//主函数 
int main()
{
	GH *G = NULL;
	CreateGraph(G,1);
//	PrintGraph(G);
	cout<<"利用迪杰斯特拉算法输出所有两两顶点之间的最短路径以及路径长度"<<endl;
	for(int i = 0;i<G->vexnum;i++)
		DIJ(G,i);
	cout<<"利用弗洛伊德算法输出所有两两顶点之间的最短路径以及路径长度"<<endl;	
	Floyd(G);
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
	G->g = new int*[G->vexnum];
	for(int i = 0;i<G->vexnum;i++)
		G->g[i] = new int[G->vexnum];
	G->vexname = new char[G->vexnum][20];
	char vname[20];
	for(int i = 0;i<G->vexnum;i++)
	{
		fin>>vname;
		strcpy(G->vexname[i],vname);
		for(int j = 0;j<G->vexnum;j++)
			G->g[i][j] = INF;
	}
	if(type == 1)
	{
		char u[20],v[20];
		int w;
		while(fin>>u>>v>>w)
		{
			int i = FindIndex(G,u);
			int j = FindIndex(G,v);
			if(i!=-1 && j!=-1)
			{
				G->arcnum++;
				G->g[i][j] = w;
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
		for(int j = 0;j<G->vexnum;j++)
			if(G->g[i][j] != INF) cout<<G->vexname[j]<<" ";
		cout<<endl;
	}
}
void PrintPath_DIJ(GH *G,int *path,int j)
{
	if(j == -1) return;	//如果到达死路则返回 
	PrintPath_DIJ(G,path,path[j]);	//先输出j前面的路径 
	cout<<G->vexname[j]<<"->";		//输出j 
}
void DIJ(GH *G,int s)
{
	int N = G->vexnum,min,v;
	bool *book = new bool[N];	//划分集合 
	int *dis = new int[N];		//最短长度数组 
	int *path = new int[N];		//路径。path[i]记录i号顶点最短路径上的前驱 
	for(int i = 0;i<N;i++)		//初始化工作 
	{
		book[i] = 0;
		dis[i] = INF;
		path[i] = -1;
	}
	dis[s] = 0;					//初始起点 
	for(int i = 0;i<N;i++)		//松弛N遍 
	{
		min = INF;
		for(int j = 0;j<N;j++)	//找最小的dis 
		if(!book[j])
			if(dis[j] < min) {min = dis[j];v = j;}
		book[v] = 1;		//v确定后加入集合book 
		for(int j = 0;j<N;j++)	//通过v进行松弛 
			if(!book[j] && min + G->g[v][j] < dis[j])
			{
				dis[j] = min + G->g[v][j];
				path[j] = v;
			}
	}
	for(int j = 0;j<N;j++)	//输出s到所有能到达点的最短路径 
	{
		if(dis[j] == INF || j == s) continue; 
		PrintPath_DIJ(G,path,path[j]);
		cout<<G->vexname[j]<<" "<<"长度："<<dis[j];
		cout<<endl;
	}
	delete book;
	delete path;
	delete dis;
} 
void PrintPath_Floyd(GH *G,int **path,int i,int j)
{
	if(i == j) return;
	if(path[i][j] == -1)	//如果到达死路则返回 
	{
		cout<<G->vexname[j]<<"->"; 
	}
	else
	{
		PrintPath_Floyd(G,path,i,path[i][j]);	//输出i到中间点的路径 
		PrintPath_Floyd(G,path,path[i][j],j);	//输出中间点到j的路径 
	}
}
void Floyd(GH *G)
{
	int N = G->vexnum;
	int **dis = new int*[N];	//最短长度数组 
	int **path = new int*[N];	//路径。path[i][j]记录i到j最短路径上经过的节点 
	for(int i = 0;i<N;i++) 	//初始化 
	{
		dis[i] = new int[N];
		path[i] = new int[N];
		for(int j = 0;j<N;j++)
		{
			dis[i][j] = G->g[i][j];
			path[i][j] = -1;

		}	
	}
	for(int k = 0;k<N;k++)	//floyd 
		for(int i = 0;i<N;i++)
			for(int j = 0;j<N;j++)
				if(dis[i][k] + dis[k][j] < dis[i][j])
				{
					dis[i][j] = dis[i][k] + dis[k][j];
					path[i][j] = k;
				}
	for(int i = 0;i<N;i++)	//输出所有点到所有点的最短路径 
		for(int j = 0;j<N;j++)
		{
			if(dis[i][j] == INF || i == j) continue;
			cout<<G->vexname[i]<<"->";
			PrintPath_Floyd(G,path,i,j);
			cout<<" "<<"长度："<<dis[i][j];
			cout<<endl;
		}
		
} 




