#include<iostream>
#include<fstream>
#include<cstring>
#define MAXNUM 10000
using namespace std;
//�����ļ���ȡ 
ifstream fin;
char filename[20];
//���Ľڵ� 
typedef struct node
{
    char data;
    struct node *left,*right;
}*BT;
//�����õ�ջ 
struct 
{
	BT t;
	int mark;
	}stack[MAXNUM];
int top = -1;
void push(BT t)	//ѹջ���� 
{
	if(!t) return;
	top++;
	stack[top].t = t;
	stack[top].mark = 0;		
}
//���򴴽��� 
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
//������������������������� 
//1.���������������ַ���s��start��end���ַ� 
string copy(string s,int start,int end)
{
	string t = "";
	if(start >= s.length()) return t;
	if(end >= s.length()) end = s.length() - 1;
	for(int i = start;i<=end;i++)
		t += s[i];
	return t;
}
//2.�������� 
BT CreateBT2(string pre,string mid)
{
	if(pre == "" && mid == "" ) return NULL;	//�սڵ� 
	//�������� 
	int i; 
	int plen = pre.length();
	int mlen = mid.length();
	//�ҵ����ڵ����������е�λ��i 
	for(i = 0;i<mlen;i++)
		if(mid[i] == pre[0]) break;
	if(i == mlen) return NULL;	//û�ҵ�����NULL 
	BT root  = new node;		
	root->data = pre[0];		//�µĸ��ڵ㴢���ַ� 
	root->left = CreateBT2(copy(pre,1,i),copy(mid,0,i-1));	//������������ͬ���� 
	root->right = CreateBT2(copy(pre,i+1,plen),copy(mid,i+1,mlen));//������������ͬ���� 
	return root;
}
//�ݹ���ʾ�� 
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
//�����ĸ߶� 
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
//ͨ����α��������Ŀ�� 
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
//���ܽڵ��� 
int nodenum(BT T)
{
	if(T) return nodenum(T->left)+nodenum(T->right)+1;
	else return 0;
}
//��Ҷ�ӽڵ��� 
int yezinum(BT T)
{
	if(!T) return 0;
	if(T->left == NULL && T->right == NULL) return 1;
	return yezinum(T->left) + yezinum(T->right);
}
//�ж��Ƿ�Ϊ��ȫ������ 
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
		//���һ���ڵ�û���ӽڵ�;ֻҪ�����˿������Ľڵ㣬
		//������ֵı���ΪҶ�ӽڵ㣨����������������Ϊ�գ�  
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
//�����ڵ���������� 
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
//������ 
void DestroyBT(BT T)
{
	if(T)
	{
		DestroyBT(T->left);
		DestroyBT(T->right);
		delete T;
	}
}
//ջ���������򣬺��򣬲�α��� 
void visit(BT T)
{
	//preorder
	cout<<"\n���������";
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
	cout<<"\n���������";
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
	cout<<"\n���������";
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
	//��α���
	cout<<"\n��α�����";
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
//�����ļ���ȡ�ĺ��� 
bool openfile()
{
	cout<<"�������ļ�����\n";
	cin>>filename;
	fin.open(filename,ios::in);
	if(fin.fail())
	{
		cout<<"�ļ�δ�ҵ�\n";
		return false;
	}
	return true;
}
bool closefile()
{
	fin.close();
	return false; 
}
//���˵� 
int menu()
{
	char i;
	do{
		system("cls"); 
		cout<<"1.����������������\n";
		cout<<"2.����������������������Ľ����\n";
		cout<<"3.��ʾ������\n";
		cout<<"4.��ʾ������������\n";
		cout<<"5.���ı���\n";
		cout<<"6.������������\n";
		cout<<"7.���ٶ�����\n";
		cout<<"8.�˳�\n"; 
		cout<<"��ѡ��";
		i=getchar();
		setbuf(stdin, NULL);//��ջ����� 
	}while(i<'0' || i>'8');
	return (i-'0');	
}
//������ 
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
					cout<<"�������\n";
				}
				closefile();
				break;
			case 2:
				if(openfile())
				{
					string pre,mid;
					fin>>pre>>mid;
					root = CreateBT2(pre,mid);
					cout<<"�������\n";
				}
				closefile();
				break;
			case 3:	ShowBT(root);break;
			case 4:cout<<"\n �ܽڵ�����"<<nodenum(root)
					<<"\n Ҷ�ӽڵ�����"<<yezinum(root)
					<<"\n �߶ȣ�"<<depth(root)
					<<"\n ��ȣ�"<<width(root)
					<<"\n �Ƿ�Ϊ��ȫ��������";
					if(wanquan(root))cout<<"��\n";
					else cout<<"��\n"; 
					break;
			case 5:visit(root);break;
			case 6:cout<<"������Ҫ�������������Ľڵ㣺";
				   char c;
				   cin>>c;
				   if(exchange(root,c)) cout<<"�����ɹ�\n";
				   else cout<<"û�ҵ��ڵ�\n";
				   break;
			case 7:DestroyBT(root);root = NULL;
				   cout<<"���ٳɹ�\n";
				   break;
			case 8:exit = true;break;
		}
		system("pause");
	}
	return 0;
}
