#include<iostream>
#include<time.h>
#include<stdlib.h>
using namespace std;
#define N 10

typedef struct node
{
	int data;
	node *left,*right;
}*BST;

BST root;

BST CreateBST();
bool SearchBST(BST T,int x,BST f,BST &p);
bool InsertBST(BST &T,int x);
bool DeleteBST(BST &T,int x);
void ShowBST(BST T);

int main()
{
	srand(time(0));
	root = CreateBST();
	ShowBST(root);
	cout<<endl;
	int x;
	cout<<"输入要删除的数：";
	cin>>x;
	if(DeleteBST(root,x)) cout<<"删除成功\n";
	else cout<<"没有找到该数据\n";
	ShowBST(root);
	return 0;
}


BST CreateBST()
{
	int x;
	BST root = NULL;
	cout<<"随机生成的数据为："<<endl;
	for(int i = 0;i<N;i++)
	{
		x = rand() % 30;
		cout<<x<<" ";
		InsertBST(root,x);
	}
	cout<<endl;
	return root;
}

bool SearchBST(BST T,int x,BST f,BST &p)
{
	if(!T)
	{
		p = f;return false;
	}
	else if(x == T->data)
	{
		p = T;return true;
	}
	else if(x < T->data) return SearchBST(T->left,x,T,p);
	else return SearchBST(T->right,x,T,p);
}
bool InsertBST(BST &T,int x)
{
	BST p,t;
	if(!SearchBST(T,x,NULL,p))
	{
		t = new node;
		t->data = x;
		t->left = t->right = NULL;
		if(!p) T = t;
		else if(x < p->data) p->left = t;
		else p->right = t;
		return true;
	}
	else return false;	//已有相同的节点 
}
bool DeleteBST(BST &T,int x)
{
	if(!T) return false;
	else
	{
		if(x == T->data)
		{
			if(!T->right)	//右子树为空，只要重接左子树 
			{
				BST q = T;
				T = T->left;
				delete q;
			}
			else if(!T->left)	//左子树为空，只要重接右子树 
			{
				BST q = T;
				T = T->right;
				delete q;
			}
			else			//左右都不为空 
			{
				BST q = T;
				BST s = T->left;
				while(s->right)			//转左，然后向右走到尽头 
				{
					q = s; s = s->right;
				}
				T->data = s->data;		//s指向被删节点的前驱 
				if(q != T) q->right = s->right;	//重接q的右子树 
				else q->left = s->left;			//重接q的左子树 
				delete s;
			}
			return true;
		}
		else if(x < T->data) return DeleteBST(T->left,x);
		else return DeleteBST(T->right,x);
	}
}
void ShowBST(BST T)
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
/*9-7利用随机数创建一个BST，显示该BST，
然后随机生成一个数，如果该数据存在，
则将它从BST中删除，并显示删除后的BST*/
