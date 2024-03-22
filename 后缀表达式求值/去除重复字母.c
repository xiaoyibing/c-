/*
输入一个字符串
取出一个字符
如果栈为空，输入栈中
如果不是空，与栈中的字符比较大小（小的在上，大的在下）
如果输入的大，则将top放入另一个栈中
直到将输入放进栈中
再将另一个栈里的数据移回来
如果相同则舍弃 
达到26个字符后直接输出 
*/
#include<stdio.h>
#include<stdlib.h>
typedef struct Number *list;
struct Number
{
	char data[26];
	int top;
};
void Push(list s,char c)
{
	s->top++;
	s->data[s->top]=c;
}
char Pop(list s)//出栈
{
	if (s->top==-1)
		return 0;
	s->top--;
	return s->data[s->top+1];
}
int main()
{
	list num1;
	list num2;
	num1=(list)malloc(sizeof(struct Number)); 
	num2=(list)malloc(sizeof(struct Number)); 
	num1->top=-1;
	num2->top=-1;
	char str[10];//改动 
	char ch;
	gets(str);
	int j=0;
	while(str[j]!='\0')
	{
		ch=str[j];
		if(num1->top==-1)
		{
			Push(num1,ch);
		}
		else
		{
            if(num1->data[num1->top]<ch)
            {
			while(num1->data[num1->top]<ch && num1->top!=-1)
			{
                char d;
                d=num1->data[num1->top];
				Push(num2,d); 
                Pop(num1);
			}
            if(num1->data[num1->top]>ch || num1->top==-1)
            Push(num1,ch);
            }


			if(num1->data[num1->top]>ch)
			{
				Push(num1,ch);
			}

            
			while(num2->top!=-1)
			{
				char d;
                d=num2->data[num2->top];
				Push(num1,d); 
                Pop(num2);
			}	
		}
		j++;
	}
	while(num1->top!=-1)
	{
        char d;
        d=num1->data[num1->top];
		printf("%c",d);
	    Pop(num1);
	}
	return 0; 
}
