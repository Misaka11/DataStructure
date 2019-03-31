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
bool Find(BT *T,char r,char s)
{
	if(!T) return 0;
	if(T->data == r)return 1;
	if(T->data == s)return 1;
	bool left = Find(T->left,r,s);
	bool right = Find(T->right,r,s);
	if(left && right) cout<<T->data<<endl;
	return left || right;
}

void Find_Stack(BT *T,char r,char s)
{
	struct pp
	{
		BT *T;
		int have;
		int mark;
	};
	pp stack[30];
	int top = 0;
	stack[0].T = T;
	stack[0].have = 0;
	stack[0].mark = 0;
	while(top >= 0)
	{
		pp &t = stack[top];
		if(!t.T)
		{
			top--;
			continue;
		}//cout<<t.T->data<<" ";
		if(t.have >= 2)
		{
			cout<<t.T->data<<endl;
			return;
		}
		switch(t.mark++)
		{
			case 0:
				top++;
				stack[top].T = t.T->left;
				stack[top].have = 0;
				stack[top].mark = 0;
				break;
			case 1:
				top++;
				stack[top].T = t.T->right;
				stack[top].have = 0;
				stack[top].mark = 0;
				break;
			case 2:
				if((t.T->data == r || t.T->data == s || t.have > 0) && top >0)
					stack[top - 1].have++;
				top--;
				break;
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
	char r,s;
	cout<<"r = ";
	cin>>r;
	cout<<"s = ";
	cin>>s;
	Find(root,r,s);
	Find_Stack(root,r,s);
	getchar();getchar();
	return 0;
}
