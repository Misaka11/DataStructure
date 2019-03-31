#include<iostream>
using namespace std;
int map[10][10] =
{
	1  ,1,  1,  1,  1,  1  ,1,  1,  1,  1,                  //（1,1）是入口
	1,  0,  0,  1  ,0,  0,  0  ,1,  0,  1,            
	1 , 0 , 0 , 1 , 0  ,0 , 0  ,1  ,0,  1,
	1  ,0  ,0  ,0,  0  ,1  ,1  ,0  ,0 , 1,
	1 , 0,  1 , 1 , 1,  0 , 0  ,0 , 0 , 1,
	1,  0,  0  ,0  ,1 , 0  ,0  ,0 , 0  ,1,
	1 , 0  ,1 , 0 , 0 , 0  ,1 , 0,  0 , 1,
	1 , 0  ,1  ,1,  1 , 0,  1,  1 , 0 , 1,
	1  ,1,  0 , 0 , 0 , 0 , 0 , 0 , 0 , 1,                  //（8,8）是出口
	1 , 1 , 1  ,1  ,1  ,1  ,1  ,1  ,1  ,1,
};
int dx[4] = {1,0,-1,0},
	dy[4] = {0,-1,0,1};
struct poi
{
	int x,y,step,forward;
	poi(int x1 = 0,int y1 = 0,int step1 = 0,int forward1 = 0)
	{
		x = x1,y = y1,step = step1,forward = forward1;
	}
};
poi que[11*11];
poi sta[11*11];
void SearchByStack();
void SearchByQueue();
int main()
{
	cout<<"input 1 to show all the ways or input 2 to show the shortest way:";
	int choice;
	cin>>choice;
	if(choice == 1)
		SearchByStack();
	else if(choice == 2)
		SearchByQueue();
	getchar();getchar();
	return 0;
}
void SearchByStack()
{
	int top = -1,ways = 0;
	sta[++top] = poi(1,1);
	map[1][1] = 1;
	while(top>=0)
	{
		int x1 = sta[top].x;
		int y1 = sta[top].y;
		int f1 = sta[top].forward++;
		if(x1 == 8 && y1 == 8)
		{
			cout<<"the "<<++ways<<" way: ";
			for(int i = 0;i<=top;i++)
				cout<<'('<<sta[i].x<<','<<sta[i].y<<") ";
			cout<<endl;
			map[x1][y1] = 0;
			top--;
		}
		else if(f1 == 4)
		{
			map[x1][y1] = 0;
			top--;
		}
		else
		{
			int x2 = x1 + dx[f1];
			int y2 = y1 + dy[f1];
			if(!map[x2][y2])
			{
				sta[++top] = poi(x2,y2);
				map[x2][y2] = 1;
			}
		}
	}
}

void SearchByQueue()
{
	int f = 0,r = 1;
	map[1][1] = 1;
	que[0] = poi(1,1,1,-1);
	while(f < r)
	{
		int x1 = que[f].x;
		int y1 = que[f].y;
		for(int k = 0;k<4;k++)
		{
			int x2 = x1 + dx[k];
			int y2 = y1 + dy[k];
			if(!map[x2][y2])
			{
				que[r++] = poi(x2,y2,que[f].step + 1,f);
				map[x2][y2] = 1;
			}
			if(x2 == 8 && y2 == 8)
			{
				cout<<"the shortest way is : ";
				int pre = r - 1;
				while(pre!=-1)
				{
					cout<<'('<<que[pre].x<<','<<que[pre].y<<")←";
					pre = que[pre].forward;
				}
				return;
			}
		}
		f++;
	}
}