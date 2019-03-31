#include<iostream>
#include<time.h>
#include<stdlib.h>
using namespace std;
#define LH 1	//左高 
#define EH 0	//等高 
#define RH -1	//右高 

typedef struct BSTNode
{
	int data;
	int bf;				//节点的平衡因子 
	BSTNode *left,*right;
}BSTNode,*BSTree;

BSTree CreateBST(int n);						//创建n个元素的二叉平衡树 
void ShowBST(BSTree T);							//显示平衡树 
void R_Rotate(BSTree &p);						//右旋 
void L_Rotate(BSTree &p);						//左旋 
bool InsertAVL(BSTree &T,int e,bool &taller);	//插入新数据e 
void LeftBalance(BSTree &T);					//调节左平衡 
void RightBalance(BSTree &T);					//调节右平衡 


int main()
{
	BSTree T;
	int N;
	cout<<"输入数据的个数N = ";
	cin>>N;
	T = CreateBST(N);
	cout<<"建立的二叉平衡树为：\n";
	ShowBST(T);
	return 0; 
} 

BSTree CreateBST(int n)
{
	srand(time(0));
	bool taller;
	BSTree T = NULL;
	cout<<"下面是生成的N个随机数据\n";
	for(int i = 0;i<n;i++)
	{
		int data = rand()%60;
		cout<<data<<" ";
		InsertAVL(T,data,taller);
	}
	cout<<endl<<endl; 
	return T;
}

void ShowBST(BSTree T)
{
	if(!T) return;
	cout<<T->data;
	if(T->left || T->right)
		{
			cout<<'(';
			ShowBST(T->left);
			cout<<',';
			ShowBST(T->right);
			cout<<')';
		}
}
void R_Rotate(BSTree &p)
{
	BSTNode *lc = p->left;
	p->left = lc->right;
	lc->right = p;
	p = lc;
}
void L_Rotate(BSTree &p)
{
	BSTNode *rc = p->right;
	p->right = rc->left;
	rc->left = p;
	p = rc;
}
bool InsertAVL(BSTree &T,int e,bool &taller)
{
	if(!T)
	{
		T = new BSTNode;T->data = e;
		T->left = T->right = NULL;
		T->bf = EH;
		taller = true;
	}
	else
	{
		if(e == T->data){taller = false; return 0;}
		if(e < T->data)
		{
			if(!InsertAVL(T->left,e,taller)) return 0;
			if(taller)
			switch(T->bf)
			{
				case LH:
					LeftBalance(T);taller = false;break;
				case EH:
					T->bf = LH;taller = true;break;
				case RH:
					T->bf = EH;taller = false;break;
			}
		}
		else
		{
			if(!InsertAVL(T->right,e,taller)) return 0;
			if(taller)
			switch(T->bf)
			{
				case LH:
					T->bf = EH;taller = false;break;
				case EH:
					T->bf = RH;taller = true;break;
				case RH:
					RightBalance(T);taller = false;break;
			}
		}
	}
	return 1;
}
void LeftBalance(BSTree &T)
{
	BSTNode *lc = T->left;
	switch(lc->bf)
	{
		case LH:
			T->bf = lc->bf = EH;
			R_Rotate(T);break;
		case RH:
			BSTNode *rd = lc->right;
			switch(rd->bf)
			{
				case LH:T->bf = RH;lc->bf = EH;break;
				case EH:T->bf = lc->bf = EH;break;
				case RH:T->bf = EH; lc->bf = LH;break;
			} 
			rd->bf = EH;
			L_Rotate(T->left);
			R_Rotate(T);
	} 
}
void RightBalance(BSTree &T)
{
	BSTNode *rc = T->right;
	switch(rc->bf)
	{
		case RH:
			T->bf = rc->bf = EH;
			L_Rotate(T);break;
		case LH:
			BSTNode *ld = rc->left;
			switch(ld->bf)
			{
				case LH:T->bf = LH;rc->bf = EH;break;
				case EH:T->bf = rc->bf = EH;break;
				case RH:T->bf = EH; rc->bf = RH;break;
			} 
			ld->bf = EH;
			R_Rotate(T->right);
			L_Rotate(T);
		
	} 
}






//9-11 利用随机数创建一个平衡的二叉排序树。

