#include<iostream>
#include<time.h>
#include<stdlib.h>
using namespace std;

struct qujian			//结构体存储每次快排的low和high 
{
	int low,high;
};
//快排——栈 
void QuickSort_Stack(int *a,int n)
{
	qujian *stack;
	int top = -1,i,j,low,high,mid;
	stack = new qujian[n];
	stack[++top].low = 0;
	stack[top].high = n-1;
	while(top >= 0)
	{
		i = low = stack[top].low;
		j = high = stack[top].high;
		if(i == j)
		{
			top--;
			continue;
		}
		mid = a[(i+j)/2];
		while(i<=j)
		{
			while(a[i]<mid)i++;
			while(a[j]>mid)j--;
			if(i<=j)
			{
				int t = a[i];
				a[i] = a[j];
				a[j] = t;
				i++;j--;
			}
		}
		top--;
		if(i<high)
		{
			stack[++top].low = i;
			stack[top].high = high;
		}
		if(j>low)
		{
			stack[++top].low = low;
			stack[top].high = j;
		}
	}
}
//快排——队列 
void QuickSort_Que(int *a,int n)
{
	qujian *que;
	int h = 0,r = 0,i,j,low,high,mid;
	que = new qujian[3 * n];
	que[r].low = 0;
	que[r++].high = n-1;
	while(h<r)
	{
		i = low = que[h].low;
		j = high = que[h].high;
		if(i == j)
		{
			h++;
			continue;
		}
		mid = a[(i+j)/2];
		while(i<=j)
		{
			while(a[i]<mid)i++;
			while(a[j]>mid)j--;
			if(i<=j)
			{
				int t = a[i];
				a[i] = a[j];
				a[j] = t;
				i++;j--;
			}
		}
		h++;
		if(i<high)
		{
			que[r].low = i;
			que[r++].high = high;
		}
		if(j>low)
		{
			que[r].low = low;
			que[r++].high = j;
		}
	}
}
//输出数组 
void PrintArr(int *a,int n)
{
	for(int i = 0;i<n;i++)
		cout<<a[i]<<" ";
	cout<<endl;
}
//创建数组 
int * CreateArr(int n)
{
	int *a;	
	a = new int[n];
	for(int i = 0;i<n;i++)
		a[i] = rand() % 50;
	return a;
}
//主程序 
int main()
{
	srand(time(0));
	int *a,*b,N;
	cout<<"输入数据个数N = ";
	cin>>N;
	a = CreateArr(N);
	b = CreateArr(N);
	cout<<"下面是使用栈快速排序的数组a:\n";
	PrintArr(a,N);
	cout<<"下面是使用队列快速排序的数组b:\n";
	PrintArr(b,N);
	cout<<"下面是经过栈快速排序的数组a:\n";
	QuickSort_Stack(a,N);
	PrintArr(a,N);
	cout<<"下面是经过队列快速排序的数组b:\n";
	QuickSort_Stack(b,N);
	PrintArr(b,N);
	return 0;
}
