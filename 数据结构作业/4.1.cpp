#include<iostream>
#include<cstring>
using namespace std;

void Inverse(char *s,int n)
{
	if(n == 1) return;
	char t = s[0];
	for(int i = 0;i<n-1;i++)
		s[i] = s[i+1];
	s[n-1] = t;
	Inverse(s,n-1);
}

void EqualString(char *s,char *re)
{
	int len = strlen(s),i,j,k;
	for(k = len;k>1;k--)
		for(i = 0;i < len - k + 1;i++)
		{
			for(j = 1;j<k;j++)
				if(s[i + j] != s[i]) break;
			if(j == k)
			{	
				for(int p = 0;p < k;p++) 
					re[p] = s[i];
				re[k] = '\0';
				return;
			}
		}
}


int main()
{
	char s[100],re[100] = "无等值子串";
	cout<<"Input string: ";
	cin>>s;
	EqualString(s,re);
	cout<<"最大等值子串为: "<<re<<endl;
	Inverse(s,strlen(s));
	cout<<"逆置后的字符串为："<<s<<endl;
	
	getchar();getchar();
	return 0;
}