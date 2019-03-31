#include<iostream>
#include<fstream>
#include<string.h> 
using namespace std;
#define N 15
int g[N][N];
struct
{
	int index,pre,step;
}que[50];
bool visit[N];
int path[N];

void CreateGraph(char *filename)
{
	int n,u,v;
	ifstream fin;
	fin.open(filename,ios::in);
	if(fin.fail())
	{
		cout<<"δ�ҵ����ļ�"<<endl;
		exit(0);
	}
	fin>>n;
	while(fin>>u>>v)
	{
		g[u][v] = 1;
		g[v][u] = 1;
	}
	fin.close();
}
void Print(int r)
{
	if(r != -1)
	{
		Print(que[r].pre);
		cout<<que[r].index<<" ";
	}
}
//���������· 
void bfs(int s,int t)
{
	que[0].index = s;
	que[0].pre = -1;
	que[0].step = 0;
	for(int i = 0;i<N;i++)visit[i] = 0;
	visit[s] = 1;
	int f=0,r=1;
	while(f<r)
	{
		bool flag = false;
		for(int i = 0;i<N;i++)
			if(g[que[f].index][i] && !visit[i])
			{
				que[r].index = i;
				que[r].pre = f;
				que[r].step = que[f].step + 1;
				visit[i] = 1;
				if(i == t)
				{
					Print(r);
					cout<<endl;
					return;
				} 
				r++;
				
			}
		f++;
	}
}
//������� 
void dfs(int index,int depth)
{
	if(index == 14)	//�����յ㣬���·���Ƿ�������� 
	{
		bool y1 = false,y2 = false,y3 = false,y4 = false;
		for(int i = 0;i<depth;i++)
		{
			if(path[i] == 1) y1 = true;
			if(path[i] == 6) y2 = true;
			if(path[i] == 7) y3 = true;
			if(path[i] == 9) y4 = true;
		}
		if((y1||y2) && !y3 && !y4)
		{	for(int i = 0;i<depth;i++)
				cout<<path[i]<<"->";
			cout<<index<<endl;
		}
		return;
	}
	visit[index] = 1;
	path[depth] = index;
	for(int i = 0;i<N;i++)
		if(g[index][i] && !visit[i])
			dfs(i,depth + 1);
	visit[index] = 0;
}
int main()
{
	char filename[30];
	cout<<"�������ļ�����";
	cin>>filename;
	CreateGraph(filename);
	cout<<"���Ϊv0,�յ�Ϊv14��������б��뾭����v1��v6�������ܾ���v7��v9��·�����£�\n";
	dfs(0,0);
	cout<<"���Ϊv0,�������v6�����յ�v14��һ�����·�����£�\n";
	bfs(0,6);
	bfs(6,14);
	system("pause");
	return 0;
}
