#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <conio.h>
using namespace std;
//学生的信息 
struct Student
{
	char name[20];
	float score; 
	char id[20];
};
//链表的一个节点 
struct node
{
  Student stu;
  node *next;
  node *pre;  
};
//head存放及格学生的信息，fail存放不及格学生的信息 
node *head,*fail;
//文件名 
char filename[20];
//临时变量 
char s[20];

void Create();					//创建记录 
void Push(node *h,Student &s); 	//将学生信息在链表中找到合适的位置放置 
void DisplayAll(node *h);		//显示函数 
void Insert();					//插入函数 
void Del(char *s);				//删除函数 s为姓名 
int Query(char *s);				//查询函数 
void BuKao();					//补考函数 
void Save();					//保存函数 
void Distory();					//销毁链表 
//菜单函数 
int menu_select()
{
	char i;
	do{
		system("cls");
		printf("1.创建纪录（从文件读入）\n");
		printf("2.显示所有记录\n");
		printf("3.插入一条记录\n");
		printf("4.删除一条记录\n");
		printf("5.输入补考成绩\n");
		printf("6.查询\n");	
		printf("7.保存\n");	
		printf("0.退出\n");
		printf("请输入选择序号(0-7):");
		i=getchar();		
	}while(i<'0' || i>'7');
	return (i-'0');	
}
//主函数 
int main()
{ 
    for(;;)
	{
		switch(menu_select())
		{
		case 1:
			cout<<"调用创建链表函数\n";
			Create();
			break;
		case 2:
			cout<<"及格学生的信息：\n";
			DisplayAll(head);
			cout<<"不及格学生的信息：\n";
			DisplayAll(fail);		
			break;
		case 3:
			printf("调用插入函数\n");
			Insert();		
			break;
		case 4:
			printf("调用删除函数\n");
			cout<<"输入删除学生姓名\n";
			cin>>s;
			Del(s);
			break;
		case 5:			    
			printf("调用补考函数 :\n");	
			BuKao();		
			break;		
		case 6:			    
			printf("调用查询函数\n");
			cout<<"输入查询学生姓名\n";
			cin>>s;
			Query(s);		
			break;
		case 7:
			printf("调用保存函数\n");
			Save();
			cout<<"保存成功\n";
			break;		  
		case 0:
			printf("再见\n");
			Distory();
			system("pause");
			exit(0);
		}
		system("pause");
	}
    return 0;    
}

void Create()
{
	//创建链表头 
	head = new node;
	head->next = head->pre = NULL;
	fail = new node;
	fail->next = fail->pre = NULL;
	//从文件读入 
	cout<<"请输入文件名:"<<endl;
	cin>>filename; 
    ifstream fin;
    fin.open(filename,ios::in);
    if(fin.fail())
    {
        cout<<"文件不存在"<<endl;
        exit(0);   
    }
    Student t;
    while(fin>>t.name>>t.score>>t.id)
    {   
        if(t.score < 60)		//根据分数是否及格存放信息 
            Push(fail,t); 
        else Push(head,t);
    }
    fin.close();
}
void Push(node *h,Student &s)
{
	node *p = h;
	while(p->next)		//寻找合适的位置插入 
	{
		if(strcmp(s.name,p->next->stu.name) == -1) break;
		else p = p->next;
	} 
	node *t = new node;		//创建新节点 
	strcpy(t->stu.id,s.id);
	strcpy(t->stu.name,s.name);
	t->stu.score = s.score;
	if(p->next)			//如果在表中插入 
	{
		p->next->pre = t;
		t->next = p->next;
		t->pre = p;
		p->next = t;
	}
	else				//如果在表尾插入 
	{
		p->next = t;
		t->pre = p;
		t->next = NULL;
	}
}
void DisplayAll(node *h)
{
	if(h == NULL || h->next == NULL)
	{
		cout<<"没有学生信息\n";
		return;
	}
	int num = 0;
	for(node *t = h->next;t != NULL; t = t->next)
	{
		num++;			//每10人一页 
		if(num>10)
		{
			cout<<"按任意键下一页\n";
			getch();
			num = 0;
			system("cls");
		}
		cout<<"姓名： "<<t->stu.name<<" , 成绩： "
			<<t->stu.score<<" , 学号： "<<t->stu.id
			<<endl;
	}

}
 
void Insert()
{
	Student t;
	cout<<"请依次输入学生的姓名 成绩 学号\n";
	cin>>t.name>>t.score>>t.id;
	if(strlen(t.id) != 9)			//检测学号是否合法 
	{
		cout<<"学号必须为长度为9且每一位都为数字，插入失败\n";
		return;
	}
	for(int i = 0;i < 9;i++)
		if(t.id[i] > '9' || t.id[i] < '0')
			{
				cout<<"学号必须为长度为9且每一位都为数字，插入失败\n";
				return;
			}
	if(t.score<60)		//根据分数是否及格存放信息 
		Push(fail,t);
	else Push(head,t);
	cout<<"插入成功！\n"; 
}
void Del(char *s)
{
	int num = Query(s);	//查询是否存在 
	if(num == 1)		//只存在一条记录 
	{
		for(node *t = head->next;t != NULL; t = t->next)
		if(strcmp(s,t->stu.name) == 0)
		{
			t->pre->next = t->next;
			if(t->next) t->next->pre = t->pre;
			free(t);
			cout<<"删除成功\n";
		}
		for(node *t = fail->next;t != NULL; t = t->next)
		if(strcmp(s,t->stu.name) == 0)
		{
			t->pre->next = t->next;
			if(t->next) t->next->pre = t->pre;
			free(t);
			cout<<"删除成功\n";
		}
	}
	else if(num>1)		//存在多条记录 
	{
		cout<<"请输入学号进行删除：\n";
		char id[20];
		cin>>id;
		for(node *t = head->next;t != NULL; t = t->next)
		if(strcmp(id,t->stu.id) == 0)
		{
			t->pre->next = t->next;
			if(t->next) t->next->pre = t->pre;
			free(t);
			cout<<"删除成功\n";
		}
		for(node *t = fail->next;t != NULL; t = t->next)
		if(strcmp(id,t->stu.id) == 0)
		{
			t->pre->next = t->next;
			if(t->next) t->next->pre = t->pre;
			free(t);
			cout<<"删除成功\n";
		}
	}
	else cout<<"查无此人\n";
}
int Query(char *s)
{//根据姓名查找，找到就计数器+1，并输出该记录 
	int num = 0;
	for(node *t = head->next;t != NULL; t = t->next)
		if(strcmp(s,t->stu.name) == 0)
		{
			num++;
			cout<<"姓名： "<<t->stu.name<<" , 成绩： "
				<<t->stu.score<<" , 学号： "<<t->stu.id
				<<endl;
		}
	for(node *t = fail->next;t != NULL; t = t->next)
		if(strcmp(s,t->stu.name) == 0)
		{
			num++;
			cout<<"姓名： "<<t->stu.name<<"成绩： "
				<<t->stu.score<<" , 学号： "<<t->stu.id
				<<endl;
		}
	return num;
}

void BuKao()
{
	cout<<"输入一条补考记录，包括学生姓名，补考成绩以及学号:\n";
	Student s;
	cin>>s.name>>s.score>>s.id;
	node *t;
	for(t = fail->next;t != NULL; t = t->next)	//在不及格链表中查找 
	if(strcmp(s.id,t->stu.id) == 0)break;
	if(t && t->stu.score < 60)				//找到并且分数低于60插入补考记录 
	{
		if(s.score < 60)
			Push(fail,s);
		else Push(head,s);
		cout<<"记录成功\n";
	}
	else cout<<"该学生不存在或已及格\n";
}
void Save()
{
	ofstream fout;
	fout.open(filename,ios::out);	//覆盖文件 
	for(node *t = head->next;t != NULL; t = t->next)	//遍历输出及格链表 
	{
		fout<<t->stu.name<<" "
			<<t->stu.score<<" "
			<<t->stu.id<<endl;
	}
	for(node *t = fail->next;t != NULL; t = t->next)	//遍历输出不及格链表 
	{
		fout<<t->stu.name<<" "
			<<t->stu.score<<" "
			<<t->stu.id<<endl;
	}
	fout.close();
}
void Distory()
{
	for(node *t = head;t != NULL;)		//销毁及格链表 
	{
		node *p = t->next;
		free(t);
		t = p;
	}
	for(node *t = fail;t != NULL;)		//销毁不及格链表 
	{
		node *p = t->next;
		free(t);
		t = p;
	}
}
