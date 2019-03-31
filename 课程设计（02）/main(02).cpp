#include<iostream>
#include<stdio.h>
#include<string.h>

using namespace std;

char op[10] = " +-*/";		//��������� ���ڷ�������׺���ʽ 
char stack[81];				//��ʱ��һ��ջ ������׺ת���ɺ�׺
int top = -1;				//ջ�� 
char infix[81];				//��׺���ʽ 
float post[81];				//��׺���ʽ �������������������op�еı�ŵ��෴����� 
int n;						//��׺���ʽ�ĸ��� 

bool legal();	//�ж���׺���ʽ�Ƿ�Ϸ� 
bool Change();	//��׺���ʽת��Ϊ��׺���ʽ 
bool isHigh(char opa,char opb);	//�����opa���㼶�Ƿ����opb 
void Printpost();	//�����׺���ʽ 
float Computepost();	//�����׺���ʽ 
int index(char t)	//�ҵ��������Ӧ������op�еı�ŵ��෴�� 
{
	for(int i = 1;i<=5;i++)
		if(t == op[i]) return -i;
}

int main()
{
	while(1)
	{
		cout<<"�������������ʽ(����#�˳�����):"<<endl;
		cin.getline(infix,81);
		if(infix[0] == '#') break;
		n=0;						//�����׺���ʽ 
		if(!legal())
			cout<<"�������ʽ�Ƿ�\n";
		else if(Change())			//������ʽת���ɹ�
		{
			Printpost();					//�����׺���ʽ
			cout<<Computepost()<<endl;		//�����׺���ʽ 
		}
	}
	cout<<"�ټ���";
	return 0;
}
bool legal()
{
	int p = 0;  //p����֮ǰָ�����ʲô�ַ�
	//0 ��ʾ�տ�ʼ��1 ��ʾ���֣�2 ��ʾ+-*/��3 ��ʾ(,4��ʾ),5 ��ʾ.
	int point = 0;//point������һ��������С����ĸ��� 
	int kuohao = 0;//kuohao���������� 
	for(int k = 0;k<strlen(infix);k++)
	{
		char t = infix[k];
		if(point > 1) return false;		//һ�����ж��С���� 
		if(kuohao < 0) return false;	//�������ȶ��������� 
		if(t == ' ') continue;	//���Կո�
		else if(t>='0' && t<='9')	//���Ϊ����
		{
			if(p == 4) return false; //����ǰ��Ϊ )
			if(p != 1 && p != 5)	//֮ǰ��Ϊ���ֻ�С����ʱ���㣬������һ���µ����� 
				point = 0;
			p = 1;
		}
		else if(t == '+' || t == '-' || t == '*' || t == '/')//���Ϊ+-*/
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
		{	//�Ƿ��ַ� 
			return false;
		}
	}
	if(kuohao != 0) return false;		//���Ų�ƥ�� 
	if(p != 0 && p != 1 && p != 4) return false; //���ʽĩβ������ 
	return true;
}
bool Change()
{
	for(int k = 0;k<strlen(infix);k++)
	{
		char t = infix[k];
		if(t == ' ') continue;	//���Կո�
		else if(t == '+' || t == '-' || t == '*' || t == '/' || t == '(' || t == ')')	//���Ϊ�����
		{
			if(top == -1) stack[++top] = t;	//���ջΪ��
			else
			if(isHigh(stack[top],t))   //���ջ������������ȼ�>���ʽ�е���������ȼ�	
			{
				if(t == ')')	//������
				{
					while(top>=0 && stack[top] != '(')	//����ֱ��������
						post[n++] = index(stack[top--]);
					if(top>=0) top--;	//����������
				}
				else			//�Ǳ�����
				{
					while(top>=0 && isHigh(stack[top],t))//����ջ�в�����ֱ��ջ�����������ȼ����ڵ�ǰ���������
					{
						post[n++] = index(stack[top--]);
					}
					stack[++top] = t;		//ѹ���µĲ�����; 
				}	
			}
			else						//���ջ������������ȼ�<���ʽ�е���������ȼ�
			{
				stack[++top] = t;
			}
		}
		else if(t>='0' && t<='9')	//���Ϊ����,��������ʵ���洢����׺���ʽ
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
			cout<<"�зǷ��ַ�\n";
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
	cout<<"��׺���ʽΪ��";
	for(int i = 0;i<n;i++)
		if(post[i]>=0)cout<<post[i]<<" ";
	else cout<<op[(int)-post[i]]<<" ";
	cout<<endl;
}
float Computepost()
{
	float s[20] = {0};		//��ʱ����ջ 
	int top_s = -1;			//ջ�� 
	float t1,t2;			//���ڴ��ջ������������������ 
	for(int i = 0;i<n;i++)
	{
		if(post[i] >= 0) s[++top_s] = post[i];	//�����������ѹջ 
		else			//���������� 
		{
			t2 = s[top_s--];		//ȡջ�������ּ��� 
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
					cout<<"���ֳ���Ϊ0���ñ��ʽ���Ϸ�,���-999999\n";
					return -999999;
				} 
				s[++top_s] = t1 / t2;
			} 
		}
	}
	return s[0];
}
