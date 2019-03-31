#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<math.h>
using namespace std;

//全局变量 
int preArr[60000],Arr[60000];	//preArr存原始数据，Arr用于排序 
int N;							//数据规模 
int cmp,move; 					//比较次数和移动次数 

//函数
void Init();						//生成随机数据 
void copyArr(int *a,int *b,int n);	//把数据从b拷贝到a 
bool okArr(int *a,int n);			//检测数组a是否升序 
void printArr(int *a,int n);		//打印数组 
void InsertSort(int *a,int n);		//直接插排
void BInsertSort(int *a,int n);		//折半插排
void ShellSort(int *a,int n);		//希尔排序
void BubbleSort(int *a,int n);		//起泡排序
void QuickSort(int *a,int n);		//快速排序
void SelectSort(int *a,int n);		//选择排序
void HeapSort(int *a,int n);		//堆排序
void MergeSort(int *a,int n);		//二路归并排序 
int main()
{
	Init();					//printArr(Arr,n);
	InsertSort(Arr,N);		//printArr(Arr,N);
	BInsertSort(Arr,N);		//printArr(Arr,N);
	ShellSort(Arr,N);		//printArr(Arr,N);
	BubbleSort(Arr,N);		//printArr(Arr,N);
	QuickSort(Arr,N);		//printArr(Arr,N);
	SelectSort(Arr,N);		//printArr(Arr,N);
	HeapSort(Arr,N);		//printArr(Arr,N);
	MergeSort(Arr,N);		//printArr(Arr,N);
	return 0;
}

void Init()
{
	srand(time(0));
	cout<<"输入数据个数：";
	cin>>N;
	for(int i = 1;i<=N;i++)
		preArr[i] = Arr[i] = rand() % 30000;
	cout<<"原始数据随机生成完毕\n";
}
void copyArr(int *a,int *b,int n)
{
	for(int i = 1;i<=n;i++)
		a[i] = b[i];
}
bool okArr(int *a,int n)
{
	for(int i = 1;i<n;i++)
		if(a[i]>a[i+1]) return false;
	return true;
}
void printArr(int *a,int n)
{
	for(int i = 1;i<=n;i++)
		cout<<a[i]<<" ";
	cout<<endl;
}
void InsertSort(int *a,int n)		//直接插排
{
	copyArr(Arr,preArr,n);
	cmp = 0;move = 0;
	int i,j;
	for(i = 2;i<=n;i++,cmp++)
		if(a[i - 1] > a[i])
		{
			a[0] = a[i];move++;
			for(j = i-1;a[0]<a[j];j--,cmp++,move++)
				a[j+1] = a[j];
			a[j+1] = a[0];move++;
		}
	cout<<"直接插排\t比较次数："<<cmp<<"\t\t移动次数："<<move<<endl;
}
void BInsertSort(int *a,int n)		//折半插排
{
	copyArr(Arr,preArr,n);
	cmp = 0;move = 0;
	int i,j,low,high,m;
	for(i = 2;i<=n;i++)
	{
		a[0] = a[i]; move++;
		low = 1;high = i-1;
		while(low<=high)
		{
			m = (low + high) / 2;
			if(a[0] < a[m]) high = m-1; 
			else low = m + 1; cmp++;
		}
		for(j = i-1;j>=high + 1;j--,move++) a[j+1] = a[j];
		a[high + 1] = a[0];move++;
	}	
	cout<<"折半插排\t比较次数："<<cmp<<"\t\t移动次数："<<move<<endl;
}
void ShellSort(int *a,int n)		//希尔排序
{
	copyArr(Arr,preArr,n);
	cmp = 0;move = 0;
	int i,j,k,dk,t = log2(n-1);
	for(k = 1;k<=t;k++)
	{
		dk = 1<<(t-k+1) - 1;				//d[k] = 2^(t-k+1) - 1
		for(i = dk + 1;i<=n;i++,cmp++)
			if(a[i] < a[i - dk])
			{
				a[0] = a[i];move++;
				for(j = i - dk;j > 0 && a[0] < a[j];j-=dk,cmp++,move++)
					a[j + dk] = a[j];
				a[j + dk] = a[0];	move++;
			}
	}
	cout<<"希尔排序\t比较次数："<<cmp<<"\t\t移动次数："<<move<<endl;
}
void BubbleSort(int *a,int n)		//起泡排序
{
	copyArr(Arr,preArr,n);
	cmp = 0;move = 0;
	int k,i,j,t;
	for(i = n;i >= 1;i--)
	{
		k = true;
		for(j = 1;j < i;j++,cmp++)
			if(a[j] > a[j+1])
				{
					t = a[j];
					a[j] = a[j + 1];
					a[j + 1] = t;
					move+=3;
					k = false;
				}
		if(k) break;
	}
	cout<<"起泡排序\t比较次数："<<cmp<<"\t\t移动次数："<<move<<endl;
}
void qsort(int a[],int l,int r)
{
	int i=l,j=r,mid=a[(l+r)/2],t;
	while(i<=j)
	{
		while(a[i]<mid) i++,cmp++;
		while(a[j]>mid) j--,cmp++;cmp+=2;
		if(i<=j)
		{
			t=a[i];a[i]=a[j];a[j]=t; i++;j--;move+=3;
		}
	}
	if(i<r) qsort(a,i,r);
	if(j>l) qsort(a,l,j);
}
void QuickSort(int *a,int n)		//快速排序
{
	copyArr(Arr,preArr,n);
	cmp = 0;move = 0;
	qsort(a,1,n);
	cout<<"快速排序\t比较次数："<<cmp<<"\t\t移动次数："<<move<<endl;
}
void SelectSort(int *a,int n)		//选择排序
{
	copyArr(Arr,preArr,n);
	cmp = 0;move = 0;
	int i,j,k,min;
	for(i = 1;i<n;i++)
	{
		min = a[i];
		j = i;
		for(k = i + 1;k<=n;k++,cmp++)
			if(a[k] < min)
			{
				min = a[k];
				j = k;	move+=2;
			}
		if(j != i)
		{
			k = a[i];	move+=3;
			a[i] = a[j];
			a[j] = k;
		}
	}
	cout<<"选择排序\t比较次数："<<cmp<<"\t\t移动次数："<<move<<endl;
}
void adjust(int *a,int s,int m)
{
	int rc = a[s];move++;
	for(int j = s * 2;j<=m;j*=2)
	{
		if(j<m && a[j] <a[j+1]) j++; cmp+=2;
		if(rc>=a[j]) break;
		a[s] = a[j];s = j;move++;
	}
	a[s] = rc;	move++;
}
void HeapSort(int *a,int n)			//堆排序 
{
	copyArr(Arr,preArr,n);
	cmp = 0;move = 0;
	for(int i = n/2;i >=1;i-- )
		adjust(a,i,n);
	for(int i = n;i>1;i--)
	{
		int t = a[1];
		a[1] = a[i];
		a[i] = t; move += 3;
		adjust(a,1,i-1);
	}
	cout<<"堆排序\t\t比较次数："<<cmp<<"\t\t移动次数："<<move<<endl;
}
void merge(int arr[],int low,int mid,int high)  
{//low为第1有序区的第1个元素，i指向第1个元素, mid为第1有序区的最后1个元素  
    int i=low,j=mid+1,k=0;  //mid+1为第2有序区第1个元素，j指向第1个元素   
    int *temp=new int[high-low+1]; //temp数组暂存合并的有序序列  
    while(i<=mid && j<=high)//顺序选取两个有序区的较小元素，存储到t数组中  
    {  	cmp++;move++;
        if(arr[i]<=arr[j])//较小的先存入temp中  
            temp[k++]=arr[i++];  
        else  
            temp[k++]=arr[j++];  
    }  
    while(i<=mid)//若比较完之后，第一个有序区仍有剩余，则直接复制到t数组中  
        temp[k++]=arr[i++],move++;  
    while(j<=high)//同上  
        temp[k++]=arr[j++],move++;  
    for(i=low,k=0;i<=high;i++,k++,move++)//将排好序的存回arr中low到high这区间   
        arr[i]=temp[k];  
    delete []temp;//删除指针，由于指向的是数组，必须用delete []   
} 
void mergesort(int *arr,int low,int high)
{
	//用递归应用二路归并函数实现排序——分治法  
    if(low<high) 
    {  
        int mid=(low+high)/2;  
        mergesort(arr,low,mid);  
        mergesort(arr,mid+1,high);  
        merge(arr,low,mid,high);  
    } 
}
void MergeSort(int *a,int n)		//二路归并排序 
{
	copyArr(Arr,preArr,n);
	cmp = 0;move = 0;
	mergesort(a,1,n);
	cout<<"二路归排\t比较次数："<<cmp<<"\t\t移动次数："<<move<<endl;
}
