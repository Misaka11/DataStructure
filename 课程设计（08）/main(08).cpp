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
	int type;//0��ʾ����ͼ��1��ʾ����ͼ
	int arcnum,vexnum;//ͼ�бߵĸ����Ͷ���ĸ���
	char (*vexname)[20];//��Ŷ������ֵĶ�ά��̬����������ָ�룩 
	int **g; 	//��̬��ά����ͼ 
}GH;

//ȫ�ֱ���
char filename[30];

//�������� 
void PrintGraph(GH *G); 			//��ӡ����ͼ 
void CreateGraph(GH *&G,int type);	//����ͼ 
int FindIndex(GH *G,char *name);	//���ض������ƶ�Ӧ����� 
void DIJ(GH *G,int s);				//������s���������е�����·���ͳ��� 
void Floyd(GH *G);					//���������������֮������·���Լ�·������ 
void PrintPath_DIJ(GH *G,int *path,int j);//�ݹ����·�� 
void PrintPath_Floyd(GH *G,int **path,int i,int j);//�ݹ����·�� 

//������ 
int main()
{
	GH *G = NULL;
	CreateGraph(G,1);
//	PrintGraph(G);
	cout<<"���õϽ�˹�����㷨���������������֮������·���Լ�·������"<<endl;
	for(int i = 0;i<G->vexnum;i++)
		DIJ(G,i);
	cout<<"���ø��������㷨���������������֮������·���Լ�·������"<<endl;	
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
	cout<<"�����ͼΪ��"<<endl;
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
	if(j == -1) return;	//���������·�򷵻� 
	PrintPath_DIJ(G,path,path[j]);	//�����jǰ���·�� 
	cout<<G->vexname[j]<<"->";		//���j 
}
void DIJ(GH *G,int s)
{
	int N = G->vexnum,min,v;
	bool *book = new bool[N];	//���ּ��� 
	int *dis = new int[N];		//��̳������� 
	int *path = new int[N];		//·����path[i]��¼i�Ŷ������·���ϵ�ǰ�� 
	for(int i = 0;i<N;i++)		//��ʼ������ 
	{
		book[i] = 0;
		dis[i] = INF;
		path[i] = -1;
	}
	dis[s] = 0;					//��ʼ��� 
	for(int i = 0;i<N;i++)		//�ɳ�N�� 
	{
		min = INF;
		for(int j = 0;j<N;j++)	//����С��dis 
		if(!book[j])
			if(dis[j] < min) {min = dis[j];v = j;}
		book[v] = 1;		//vȷ������뼯��book 
		for(int j = 0;j<N;j++)	//ͨ��v�����ɳ� 
			if(!book[j] && min + G->g[v][j] < dis[j])
			{
				dis[j] = min + G->g[v][j];
				path[j] = v;
			}
	}
	for(int j = 0;j<N;j++)	//���s�������ܵ��������·�� 
	{
		if(dis[j] == INF || j == s) continue; 
		PrintPath_DIJ(G,path,path[j]);
		cout<<G->vexname[j]<<" "<<"���ȣ�"<<dis[j];
		cout<<endl;
	}
	delete book;
	delete path;
	delete dis;
} 
void PrintPath_Floyd(GH *G,int **path,int i,int j)
{
	if(i == j) return;
	if(path[i][j] == -1)	//���������·�򷵻� 
	{
		cout<<G->vexname[j]<<"->"; 
	}
	else
	{
		PrintPath_Floyd(G,path,i,path[i][j]);	//���i���м���·�� 
		PrintPath_Floyd(G,path,path[i][j],j);	//����м�㵽j��·�� 
	}
}
void Floyd(GH *G)
{
	int N = G->vexnum;
	int **dis = new int*[N];	//��̳������� 
	int **path = new int*[N];	//·����path[i][j]��¼i��j���·���Ͼ����Ľڵ� 
	for(int i = 0;i<N;i++) 	//��ʼ�� 
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
	for(int i = 0;i<N;i++)	//������е㵽���е�����·�� 
		for(int j = 0;j<N;j++)
		{
			if(dis[i][j] == INF || i == j) continue;
			cout<<G->vexname[i]<<"->";
			PrintPath_Floyd(G,path,i,j);
			cout<<" "<<"���ȣ�"<<dis[i][j];
			cout<<endl;
		}
		
} 




