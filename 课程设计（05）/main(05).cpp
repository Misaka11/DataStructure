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
} HNode;        //���ṹ��  

int zimu[N];		//���26��ĸ�������г��ֵĴ��� 
HNode h[2 * N - 1];	//huffman�� 
string hc[N];		//���26��ĸ�ı��� 

void ReadfromFile();//���ļ���ȡ���£���ͳ��26��ĸ�������г��ֵĴ��� 
void Print();		//���26Ӣ����ĸ���ֵĴ������Լ���Ӧ�ı���
void HuffmanTree (int n); //����һ�Ź�������
void Encode(int i,string code);//���������б��� 

int main()
{
	ReadfromFile();	//��ȡ���� 
	HuffmanTree(N);	//������ 
	Encode(2 * N - 2,"");	//�Ӹ��ڵ�ݹ���� 
	Print();		//������ 
	return 0;
}

void ReadfromFile()
{
	char filename[20];
	cout<<"���������µ��ļ�����";
	cin>>filename;
	ifstream fin;
	fin.open(filename,ios::in);
	if(fin.fail())
	{
		cout<<"�ļ�������\n";
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
		cout<<(char)(i+'a')<<"\t����\t"<<zimu[i]<<"\t"<<hc[i]<<endl; 
}

void HuffmanTree (int n)
{
	//m1��m2���������������ͬ������������СȨֵ����Ȩֵ�� 
    //x1��x2���������������ͬ������������СȨֵ����������е���š�
    int m1, m2, x1, x2;  
    // ��ʼ����Ź����������� h[] �еĽ��
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
    // ѭ������ Huffman�� 
    for (int i=0; i<n-1; i++)  
    {  
        m1=m2=INF;     //m1��m2�д�������޸�����ҽ��Ȩֵ��С��������� 
        x1=x2=0; 
        //�ҳ����н����Ȩֵ��С���޸������������
        for (int j=0; j<n+i; j++)  
        {  
        	if(h[j].pa != -1) continue;//�и��ڵ���� 
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
        //�����ҵ��������ӽ�� x1��x2 �ĸ������Ϣ 
        h[x1].pa  = n+i; 
        h[x2].pa  = n+i; 
        h[n+i].w = h[x1].w + h[x2].w;  
        h[n+i].left = x1;  
        h[n+i].right = x2; 
    }
} 
//�ݹ���� 
void Encode(int i,string code)
{
	//Ҷ�ӽڵ㣬������� 
	if(h[i].left == -1 && h[i].right == -1)
	{
		hc[h[i].value - 'a'] = code;
	}
	else 
	{
		Encode(h[i].left,code + '0');	//���֧������+0 
		Encode(h[i].right,code + '1');	//�ҷ�֧������+1 
	}
}
