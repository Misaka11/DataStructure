#include<iostream>
#include<fstream>
#include<cstring>
#define N 43
using namespace std;

struct record	//��Ϣ��¼ 
{
	char name[30];
	char sex[30];
	char phone[30];
	char e_mail[30];
};
typedef struct	//��ϣ�� 
{
	record *elem;	//Ԫ�ض�̬���� 
	bool *exist;	//ĳλ���Ƿ����Ԫ�صĶ�̬���� 
	int count;		//��ǰ��ϣ��Ԫ������ 
	int size;		//��ǰ��ϣ������ 
}HashTable;

HashTable H;		//����һ����ϣ�� 
int maxc;			//���Ѱַ���� 

void CreateHash(HashTable &H);	//���ļ���ȡ��¼��������ϣ�� 
int InsertHash(HashTable &H,record t);//�ڹ�ϣ���в���Ԫ��t�����ڴ�����ϣ�� 
int Hash(string key);	//��ϣ����
int SearchHash(HashTable H,string key,int &p,int &c);//����Ԫ�� 

int main()
{
	CreateHash(H);
	cout<<"�Ŷ�ַɢ�б���ߵ�Ѱַ������"<<maxc<<endl;
	cout<<"������Ҫ��ѯ���ֻ����룺";
	int p,c = 0;
	string tp;
	cin>>tp;
	if(SearchHash(H,tp,p,c))
	{
		cout<<"ɢ�д���: "<<c<<" ���ҳɹ�\n";
		cout<<H.elem[p].name<<" "<<H.elem[p].sex<<" "<<H.elem[p].e_mail<<endl;
	} 
	else
	{
		cout<<"ɢ�д���: "<<c<<" ����ʧ��\n";
	}
	return 0;
}

void CreateHash(HashTable &H)
{
	//���ļ������¼����hash�� 
	H.size = N;
	H.count = 0;
	H.elem = new record [N];
	H.exist = new bool [N]; 
	for(int i=0;i<N;i++) H.exist[i] = false;
	ifstream fin;
	char filename[20];
	cout<<"�����¼�ļ�����";
	cin>>filename;
	fin.open(filename,ios::in);
	if(fin.fail())
	{
		cout<<"�ļ�δ�ҵ�\n";
		exit(0);
	}
	record t;
	while(fin>>t.name>>t.sex>>t.phone>>t.e_mail)
	{
		int c = InsertHash(H,t);
		if(c > maxc) maxc = c;
	}
}

int SearchHash(HashTable H,string key,int &p,int &c)
{
	//�ڹ�ϣ��H�������ؼ���key���������ɹ�����p���أ���������1
	// ������ʧ�ܣ���������0��cΪ��ͻ����
	p = Hash(key);
	int t;
	for(t = p; H.exist[t] && H.elem[t].phone != key;c++)
	{
		if(c % 2)
			t = (p + c/2 * c/2) % N;
		else 
			t = (p - c/2 * c/2) % N;
		if(t < 0) t = (t + N) % N;
	}
	p = t;
	if(key == H.elem[p].phone) return 1;
	else return 0;
}

int Hash(string key)
{
	//����key��hashֵ 
	//�������ԣ�����λ���*4�����Ѱַ�������� 
	int k = 0;
	for(int i = 0;i<key.length();i++)
	{
		k = (key[i] - '0') * 4;
	} 
	k %= N;
	return k;
}
int InsertHash(HashTable &H,record t)
{
	//����ɹ�����Ѱַ����
	//����ʧ�ܷ���-1 
	int c = 0;
	int p;
	if(SearchHash(H,t.phone,p,c)) return -1;
	else 
	{
		H.elem[p] = t;
		H.exist[p] = true;
		++H.count;
	//	cout<<p<<" "<<H.elem[p].name<<endl;
		return c;
	}
}
