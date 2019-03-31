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
	Triple data[MAXSIZE + 1];	//������Ԫ���data[0]δ��
	int mu,nu,tu;	//����������������ͷ���Ԫ����
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
	cout<<"\nԭ����Q:\n";
	ShowSMatrix(Q);
	AddSMatrix(M,N,Q);
	cout<<"\nQ=M+N��Q:\n";
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
		cout<<"����Ԫ�����������ʧ��"<<endl;
		return false;
	}
	if(i > M.mu || j > M.nu)
	{
		cout<<"������������"<<endl;
		return false;
	}
	Triple t;
	t.i = i;t.j = j;t.e = e;
	int p;			//��־��Ԫ��Ӧ�ò����λ��  
    if(M.tu==0)			//����ǰ����Mû�з���Ԫ��
	{  
		M.data[++M.tu] = t;
        return true;  
    }  
    for(p = 1;p<=M.tu;p++)	//Ѱ�Һ��ʵĲ���λ��  
		if((M.data[p].i > i) || (M.data[p].i == i && M.data[p].j > j)) break;
    for(int k=M.tu;k>=p;k--)		//�ƶ�p֮���Ԫ�� 
        M.data[k+1]=M.data[k]; 
    //������Ԫ��  
	M.data[p] = t; 
	M.tu++;
    return true;  
}
void ShowSMatrix(TSMatrix &M)
{
	if(M.tu == 0)
	{	
		cout<<"�þ���Ϊ��"<<endl;
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
