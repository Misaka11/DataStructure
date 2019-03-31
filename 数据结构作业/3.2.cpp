#include<iostream>
#include<stdio.h>
using namespace std;

struct record
{
	int n;
	char from,temp,to;
	record(){};
	record(int n1,char from1,char temp1,char to1)
	{
		n = n1;from = from1;temp = temp1;to = to1;
	}
};
record a[50];
int top,n;

void move(int num,char from,char to)
{
	printf("%d %c->%c\n",num,from,to);
}

//·ÇµÝ¹éººÅµËþ 
void hanio()
{
	record t;
	while(top > 0)
	{
		t = a[top - 1];
		if(t.n == 1)
		{
			move(t.n,t.from,t.to); 
			top--;
			if(top > 0)
			{
				t = a[top - 1];
				move(t.n,t.from,t.to);
				a[top - 1] = record(t.n - 1, t.temp, t.from, t.to);
			}	
		}
		else
			a[top++] = record(t.n - 1, t.from, t.to, t.temp);	
	}
}

int main()
{
	cout<<"ÇëÊäÈëººÅµËþ¸öÊý£º";
	cin>>n;
	a[top++] = record(n,'A','B','C');
	hanio();
	return 0;
}

/*µÝ¹éººÅµËþ 
void hanio(int n,char from,char temp,char to)
{
	if(n == 1) move(n,from,to);
	hanio(n-1,from,to,temp);
	move(n,from,to);
	hanio(n-1,temp,from,to);
}*/
