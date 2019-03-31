#include<iostream>
#include<fstream>
#include<cstring>
#define N 43
using namespace std;

struct record	//信息记录 
{
	char name[30];
	char sex[30];
	char phone[30];
	char e_mail[30];
};
typedef struct	//哈希表 
{
	record *elem;	//元素动态数组 
	bool *exist;	//某位置是否存在元素的动态数组 
	int count;		//当前哈希表元素数量 
	int size;		//当前哈希表容量 
}HashTable;

HashTable H;		//定义一个哈希表 
int maxc;			//最高寻址次数 

void CreateHash(HashTable &H);	//从文件读取记录并创建哈希表 
int InsertHash(HashTable &H,record t);//在哈希表中插入元素t，用于创建哈希表 
int Hash(string key);	//哈希函数
int SearchHash(HashTable H,string key,int &p,int &c);//搜索元素 

int main()
{
	CreateHash(H);
	cout<<"放定址散列表最高的寻址次数："<<maxc<<endl;
	cout<<"输入需要查询的手机号码：";
	int p,c = 0;
	string tp;
	cin>>tp;
	if(SearchHash(H,tp,p,c))
	{
		cout<<"散列次数: "<<c<<" 查找成功\n";
		cout<<H.elem[p].name<<" "<<H.elem[p].sex<<" "<<H.elem[p].e_mail<<endl;
	} 
	else
	{
		cout<<"散列次数: "<<c<<" 查找失败\n";
	}
	return 0;
}

void CreateHash(HashTable &H)
{
	//从文件读入记录建立hash表 
	H.size = N;
	H.count = 0;
	H.elem = new record [N];
	H.exist = new bool [N]; 
	for(int i=0;i<N;i++) H.exist[i] = false;
	ifstream fin;
	char filename[20];
	cout<<"输入记录文件名：";
	cin>>filename;
	fin.open(filename,ios::in);
	if(fin.fail())
	{
		cout<<"文件未找到\n";
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
	//在哈希表H中搜索关键字key，若搜索成功，用p返回，函数返回1
	// 若搜索失败，函数返回0。c为冲突次数
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
	//计算key的hash值 
	//经过尝试，将各位求和*4得最高寻址次数最少 
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
	//插入成功返回寻址次数
	//插入失败返回-1 
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
