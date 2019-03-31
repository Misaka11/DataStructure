#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<math.h>
using namespace std;

//ȫ�ֱ��� 
int preArr[60000],Arr[60000];	//preArr��ԭʼ���ݣ�Arr�������� 
int N;							//���ݹ�ģ 
int cmp,move; 					//�Ƚϴ������ƶ����� 

//����
void Init();						//����������� 
void copyArr(int *a,int *b,int n);	//�����ݴ�b������a 
bool okArr(int *a,int n);			//�������a�Ƿ����� 
void printArr(int *a,int n);		//��ӡ���� 
void InsertSort(int *a,int n);		//ֱ�Ӳ���
void BInsertSort(int *a,int n);		//�۰����
void ShellSort(int *a,int n);		//ϣ������
void BubbleSort(int *a,int n);		//��������
void QuickSort(int *a,int n);		//��������
void SelectSort(int *a,int n);		//ѡ������
void HeapSort(int *a,int n);		//������
void MergeSort(int *a,int n);		//��·�鲢���� 
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
	cout<<"�������ݸ�����";
	cin>>N;
	for(int i = 1;i<=N;i++)
		preArr[i] = Arr[i] = rand() % 30000;
	cout<<"ԭʼ��������������\n";
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
void InsertSort(int *a,int n)		//ֱ�Ӳ���
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
	cout<<"ֱ�Ӳ���\t�Ƚϴ�����"<<cmp<<"\t\t�ƶ�������"<<move<<endl;
}
void BInsertSort(int *a,int n)		//�۰����
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
	cout<<"�۰����\t�Ƚϴ�����"<<cmp<<"\t\t�ƶ�������"<<move<<endl;
}
void ShellSort(int *a,int n)		//ϣ������
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
	cout<<"ϣ������\t�Ƚϴ�����"<<cmp<<"\t\t�ƶ�������"<<move<<endl;
}
void BubbleSort(int *a,int n)		//��������
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
	cout<<"��������\t�Ƚϴ�����"<<cmp<<"\t\t�ƶ�������"<<move<<endl;
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
void QuickSort(int *a,int n)		//��������
{
	copyArr(Arr,preArr,n);
	cmp = 0;move = 0;
	qsort(a,1,n);
	cout<<"��������\t�Ƚϴ�����"<<cmp<<"\t\t�ƶ�������"<<move<<endl;
}
void SelectSort(int *a,int n)		//ѡ������
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
	cout<<"ѡ������\t�Ƚϴ�����"<<cmp<<"\t\t�ƶ�������"<<move<<endl;
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
void HeapSort(int *a,int n)			//������ 
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
	cout<<"������\t\t�Ƚϴ�����"<<cmp<<"\t\t�ƶ�������"<<move<<endl;
}
void merge(int arr[],int low,int mid,int high)  
{//lowΪ��1�������ĵ�1��Ԫ�أ�iָ���1��Ԫ��, midΪ��1�����������1��Ԫ��  
    int i=low,j=mid+1,k=0;  //mid+1Ϊ��2��������1��Ԫ�أ�jָ���1��Ԫ��   
    int *temp=new int[high-low+1]; //temp�����ݴ�ϲ�����������  
    while(i<=mid && j<=high)//˳��ѡȡ�����������Ľ�СԪ�أ��洢��t������  
    {  	cmp++;move++;
        if(arr[i]<=arr[j])//��С���ȴ���temp��  
            temp[k++]=arr[i++];  
        else  
            temp[k++]=arr[j++];  
    }  
    while(i<=mid)//���Ƚ���֮�󣬵�һ������������ʣ�࣬��ֱ�Ӹ��Ƶ�t������  
        temp[k++]=arr[i++],move++;  
    while(j<=high)//ͬ��  
        temp[k++]=arr[j++],move++;  
    for(i=low,k=0;i<=high;i++,k++,move++)//���ź���Ĵ��arr��low��high������   
        arr[i]=temp[k];  
    delete []temp;//ɾ��ָ�룬����ָ��������飬������delete []   
} 
void mergesort(int *arr,int low,int high)
{
	//�õݹ�Ӧ�ö�·�鲢����ʵ�����򡪡����η�  
    if(low<high) 
    {  
        int mid=(low+high)/2;  
        mergesort(arr,low,mid);  
        mergesort(arr,mid+1,high);  
        merge(arr,low,mid,high);  
    } 
}
void MergeSort(int *a,int n)		//��·�鲢���� 
{
	copyArr(Arr,preArr,n);
	cmp = 0;move = 0;
	mergesort(a,1,n);
	cout<<"��·����\t�Ƚϴ�����"<<cmp<<"\t\t�ƶ�������"<<move<<endl;
}
