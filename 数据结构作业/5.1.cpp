#include<iostream>
#include<cstring>
#define MAXSIZE 50
using namespace std;

struct Triple
{
	int i,j,e;
};
struct TSMatrix
{
	Triple data[MAXSIZE + 1];	//非零三元组表，data[0]未用
	int mu,nu,tu;	//矩阵的行数，列数和非零元个数
};

TSMatrix M,N,Q;

void Init();
void CreateSMatrix(TSMatrix &M,int m,int n);
bool AddData(TSMatrix &M,int i,int j,int e);
void ShowSMatrix(TSMatrix &M);
void AddSMatrix(TSMatrix &M,TSMatrix &N,TSMatrix &Q);

int main()
{
	Init();
	cout<<"M:\n";
	ShowSMatrix(M);
	cout<<"\nN:\n";
	ShowSMatrix(N);
	cout<<"\n原来的Q:\n";
	ShowSMatrix(Q);
	AddSMatrix(M,N,Q);
	cout<<"\nQ=M+N，Q:\n";
	ShowSMatrix(Q);
	getchar();getchar();
	return 0;
}

void Init()
{
	CreateSMatrix(M,3,4);
	CreateSMatrix(N,3,4);
	CreateSMatrix(Q,3,4);
	AddData(M,1,2,3);
	AddData(M,2,2,-1);
	AddData(M,3,1,9);
	AddData(M,2,4,12);
	AddData(N,1,4,4);
	AddData(N,2,2,1);
	AddData(N,2,3,5);
	AddData(N,3,1,2);
	AddData(N,3,2,-6);
}
void CreateSMatrix(TSMatrix &M,int m,int n)
{
	M.mu = m;
	M.nu = n;
	M.tu = 0;
}
bool AddData(TSMatrix &M,int i,int j,int e)
{
	if(M.tu + 1 > MAXSIZE)
	{
		cout<<"矩阵元素已满，添加失败"<<endl;
		return false;
	}
	if(i > M.mu || j > M.nu)
	{
		cout<<"输入数据有误"<<endl;
		return false;
	}
	Triple t;
	t.i = i;t.j = j;t.e = e;
	int p;			//标志新元素应该插入的位置  
    if(M.tu==0)			//插入前矩阵M没有非零元素
	{  
		M.data[++M.tu] = t;
        return true;  
    }  
    for(p = 1;p<=M.tu;p++)	//寻找合适的插入位置  
		if((M.data[p].i > i) || (M.data[p].i == i && M.data[p].j > j)) break;
    for(int k=M.tu;k>=p;k--)		//移动p之后的元素 
        M.data[k+1]=M.data[k]; 
    //插入新元素  
	M.data[p] = t; 
	M.tu++;
    return true;  
}
void ShowSMatrix(TSMatrix &M)
{
	if(M.tu == 0)
	{	
		cout<<"该矩阵为空"<<endl;
		return;
	}
	int i,j,p = 1;
	for(i = 1;i<=M.mu;i++)
	{	
		for(j = 1;j<=M.nu;j++)
			if(i == M.data[p].i && j == M.data[p].j)
				cout<<M.data[p++].e<<' ';
			else cout<<"0 ";
		cout<<endl;
	}
}
void AddSMatrix(TSMatrix &M,TSMatrix &N,TSMatrix &Q)
{
	int p = 1,q = 1;
	while(p<=M.tu && q <= N.tu)
	{
		if(M.data[p].i > N.data[q].i || (M.data[p].i == N.data[q].i && M.data[p].j > N.data[q].j))
		{
			AddData(Q,N.data[q].i,N.data[q].j,N.data[q].e);
			q++;
		}
		else if(M.data[p].i == N.data[q].i && M.data[p].j == N.data[q].j)
		{
			AddData(Q,M.data[p].i,M.data[p].j,M.data[p].e + N.data[q].e);
			p++;q++;
		}
		else
		{
			AddData(Q,M.data[p].i,M.data[p].j,M.data[p].e);
			p++;
		}
	}
	while(p<=M.tu)
	{
		AddData(Q,M.data[p].i,M.data[p].j,M.data[p].e);
		p++;
	}
	while(q<=N.tu)
	{
		AddData(Q,N.data[q].i,N.data[q].j,N.data[q].e);
		q++;
	}
}
