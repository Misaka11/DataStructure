#include<iostream>
#include<fstream>
#include<cstring>
#define MAXNUM 10000
using namespace std;
//用于文件读取 
ifstream fin;
char filename[20];
//树的节点 
typedef struct node
{
    char data;
    struct node *left,*right;
}*BT;
//遍历用的栈 
struct 
{
	BT t;
	int mark;
	}stack[MAXNUM];
int top = -1;
void push(BT t)	//压栈函数 
{
	if(!t) return;
	top++;
	stack[top].t = t;
	stack[top].mark = 0;		
}
//先序创建树 
void CreateBT1(BT &T)
{
	char c;
	if(fin>>c)
	{
		if(c  == '#')
			T = NULL;
		else
		{
			T = new node;
			T->data = c;
			CreateBT1(T->left);
			CreateBT1(T->right);
		}
	}
	else T = NULL;
}
//根据中序和先序遍历结果创建树 
//1.辅助函数，复制字符串s从start到end的字符 
string copy(string s,int start,int end)
{
	string t = "";
	if(start >= s.length()) return t;
	if(end >= s.length()) end = s.length() - 1;
	for(int i = start;i<=end;i++)
		t += s[i];
	return t;
}
//2.创建函数 
BT CreateBT2(string pre,string mid)
{
	if(pre == "" && mid == "" ) return NULL;	//空节点 
	//辅助变量 
	int i; 
	int plen = pre.length();
	int mlen = mid.length();
	//找到根节点在中序结果中的位置i 
	for(i = 0;i<mlen;i++)
		if(mid[i] == pre[0]) break;
	if(i == mlen) return NULL;	//没找到返回NULL 
	BT root  = new node;		
	root->data = pre[0];		//新的根节点储存字符 
	root->left = CreateBT2(copy(pre,1,i),copy(mid,0,i-1));	//对左子树做相同操作 
	root->right = CreateBT2(copy(pre,i+1,plen),copy(mid,i+1,mlen));//对右子树做相同操作 
	return root;
}
//递归显示树 
void ShowBT(BT T)
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
//求数的高度 
int depth(BT T)
{
	if(!T) return 0;
	else 
	{
		int d1 = depth(T->left);
		int d2 = depth(T->right);
		if(d1>=d2) return d1 + 1;
		else return d2 + 1;	
	}
}
//通过层次遍历求树的宽度 
int width(BT T)
{
	if(!T) return 0;
	BT q[MAXNUM];
	int h = 0,r = 0;
	q[r++] = T;
	int lastw = 1;
	int nwidth = 1;
	int curw = 0;
	while(h<r)
	{
		int templastw = lastw;
		while(templastw > 0)
		{
			if(q[h]->left)
				q[r++] = q[h]->left;
			if(q[h]->right)
				q[r++] = q[h]->right;
			templastw--;
			h++;
		}
		curw = r - h;
		nwidth = curw > nwidth ? curw : nwidth;
		lastw = curw;
	}
	return nwidth;
}
//求总节点数 
int nodenum(BT T)
{
	if(T) return nodenum(T->left)+nodenum(T->right)+1;
	else return 0;
}
//求叶子节点数 
int yezinum(BT T)
{
	if(!T) return 0;
	if(T->left == NULL && T->right == NULL) return 1;
	return yezinum(T->left) + yezinum(T->right);
}
//判断是否为完全二叉树 
bool wanquan(BT T)
{
	if(!T) return false;
	BT q[MAXNUM];
	int h = 0,r = 0;
	q[r++] = T;
	bool mustHaveNoChild = false; 
	while(h<r)
	{
		if (mustHaveNoChild)
		//如果一个节点没有子节点;只要出现了空子树的节点，
		//后面出现的必须为叶子节点（左字树右子树必须为空）  
        {  
            if (q[h]->left|| q[h]->right)  
            	return false;
        }  
        else  
        {  
            if (q[h]->left && q[h]->right)  
            {  
                q[r++] = q[h]->left;
                q[r++] = q[h]->right; 
            }  
            else if (q[h]->left && !q[h]->right)  
            {  
                mustHaveNoChild = true;  
                q[r++] = q[h]->left;
            }  
            else if(!q[h]->left && q[h]->right)  
            {  
                return false;
            }  
            else  
            {  
                mustHaveNoChild = true;  
            }  
        }  
		h++;
	}
	return true;
}
//交换节点的左右子树 
bool exchange(BT T,char c)
{
	if(!T)return false;
	else
	{
		if(T->data == c)
		{
			BT temp = T->left;
			T->left = T->right;
			T->right = temp;
			return true;
		}
		else return exchange(T->left,c) || exchange(T->right,c);
	}
}
//销毁树 
void DestroyBT(BT T)
{
	if(T)
	{
		DestroyBT(T->left);
		DestroyBT(T->right);
		delete T;
	}
}
//栈的先序，中序，后序，层次遍历 
void visit(BT T)
{
	//preorder
	cout<<"\n先序遍历：";
	push(T);
	while(top >= 0)
	{
		switch(stack[top].mark++)
		{
			case 0:cout<<stack[top].t->data<<" ";break;
			case 1:push(stack[top].t->left);break;
			case 2:push(stack[top].t->right);break;
			case 3:top--;break;
		}
	}
	//Inorder
	cout<<"\n中序遍历：";
	push(T);
	while(top >= 0)
	{
		switch(stack[top].mark++)
		{
			case 0:push(stack[top].t->left);break;
			case 1:cout<<stack[top].t->data<<" ";break;
			case 2:push(stack[top].t->right);break;
			case 3:top--;break;
		}
	}
	//postorder
	cout<<"\n后序遍历：";
	push(T);
	while(top >= 0)
	{
		switch(stack[top].mark++)
		{
			case 0:push(stack[top].t->left);break;
			case 1:push(stack[top].t->right);break;
			case 2:cout<<stack[top].t->data<<" ";break;
			case 3:top--;break;
		}
	}
	//层次遍历
	cout<<"\n层次遍历：";
	BT q[MAXNUM];
	int h = 0,r = 0;
	q[r++] = T;
	int lastw = 1;
	while(h<r)
	{
		int templastw = lastw;
		cout<<endl;
		while(templastw > 0)
		{
			cout<<q[h]->data<<" ";
			if(q[h]->left)
				q[r++] = q[h]->left;
			if(q[h]->right)
				q[r++] = q[h]->right;
			templastw--;
			h++;
		}
		lastw = r - h;
	}
	cout<<endl;
}
//用于文件读取的函数 
bool openfile()
{
	cout<<"请输入文件名：\n";
	cin>>filename;
	fin.open(filename,ios::in);
	if(fin.fail())
	{
		cout<<"文件未找到\n";
		return false;
	}
	return true;
}
bool closefile()
{
	fin.close();
	return false; 
}
//主菜单 
int menu()
{
	char i;
	do{
		system("cls"); 
		cout<<"1.创建二叉树（先序）\n";
		cout<<"2.创建二叉树（中序与先序的结果）\n";
		cout<<"3.显示二叉树\n";
		cout<<"4.显示二叉树的属性\n";
		cout<<"5.树的遍历\n";
		cout<<"6.交换左右子树\n";
		cout<<"7.销毁二叉树\n";
		cout<<"8.退出\n"; 
		cout<<"请选择：";
		i=getchar();
		setbuf(stdin, NULL);//清空缓冲区 
	}while(i<'0' || i>'8');
	return (i-'0');	
}
//主函数 
int main()
{
	BT root = NULL;
	bool exit = false;
	while(!exit)
	{
		switch(menu())
		{	system("cls");
			case 1:	
				if(openfile())
				{
					CreateBT1(root);
					cout<<"创建完成\n";
				}
				closefile();
				break;
			case 2:
				if(openfile())
				{
					string pre,mid;
					fin>>pre>>mid;
					root = CreateBT2(pre,mid);
					cout<<"创建完成\n";
				}
				closefile();
				break;
			case 3:	ShowBT(root);break;
			case 4:cout<<"\n 总节点数："<<nodenum(root)
					<<"\n 叶子节点数："<<yezinum(root)
					<<"\n 高度："<<depth(root)
					<<"\n 宽度："<<width(root)
					<<"\n 是否为完全二叉树：";
					if(wanquan(root))cout<<"是\n";
					else cout<<"否\n"; 
					break;
			case 5:visit(root);break;
			case 6:cout<<"请输入要交换左右子树的节点：";
				   char c;
				   cin>>c;
				   if(exchange(root,c)) cout<<"交换成功\n";
				   else cout<<"没找到节点\n";
				   break;
			case 7:DestroyBT(root);root = NULL;
				   cout<<"销毁成功\n";
				   break;
			case 8:exit = true;break;
		}
		system("pause");
	}
	return 0;
}
