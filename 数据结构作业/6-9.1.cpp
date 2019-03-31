#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
ifstream fin;

typedef struct node
{
    char data;
    struct node *left,*right;
}BT;

void CreateBT(BT *&T)
{
	char c;
	if(fin>>c)
	{
		if(c  == '#')
			T = NULL;
		else
		{
			T = new BT;
			T->data = c;
			CreateBT(T->left);
			CreateBT(T->right);
		}
	}
}
void ShowBT(BT *T)
{
	if(!T) return;
	cout<<T->data;
	if(T->left || T->right)
		{
			cout<<'(';
			ShowBT(T->left);
			cout<<',';
			ShowBT(T->right);
			cout<<')';
		}
}
void AllPath(BT *T,char *path,int depth)
{
	if(!T) return;
	if(!T->left && !T->right)
	{
		for(int i = 0;i<depth;i++)
			cout<<path[i]<<"¡ú";
		cout<<T->data<<endl;
	}
	else
	{
		path[depth] = T->data;
		AllPath(T->left,path,depth+1);
		AllPath(T->right,path,depth+1);
	}
}
void AllPath_Stack(BT *root)
{
	struct pp{
		BT *T;
		int mark;
	}Stack[100];
	int top = 0;
	Stack[top].T = root;
	Stack[top].mark = 0;
	top++;
	while(top > 0)
	{
		pp &t = Stack[top - 1];
		if(!t.T->left && !t.T->right)
		{
			for(int i = 0;i<top -1;i++)
				cout<<Stack[i].T->data<<"¡ú";
			cout<<t.T->data<<endl;
			top--;
		}
		else
		switch (t.mark++)
		{
		case 0: if(t.T->left)
				{
					Stack[top].T = t.T->left;
					Stack[top].mark = 0;
					top++;
				}break;
		case 1: if(t.T->right)
				{
					Stack[top].T = t.T->right;
					Stack[top].mark = 0;
					top++;
				}break;
		default:
			top--;
		} 
	}
}

int main()
{
	BT *root = NULL;
	fin.open("BT1.txt");
	CreateBT(root);
	fin.close();
	ShowBT(root);
	cout<<endl;
	char path[100];
	AllPath(root,path,0);
	AllPath_Stack(root);
	getchar();
	return 0;
}
