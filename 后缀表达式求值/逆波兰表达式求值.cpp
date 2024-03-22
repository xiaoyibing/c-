#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node *list; // 重命名
typedef struct Node *list2; // 重命名

struct Node
{
    char data[10000];
    int pointer; // 栈顶
};
struct Node2
{
    int data[10000];
    int pointer; // 栈顶
};

void Push(list s, char c) // 入栈
{
    s->pointer++;
    s->data[s->pointer] = c;
}

void Push2(list2 s, int c) // 入栈
{
    s->pointer++;
    s->data[s->pointer] = c;
}

char Pop(list s) // 出栈
{
    if (s->pointer == -1)
        return 0;
    s->pointer--;
    return s->data[s->pointer + 1];
}
char Pop2(list2 s) // 出栈
{
    if (s->pointer == -1)
        return 0;
    s->pointer--;
    return s->data[s->pointer + 1];
}
int main()
{
    char str[10000];   // 中缀表达式
    char str2[10000];  // 后缀表达式
    int str_i = 0;
    int str2_i = 0;
    char ch;
    list ps;
    list2 ps2;

    ps = (list)malloc(sizeof(struct Node));
    ps2 = (list2)malloc(sizeof(struct Node2));

    ps->pointer = -1;
    ps2->pointer = -1;

    gets(str); // 输入中缀表达式

    while (str[str_i] != '\0')
    {
        ch = str[str_i];

        // 处理运算数
        if ('0' <= ch && ch <= '9')
        {
            str2[str2_i] = ch;
            str2_i++;

            // 处理多位数
            while ('0' <= str[str_i + 1] && str[str_i + 1] <= '9')
            {
                str_i++;
                ch = str[str_i];
                str2[str2_i] = ch;
                str2_i++;
            }

            str2[str2_i] = '#';
            str2_i++;
        }
        // 左括号直接入栈
        else if (ch == '(')
        {
            Push(ps, ch);
        }
        // 遇到右括号直接出栈，直到栈顶为左括号
        else if (ch == ')')
        {
            while (ps->data[ps->pointer] != '(' && ps->pointer != -1)
            {
                str2[str2_i] = Pop(ps);
                str2_i++;
            }
            Pop(ps); // 左括号出栈但不输出
        }
        // 处理乘除法
        else if (ch == '*' || ch == '/')
        {
            if (ps->pointer == -1 || ps->data[ps->pointer] == '+' || ps->data[ps->pointer] == '-' || ps->data[ps->pointer] == '(')
            {
                Push(ps, ch);
            }
            else
            {
                while ((ps->data[ps->pointer] == '*' || ps->data[ps->pointer] == '/') && ps->pointer != -1)
                {
                    str2[str2_i] = Pop(ps);
                    str2_i++;
                }
                Push(ps, ch);
            }
        }
        // 处理加减法
        else if (ch == '+' || ch == '-')
        {
            if (ps->pointer == -1 || ps->data[ps->pointer] == '(')
            {
                Push(ps, ch);
            }
            else
            {
                while (ps->pointer != -1 && ps->data[ps->pointer] != '(')
                {
                    str2[str2_i] = Pop(ps);
                    str2_i++;
                }
                Push(ps, ch);
            }
        }

        str_i++;
    }

    // 将栈中剩余运算符弹出到后缀表达式
    while (ps->pointer != -1)
    {
        str2[str2_i] = Pop(ps);
        str2_i++;
    }
	str2[str2_i] = '\0';  // 添加字符串结束符

    printf("转换的后缀表达式为：%s\n", str2);

    // 计算后缀表达式的值
    int all_num = strlen(str2);
    char char_cc[10000];
    int j = 0;

// ...

for (int i = 0; i < all_num; i++)
{
    if ('0' <= str2[i] && str2[i] <= '9')
    {
        char_cc[j] = str2[i];
        j++;
    }
    else if (str2[i] == '#')
    {
        int int_cc = 0;
        for (int r = 0; r < j; r++)
        {
            int_cc = int_cc * 10 + char_cc[r] - '0';
        }
        Push2(ps2, int_cc);
        j = 0;
    }
    else
    {
        int a = Pop2(ps2);
        int b = Pop2(ps2);
        switch (str2[i])
        {
        case '+':
            Push2(ps2, b + a);
            break;
        case '-':
        	
            Push2(ps2, b - a);
            break;
        case '/':
            Push2(ps2, b / a);
            break;
        case '*':
            //Push2(ps2, b * a);
            int y;
			y=a*b;
			 Push2(ps2, y);
            //printf("%d\n",y);
        //printf("%d\n",ps2->data[ps2->pointer]); 
            break;
        }
       // printf("%d\n",ps2->data[ps2->pointer]); 
    }
}

// ...

int dddd;
dddd=Pop2(ps2);
    printf("表达式值为：%d\n", dddd);

    // 释放内存
    free(ps);
    free(ps2);

    return 0;
}

