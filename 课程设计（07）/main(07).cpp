
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h> 
#include<algorithm>
#include<stack>
#define INF 999999
using namespace std;
//�Զ���ṹ�� 
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
	char (*vexname)[20];//��Ŷ������ֵĶ�ά��̬����������ָ�룩 
	AR *N;//�������ͷ�ڵ������������̬���飩
}GH;

//ȫ�ֱ���
char filename[30];
stack<int> T;
int *ve,*vl;

//�������� 
void PrintGraph(GH *G); 			//��ӡ����ͼ 
void CreateGraph(GH *&G,int type);	//����ͼ 
int FindIndex(GH *G,char *name);	//���ض������ƶ�Ӧ����� 
bool TopologicalOrder(GH *G,stack<int> &T);//�������򣬲��������翪ʼʱ�� 
bool CriticalPath(GH *G);			//�ؼ�·�� 

//������ 
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
bool TopologicalOrder(GH *G,stack<int> &T)
{
	int *indegree,count = 0;
	indegree = new int[G->vexnum + 1];	//ͳ����ȵ����� 
	ve = new int[G->vexnum + 1];	//���翪ʼʱ������� 
	for(int i = 0;i<G->vexnum;i++) indegree[i] = ve[i] = 0;
	for(int i = 0;i<G->vexnum;i++)	//����ͼ��ͳ����� 
	{
		arcnode *t = G->N[i].next;
		while(t)
		{
			indegree[t->index]++;
			t = t->next;
		}
	}
	stack<int> s;	//�������� 
	for(int i = 0;i<G->vexnum;i++)	//���Ϊ0��ջ 
		if(!indegree[i])s.push(i); 
	while(!s.empty())		//ջ��Ϊ�� 
	{
		int j = s.top();
		T.push(j);
		s.pop();
		count++;
		for(arcnode *t = G->N[j].next;t;t = t->next)
		{
			if(--indegree[t->index] == 0) s.push(t->index);	//ɾ��ջ���ĵ㣬���¼�����Ȳ���ջ 
			if(ve[j] + t->weight > ve[t->index]) ve[t->index] = ve[j] + t->weight;//�������翪ʼʱ�� 
		}
	}
	if(count<G->vexnum)return false;	//�����������Ľڵ㲻���ܽڵ���������ڻ�· 
	return true;
}
bool CriticalPath(GH *G)
{
	if(!TopologicalOrder(G,T)) return false;	//�����������ʧ���򷵻� 
	int ee,el;
	vl = new int[G->vexnum + 1];	//����ʼʱ������ 
	//����ʼʱ�䶼�������ڵ�����翪ʼʱ�� 
	for(int i = 0;i<G->vexnum;i++) vl[i] = ve[G->vexnum-1];	
	while(!T.empty())		//������˳�� 
	{
		int j = T.top();
		T.pop();
		for(arcnode *t = G->N[j].next;t;t = t->next)	//��������ʼʱ�� 
		{
			if(vl[t->index] - t->weight < vl[j]) vl[j] = vl[t->index] - t->weight; 
		}
	}
	for(int i = 0;i<G->vexnum;i++)		//����ÿ���ߣ��������������ʼʱ���Ƿ���� 
	{
		for(arcnode *t = G->N[i].next;t;t = t->next)
		{
			ee = ve[i];el = vl[t->index] - t->weight;
			cout<<G->vexname[i]<< " "<<G->vexname[t->index]<<" "<<t->weight<<" "
				<<ee<<" "<<el<<" "<<(ee==el?'*':' ')<<endl;	//���*����������ǹؼ�·�� 
		}
	}
	return true; 
}



