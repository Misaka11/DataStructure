#include<fstream>
#include<iostream> 
using namespace std; 
#define N 26
#define INF 999999
typedef struct  
{  
    int w;  
    int pa;  
    int left;  
    int right;  
    char value;  
} HNode;        //结点结构体  

int zimu[N];		//存放26字母在文章中出现的次数 
HNode h[2 * N - 1];	//huffman树 
string hc[N];		//存放26字母的编码 

void ReadfromFile();//从文件读取文章，并统计26字母在文章中出现的次数 
void Print();		//输出26英文字母出现的次数和以及相应的编码
void HuffmanTree (int n); //构造一颗哈夫曼树
void Encode(int i,string code);//根据树进行编码 

int main()
{
	ReadfromFile();	//读取文章 
	HuffmanTree(N);	//构建树 
	Encode(2 * N - 2,"");	//从根节点递归编码 
	Print();		//输出结果 
	return 0;
}

void ReadfromFile()
{
	char filename[20];
	cout<<"请输入文章的文件名：";
	cin>>filename;
	ifstream fin;
	fin.open(filename,ios::in);
	if(fin.fail())
	{
		cout<<"文件不存在\n";
		exit(0);
	}
	char c;
	while(fin.get(c))
	{
		cout<<c;
		if(c>='a' && c<= 'z') zimu[c-'a']++;
	}
	cout<<endl;
	fin.close();
}
void Print()
{
	for(int i = 0;i<26;i++)
		cout<<(char)(i+'a')<<"\t次数\t"<<zimu[i]<<"\t"<<hc[i]<<endl; 
}

void HuffmanTree (int n)
{
	//m1、m2：构造哈夫曼树不同过程中两个最小权值结点的权值， 
    //x1、x2：构造哈夫曼树不同过程中两个最小权值结点在数组中的序号。
    int m1, m2, x1, x2;  
    // 初始化存放哈夫曼树数组 h[] 中的结点
    for (int i=0; i<2*n-1; i++)  
    {  
        h[i].w = 0;
        h[i].pa =-1;  
        h[i].left =-1;  
        h[i].right =-1;  
    }  
    for (int i=0; i<n; i++)  
    {  
		h[i].value = char(i + 'a');
		h[i].w = zimu[i];
    } 
    // 循环构造 Huffman树 
    for (int i=0; i<n-1; i++)  
    {  
        m1=m2=INF;     //m1、m2中存放两个无父结点且结点权值最小的两个结点 
        x1=x2=0; 
        //找出所有结点中权值最小、无父结点的两个结点
        for (int j=0; j<n+i; j++)  
        {  
        	if(h[j].pa != -1) continue;//有父节点忽略 
            if (h[j].w < m1)  
            {  
                m2=m1;   
                x2=x1;   
                m1=h[j].w;  
                x1=j;  
            }  
            else if (h[j].w < m2)  
            {  
                m2=h[j].w;  
                x2=j;  
            }  
        } 
        //设置找到的两个子结点 x1、x2 的父结点信息 
        h[x1].pa  = n+i; 
        h[x2].pa  = n+i; 
        h[n+i].w = h[x1].w + h[x2].w;  
        h[n+i].left = x1;  
        h[n+i].right = x2; 
    }
} 
//递归编码 
void Encode(int i,string code)
{
	//叶子节点，保存编码 
	if(h[i].left == -1 && h[i].right == -1)
	{
		hc[h[i].value - 'a'] = code;
	}
	else 
	{
		Encode(h[i].left,code + '0');	//左分支，编码+0 
		Encode(h[i].right,code + '1');	//右分支，编码+1 
	}
}
