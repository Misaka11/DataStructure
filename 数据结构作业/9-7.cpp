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
	cout<<"����Ҫɾ��������";
	cin>>x;
	if(DeleteBST(root,x)) cout<<"ɾ���ɹ�\n";
	else cout<<"û���ҵ�������\n";
	ShowBST(root);
	return 0;
}


BST CreateBST()
{
	int x;
	BST root = NULL;
	cout<<"������ɵ�����Ϊ��"<<endl;
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
	else return false;	//������ͬ�Ľڵ� 
}
bool DeleteBST(BST &T,int x)
{
	if(!T) return false;
	else
	{
		if(x == T->data)
		{
			if(!T->right)	//������Ϊ�գ�ֻҪ�ؽ������� 
			{
				BST q = T;
				T = T->left;
				delete q;
			}
			else if(!T->left)	//������Ϊ�գ�ֻҪ�ؽ������� 
			{
				BST q = T;
				T = T->right;
				delete q;
			}
			else			//���Ҷ���Ϊ�� 
			{
				BST q = T;
				BST s = T->left;
				while(s->right)			//ת��Ȼ�������ߵ���ͷ 
				{
					q = s; s = s->right;
				}
				T->data = s->data;		//sָ��ɾ�ڵ��ǰ�� 
				if(q != T) q->right = s->right;	//�ؽ�q�������� 
				else q->left = s->left;			//�ؽ�q�������� 
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
/*9-7�������������һ��BST����ʾ��BST��
Ȼ���������һ��������������ݴ��ڣ�
������BST��ɾ��������ʾɾ�����BST*/
