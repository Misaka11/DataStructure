#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
ifstream fin;

typedef struct node
{
    char data;
    struct node *fir,*sib;
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
			CreateBT(T->fir);
			CreateBT(T->sib);
		}
	}
}
void ShowBT(BT *T)
{
	if(!T) return;
	cout<<T->data;
	if(T->fir)
	{
		cout<<'(';
		ShowBT(T->fir);
		cout<<')';
	}
	if(T->sib)
	{
		cout<<',';
		ShowBT(T->sib);
	}

}
void AllPath(BT *T,char *path,int depth)
{
	if(!T) return;
	if(!T->fir)
	{
		for(int i = 0;i<depth;i++)
			cout<<path[i]<<"¡ú";
		cout<<T->data<<endl;
	}
	path[depth] = T->data;
	AllPath(T->fir,path,depth+1);
	path[depth] = '\0';
	AllPath(T->sib,path,depth);
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
		if(!t.T->fir)
		{
			for(int i = 0;i<top - 1;i++)
				cout<<Stack[i].T->data<<"¡ú";
			cout<<t.T->data<<endl;
			t.mark = 1;
		}
		switch (t.mark++)
		{
		case 0: if(t.T->fir)
				{
					Stack[top].T = t.T->fir;
					Stack[top].mark = 0;
					top++;
				}break;
		case 1: if(t.T->sib)
				{
					top--;
					Stack[top].T = t.T->sib;
					Stack[top].mark = 0;
					top++;
				}
				else top--;
				break;
		} 
	}
}

int main()
{
	BT *root = NULL;
	fin.open("BT2.txt");
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
