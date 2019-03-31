#include<iostream>
using namespace std;
#define k 10
#define Max 10000
int que[k],r;
int main()
{
	r = 2;
	que[0] = 1;
	que[1] = 2;
	do
	{
		que[r%k] = que[(r-1)%k] + que[(r-2)%k];
	}while(que[(r++)%k]<=Max);
	if(r < k)
		for(int i = 0;i<r;i++)
			cout<<que[i]<<" ";
	else
		for(int i = 0;i < k;i++)
			cout<<que[(r + i)%k]<<" ";
	getchar();getchar();
	return 0;
}