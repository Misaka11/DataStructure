#include<iostream>
#include<stdio.h>
#include<string.h>

using namespace std;

char op[10] = " +-*/";		//运算符数组 用于方便计算后缀表达式 
char stack[81];				//临时的一个栈 用于中缀转换成后缀
int top = -1;				//栈顶 
char infix[81];				//中缀表达式 
float post[81];				//后缀表达式 其中运算符以其在数组op中的编号的相反数存放 
int n;						//后缀表达式的个数 

bool legal();	//判断中缀表达式是否合法 
bool Change();	//中缀表达式转换为后缀表达式 
bool isHigh(char opa,char opb);	//运算符opa运算级是否高于opb 
void Printpost();	//输出后缀表达式 
float Computepost();	//计算后缀表达式 
int index(char t)	//找到运算符对应在数组op中的编号的相反数 
{
	for(int i = 1;i<=5;i++)
		if(t == op[i]) return -i;
}

int main()
{
	while(1)
	{
		cout<<"请输入算术表达式(输入#退出程序):"<<endl;
		cin.getline(infix,81);
		if(infix[0] == '#') break;
		n=0;						//清零后缀表达式 
		if(!legal())
			cout<<"算数表达式非法\n";
		else if(Change())			//如果表达式转换成功
		{
			Printpost();					//输出后缀表达式
			cout<<Computepost()<<endl;		//计算后缀表达式 
		}
	}
	cout<<"再见！";
	return 0;
}
bool legal()
{
	int p = 0;  //p代表之前指向的是什么字符
	//0 表示刚开始，1 表示数字，2 表示+-*/，3 表示(,4表示),5 表示.
	int point = 0;//point代表在一个数字中小数点的个数 
	int kuohao = 0;//kuohao代表括号数 
	for(int k = 0;k<strlen(infix);k++)
	{
		char t = infix[k];
		if(point > 1) return false;		//一个数有多个小数点 
		if(kuohao < 0) return false;	//右括号先多于左括号 
		if(t == ' ') continue;	//忽略空格
		else if(t>='0' && t<='9')	//如果为数字
		{
			if(p == 4) return false; //数字前面为 )
			if(p != 1 && p != 5)	//之前不为数字或小数点时清零，即到达一个新的数字 
				point = 0;
			p = 1;
		}
		else if(t == '+' || t == '-' || t == '*' || t == '/')//如果为+-*/
		{
			if(p == 0 || p == 2 || p == 3 || p == 5) return false;
			p = 2;	
		}
		else if(t == '(')
		{
			if(p == 1 || p == 4 || p == 5) return false;
			p = 3;
			kuohao++;
		}
		else if(t == ')')
		{
			if(p == 0 || p == 2 || p == 3 || p == 5) return false;
			p = 4;
			kuohao--;
		}
		else if(t == '.')
		{
			if(p != 1) return false;
			point++;
			p = 5;
		}
		else	
		{	//非法字符 
			return false;
		}
	}
	if(kuohao != 0) return false;		//括号不匹配 
	if(p != 0 && p != 1 && p != 4) return false; //表达式末尾有问题 
	return true;
}
bool Change()
{
	for(int k = 0;k<strlen(infix);k++)
	{
		char t = infix[k];
		if(t == ' ') continue;	//忽略空格
		else if(t == '+' || t == '-' || t == '*' || t == '/' || t == '(' || t == ')')	//如果为运算符
		{
			if(top == -1) stack[++top] = t;	//如果栈为空
			else
			if(isHigh(stack[top],t))   //如果栈顶的运算符优先级>表达式中的运算符优先级	
			{
				if(t == ')')	//闭括号
				{
					while(top>=0 && stack[top] != '(')	//弹出直到开括号
						post[n++] = index(stack[top--]);
					if(top>=0) top--;	//弹出开括号
				}
				else			//非闭括号
				{
					while(top>=0 && isHigh(stack[top],t))//弹出栈中操作符直到栈顶操作数优先级低于当前读入操作数
					{
						post[n++] = index(stack[top--]);
					}
					stack[++top] = t;		//压入新的操作符; 
				}	
			}
			else						//如果栈顶的运算符优先级<表达式中的运算符优先级
			{
				stack[++top] = t;
			}
		}
		else if(t>='0' && t<='9')	//如果为数字,把完整的实数存储进后缀表达式
			{
				string s = "";
				s+=t;
				while((infix[k+1]>='0' && infix[k+1]<='9')||infix[k+1]=='.')
				{
					s+=infix[k+1];
					k++;
				}
				sscanf(s.c_str(),"%f",&post[n++]);
			}
		else
		{
			cout<<"有非法字符\n";
			return 0;
		}
	}
	while(top >=0)
		post[n++] = index(stack[top--]);
	return 1;
}

bool isHigh(char opa,char opb)
{
	if(opb == ')') return true;
	if(opb == '(') return false;
	if(opa == '+' && (opb == '+' || opb == '-')) return true;
	if(opa == '-' && (opb == '+' || opb == '-')) return true;
	if(opa == '*') return true;
	if(opa == '/') return true;
	return false;
}
void Printpost()
{
	cout<<"后缀表达式为：";
	for(int i = 0;i<n;i++)
		if(post[i]>=0)cout<<post[i]<<" ";
	else cout<<op[(int)-post[i]]<<" ";
	cout<<endl;
}
float Computepost()
{
	float s[20] = {0};		//临时计算栈 
	int top_s = -1;			//栈顶 
	float t1,t2;			//用于存放栈顶两个数的两个变量 
	for(int i = 0;i<n;i++)
	{
		if(post[i] >= 0) s[++top_s] = post[i];	//如果是数字则压栈 
		else			//如果是运算符 
		{
			t2 = s[top_s--];		//取栈顶两数字计算 
			t1 = s[top_s--];
			if(op[(int)-post[i]] == '+')
				s[++top_s] = t1 + t2;
			if(op[(int)-post[i]] == '-')
				s[++top_s] = t1 - t2;
			if(op[(int)-post[i]] == '*')
				s[++top_s] = t1 * t2;
			if(op[(int)-post[i]] == '/')
			{
				if(t2 == 0)
				{
					cout<<"出现除数为0，该表达式不合法,输出-999999\n";
					return -999999;
				} 
				s[++top_s] = t1 / t2;
			} 
		}
	}
	return s[0];
}
