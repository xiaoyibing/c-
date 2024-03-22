/*任务1：中缀表达式转后缀表达式
输入一个中缀表达式，程序能输出正确的后缀表达式
请输入中缀表达式：
81/3+67*(3+12)-24*5
转换的后缀表达式为：
81#3#/67#3#12#+*+24#5#*-*/

//#include <ctype.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct Node *list;//重命名
struct Node
{
	char data[1000];
	int pointer;//栈顶
};

void Push(list s,char c)//入栈
{
	s->pointer++;
	s->data[s->pointer]=c;
}

char Pop(list s)//出栈
{
	if (s->pointer==-1)
		return 0;
	s->pointer--;
	return s->data[s->pointer+1];
}

int main()
{
	char str[100];//中缀表达式 
	char str2[100];//后缀表达式 
	int str_i=0;
	int str2_i=0;
	char ch;
	list ps;
	ps=(list)malloc(sizeof(struct Node));
	ps->pointer=-1;
	gets(str);//输入中缀表达式
	
	while(str[str_i]!='\0')
	{
		ch=str[str_i];
		//Push(ps,ch);
		//printf("%s",ps->data);
		if ('0' <= str[str_i] && str[str_i] <= '9')//运算数
		{
			str2[str2_i]=str[str_i];
			str2_i++;
			if('0' <= str[str_i+1] && str[str_i+1] <= '9'){
				int a;
			}
			
			
			
			else{
			str2[str2_i]='#';
			str2_i++;}
		}
		//左括号直接入栈
		if('('==str[str_i])
            {
			Push(ps,str[str_i]);
			}
 
        //遇到右括号直接出栈，直到栈顶为左括号
        if(')'==str[str_i])
        {
            while('(' !=ps->data[ps->pointer])
            {
				str2[str2_i]=Pop(ps);
				str2_i++;
            }
            Pop(ps);  //左括号出栈但不输出
        }
		if(str[str_i]=='*' || str[str_i]=='/' )//乘除
		{
			if(ps->pointer==-1)
			{
				Push(ps,str[str_i]);
				
			}
			else
			{
				if(ps->data[ps->pointer]=='*' ||ps->data[ps->pointer]=='/'){
				while((ps->data[ps->pointer]=='*' ||ps->data[ps->pointer]=='/')&& ps->pointer!=-1)
				{
					str2[str2_i]=Pop(ps);
					str2_i++;
					
				}
				Push(ps,str[str_i]);}
				
				if(ps->data[ps->pointer]=='+' || ps->data[ps->pointer]=='-' || ps->data[ps->pointer]=='(')
				{				
					Push(ps,str[str_i]);
					
				}
			}
		}
		if(str[str_i]=='+' || str[str_i]=='-')//加减
		{
			if(ps->pointer==-1)
			{
				Push(ps,str[str_i]);
				
			}
			else
			{
				if(ps->data[ps->pointer]!='(')
				{
				while(ps->data[ps->pointer]!='(' && ps->pointer!=-1)
				{
					str2[str2_i]=Pop(ps);
					str2_i++;
					
				}
				Push(ps,str[str_i]);}
				
				if(ps->data[ps->pointer]=='(')
				{				
					Push(ps,str[str_i]);
				}
			}

		}
		str_i++;
		//printf("%s\n",str2);
	}
	while(ps->pointer!=-1)
	{
	str2[str2_i]=Pop(ps);
	str2_i++;}
	printf("%s",str2);
	return 0;
}