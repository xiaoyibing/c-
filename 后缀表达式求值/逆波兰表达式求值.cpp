#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node *list; // ������
typedef struct Node *list2; // ������

struct Node
{
    char data[10000];
    int pointer; // ջ��
};
struct Node2
{
    int data[10000];
    int pointer; // ջ��
};

void Push(list s, char c) // ��ջ
{
    s->pointer++;
    s->data[s->pointer] = c;
}

void Push2(list2 s, int c) // ��ջ
{
    s->pointer++;
    s->data[s->pointer] = c;
}

char Pop(list s) // ��ջ
{
    if (s->pointer == -1)
        return 0;
    s->pointer--;
    return s->data[s->pointer + 1];
}
char Pop2(list2 s) // ��ջ
{
    if (s->pointer == -1)
        return 0;
    s->pointer--;
    return s->data[s->pointer + 1];
}
int main()
{
    char str[10000];   // ��׺���ʽ
    char str2[10000];  // ��׺���ʽ
    int str_i = 0;
    int str2_i = 0;
    char ch;
    list ps;
    list2 ps2;

    ps = (list)malloc(sizeof(struct Node));
    ps2 = (list2)malloc(sizeof(struct Node2));

    ps->pointer = -1;
    ps2->pointer = -1;

    gets(str); // ������׺���ʽ

    while (str[str_i] != '\0')
    {
        ch = str[str_i];

        // ����������
        if ('0' <= ch && ch <= '9')
        {
            str2[str2_i] = ch;
            str2_i++;

            // �����λ��
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
        // ������ֱ����ջ
        else if (ch == '(')
        {
            Push(ps, ch);
        }
        // ����������ֱ�ӳ�ջ��ֱ��ջ��Ϊ������
        else if (ch == ')')
        {
            while (ps->data[ps->pointer] != '(' && ps->pointer != -1)
            {
                str2[str2_i] = Pop(ps);
                str2_i++;
            }
            Pop(ps); // �����ų�ջ�������
        }
        // ����˳���
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
        // ����Ӽ���
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

    // ��ջ��ʣ���������������׺���ʽ
    while (ps->pointer != -1)
    {
        str2[str2_i] = Pop(ps);
        str2_i++;
    }
	str2[str2_i] = '\0';  // ����ַ���������

    printf("ת���ĺ�׺���ʽΪ��%s\n", str2);

    // �����׺���ʽ��ֵ
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
    printf("���ʽֵΪ��%d\n", dddd);

    // �ͷ��ڴ�
    free(ps);
    free(ps2);

    return 0;
}

