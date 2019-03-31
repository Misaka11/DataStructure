#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <conio.h>
using namespace std;
//ѧ������Ϣ 
struct Student
{
	char name[20];
	float score; 
	char id[20];
};
//�����һ���ڵ� 
struct node
{
  Student stu;
  node *next;
  node *pre;  
};
//head��ż���ѧ������Ϣ��fail��Ų�����ѧ������Ϣ 
node *head,*fail;
//�ļ��� 
char filename[20];
//��ʱ���� 
char s[20];

void Create();					//������¼ 
void Push(node *h,Student &s); 	//��ѧ����Ϣ���������ҵ����ʵ�λ�÷��� 
void DisplayAll(node *h);		//��ʾ���� 
void Insert();					//���뺯�� 
void Del(char *s);				//ɾ������ sΪ���� 
int Query(char *s);				//��ѯ���� 
void BuKao();					//�������� 
void Save();					//���溯�� 
void Distory();					//�������� 
//�˵����� 
int menu_select()
{
	char i;
	do{
		system("cls");
		printf("1.������¼�����ļ����룩\n");
		printf("2.��ʾ���м�¼\n");
		printf("3.����һ����¼\n");
		printf("4.ɾ��һ����¼\n");
		printf("5.���벹���ɼ�\n");
		printf("6.��ѯ\n");	
		printf("7.����\n");	
		printf("0.�˳�\n");
		printf("������ѡ�����(0-7):");
		i=getchar();		
	}while(i<'0' || i>'7');
	return (i-'0');	
}
//������ 
int main()
{ 
    for(;;)
	{
		switch(menu_select())
		{
		case 1:
			cout<<"���ô���������\n";
			Create();
			break;
		case 2:
			cout<<"����ѧ������Ϣ��\n";
			DisplayAll(head);
			cout<<"������ѧ������Ϣ��\n";
			DisplayAll(fail);		
			break;
		case 3:
			printf("���ò��뺯��\n");
			Insert();		
			break;
		case 4:
			printf("����ɾ������\n");
			cout<<"����ɾ��ѧ������\n";
			cin>>s;
			Del(s);
			break;
		case 5:			    
			printf("���ò������� :\n");	
			BuKao();		
			break;		
		case 6:			    
			printf("���ò�ѯ����\n");
			cout<<"�����ѯѧ������\n";
			cin>>s;
			Query(s);		
			break;
		case 7:
			printf("���ñ��溯��\n");
			Save();
			cout<<"����ɹ�\n";
			break;		  
		case 0:
			printf("�ټ�\n");
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
	//��������ͷ 
	head = new node;
	head->next = head->pre = NULL;
	fail = new node;
	fail->next = fail->pre = NULL;
	//���ļ����� 
	cout<<"�������ļ���:"<<endl;
	cin>>filename; 
    ifstream fin;
    fin.open(filename,ios::in);
    if(fin.fail())
    {
        cout<<"�ļ�������"<<endl;
        exit(0);   
    }
    Student t;
    while(fin>>t.name>>t.score>>t.id)
    {   
        if(t.score < 60)		//���ݷ����Ƿ񼰸�����Ϣ 
            Push(fail,t); 
        else Push(head,t);
    }
    fin.close();
}
void Push(node *h,Student &s)
{
	node *p = h;
	while(p->next)		//Ѱ�Һ��ʵ�λ�ò��� 
	{
		if(strcmp(s.name,p->next->stu.name) == -1) break;
		else p = p->next;
	} 
	node *t = new node;		//�����½ڵ� 
	strcpy(t->stu.id,s.id);
	strcpy(t->stu.name,s.name);
	t->stu.score = s.score;
	if(p->next)			//����ڱ��в��� 
	{
		p->next->pre = t;
		t->next = p->next;
		t->pre = p;
		p->next = t;
	}
	else				//����ڱ�β���� 
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
		cout<<"û��ѧ����Ϣ\n";
		return;
	}
	int num = 0;
	for(node *t = h->next;t != NULL; t = t->next)
	{
		num++;			//ÿ10��һҳ 
		if(num>10)
		{
			cout<<"���������һҳ\n";
			getch();
			num = 0;
			system("cls");
		}
		cout<<"������ "<<t->stu.name<<" , �ɼ��� "
			<<t->stu.score<<" , ѧ�ţ� "<<t->stu.id
			<<endl;
	}

}
 
void Insert()
{
	Student t;
	cout<<"����������ѧ�������� �ɼ� ѧ��\n";
	cin>>t.name>>t.score>>t.id;
	if(strlen(t.id) != 9)			//���ѧ���Ƿ�Ϸ� 
	{
		cout<<"ѧ�ű���Ϊ����Ϊ9��ÿһλ��Ϊ���֣�����ʧ��\n";
		return;
	}
	for(int i = 0;i < 9;i++)
		if(t.id[i] > '9' || t.id[i] < '0')
			{
				cout<<"ѧ�ű���Ϊ����Ϊ9��ÿһλ��Ϊ���֣�����ʧ��\n";
				return;
			}
	if(t.score<60)		//���ݷ����Ƿ񼰸�����Ϣ 
		Push(fail,t);
	else Push(head,t);
	cout<<"����ɹ���\n"; 
}
void Del(char *s)
{
	int num = Query(s);	//��ѯ�Ƿ���� 
	if(num == 1)		//ֻ����һ����¼ 
	{
		for(node *t = head->next;t != NULL; t = t->next)
		if(strcmp(s,t->stu.name) == 0)
		{
			t->pre->next = t->next;
			if(t->next) t->next->pre = t->pre;
			free(t);
			cout<<"ɾ���ɹ�\n";
		}
		for(node *t = fail->next;t != NULL; t = t->next)
		if(strcmp(s,t->stu.name) == 0)
		{
			t->pre->next = t->next;
			if(t->next) t->next->pre = t->pre;
			free(t);
			cout<<"ɾ���ɹ�\n";
		}
	}
	else if(num>1)		//���ڶ�����¼ 
	{
		cout<<"������ѧ�Ž���ɾ����\n";
		char id[20];
		cin>>id;
		for(node *t = head->next;t != NULL; t = t->next)
		if(strcmp(id,t->stu.id) == 0)
		{
			t->pre->next = t->next;
			if(t->next) t->next->pre = t->pre;
			free(t);
			cout<<"ɾ���ɹ�\n";
		}
		for(node *t = fail->next;t != NULL; t = t->next)
		if(strcmp(id,t->stu.id) == 0)
		{
			t->pre->next = t->next;
			if(t->next) t->next->pre = t->pre;
			free(t);
			cout<<"ɾ���ɹ�\n";
		}
	}
	else cout<<"���޴���\n";
}
int Query(char *s)
{//�����������ң��ҵ��ͼ�����+1��������ü�¼ 
	int num = 0;
	for(node *t = head->next;t != NULL; t = t->next)
		if(strcmp(s,t->stu.name) == 0)
		{
			num++;
			cout<<"������ "<<t->stu.name<<" , �ɼ��� "
				<<t->stu.score<<" , ѧ�ţ� "<<t->stu.id
				<<endl;
		}
	for(node *t = fail->next;t != NULL; t = t->next)
		if(strcmp(s,t->stu.name) == 0)
		{
			num++;
			cout<<"������ "<<t->stu.name<<"�ɼ��� "
				<<t->stu.score<<" , ѧ�ţ� "<<t->stu.id
				<<endl;
		}
	return num;
}

void BuKao()
{
	cout<<"����һ��������¼������ѧ�������������ɼ��Լ�ѧ��:\n";
	Student s;
	cin>>s.name>>s.score>>s.id;
	node *t;
	for(t = fail->next;t != NULL; t = t->next)	//�ڲ����������в��� 
	if(strcmp(s.id,t->stu.id) == 0)break;
	if(t && t->stu.score < 60)				//�ҵ����ҷ�������60���벹����¼ 
	{
		if(s.score < 60)
			Push(fail,s);
		else Push(head,s);
		cout<<"��¼�ɹ�\n";
	}
	else cout<<"��ѧ�������ڻ��Ѽ���\n";
}
void Save()
{
	ofstream fout;
	fout.open(filename,ios::out);	//�����ļ� 
	for(node *t = head->next;t != NULL; t = t->next)	//��������������� 
	{
		fout<<t->stu.name<<" "
			<<t->stu.score<<" "
			<<t->stu.id<<endl;
	}
	for(node *t = fail->next;t != NULL; t = t->next)	//����������������� 
	{
		fout<<t->stu.name<<" "
			<<t->stu.score<<" "
			<<t->stu.id<<endl;
	}
	fout.close();
}
void Distory()
{
	for(node *t = head;t != NULL;)		//���ټ������� 
	{
		node *p = t->next;
		free(t);
		t = p;
	}
	for(node *t = fail;t != NULL;)		//���ٲ��������� 
	{
		node *p = t->next;
		free(t);
		t = p;
	}
}
