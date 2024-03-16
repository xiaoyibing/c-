#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
typedef int DataType;

//顺序表的储存结构定义
typedef struct 
{
    int length;//线性表的长度
    DataType data[MAXSIZE];//存放数据元素的数组   
}List;


void InitList(List* list);//初始化
int CreatList(List* list,DataType data[],int n);//存入
int Empty(List* list);//判空操作
void PrintList(List* list);//遍历操作
int Length(List* list);//求顺序表的长度
int Locate(List* list,DataType data);//按值查找(假设没有重复的值)
int Get(List* list, int n);//按位查找
int Insert(List* list,int n,DataType data);//中间插入
int Outsert(List* list,DataType data);//最后插入
int Delete(List* list,int n);//删除
void ClearList(List* list);//清空表
int InLocate(List* list,DataType data);//获得前驱
int OutLocate(List* list,DataType data);//获得后继
int ReadFile(const char* filename,List* list);//打开并读取文件
int WriteFile(const char* filename,List* list);//打开并存入文件
void mainlist();//页面


//主程序
int main(){

    List list;
    int Qq;
    InitList(&list);


    while (Qq != 1)
    {
        mainlist();
        scanf("%d",&Qq);
        switch (Qq)
        {
        case 1:
            printf("程序结束...\n");
            break;
        case 2:
            char filename1[30];
            printf("请输入文件名称：");
            scanf("%s",filename1);
            ReadFile(filename1,&list);
            printf("读取未完成\n");
            break;
        case 3:
            ClearList(&list);
            printf("清空完成\n");
            break;
        case 4:
            char filename2[30];
            printf("请输入文件名称：");
            scanf("%s",filename2);
            WriteFile(filename2,&list);
            printf("存入完成\n");
            break;
        case 5:
            int data5,n;
            printf("请输入要查找前驱的元素：");
            scanf("%d",&data5);
            n=InLocate(&list,data5);
            printf("%d的前驱元素是%d\n",data5,list.data[n]);
            break;
        case 6:
            int n6,data6;
            printf("请输入要插入的元素的位数：");
            scanf("%d",&n6);
            printf("请输入要插入的元素：");
            scanf("%d",&data6);    
            Insert(&list,n6,data6);
            printf("插入成功\n");        
            break;
        case 7:
            int data7;
            printf("请输入要插入的元素：");
            scanf("%d",&data7);    
            Outsert(&list,data7);
            printf("插入成功\n"); 
            break; 
        case 8:
            int n8;
            printf("请输入要删除的序号：");
            scanf("%d",&n8);    
            Delete(&list,n8);
            printf("删除成功\n"); 
            break; 
        case 9:
            int n9;
            printf("请输入查找元素的位：");
            scanf("%d",&n9);    
            Get(&list,n9);
            break; 
        case 10:
            int data10,n10;
            printf("请输入要查找的元素的值：");
            scanf("%d",&data10);    
            n10=Locate(&list,data10);
            printf("第%d位\n",n10); 
            break; 
        case 11:
            PrintList(&list);
            printf("遍历结束\n");
            break;
        case 12:
            int n12;
            n12=Length(&list);
            printf("列表元素个数为：%d\n",n12);
            break;
        case 13:
            int data13,n13;
            printf("请输入要查找后继的元素：");
            scanf("%d",&data13);
            n13=OutLocate(&list,data13);
            printf("%d的后继元素是%d\n",data13,list.data[n13]);
            break;

        default:
            printf("输入不符合规范\n");
            break;
        }
    }
    return 0;
}



//初始化
void InitList(List* list)
{
    list->length = 0;//初始长度为0
}

//存入
int CreatList(List* list,DataType data[],int n)
{
    if(n > MAXSIZE)//判断储存空间是否充足
    {
        printf("储存空间不足。");
        return 0;//不充足返回false
    }
    for(int i=0;i<n;i++)//将数组中的数据存入顺序表中
    {
        list->data[i]=data[i];
    }
    list->length=n;//存入数据元素的个数
    return 1;
}

//销毁
//顺序表是静态储存分配，在顺序表变量退出作用域时，自动释放内存。因此，无需销毁

//判空操作
int Empty(List* list)
{
    if(list->length == 0) return 1;//空，返回1
    else return 0;
}

//求顺序表的长度
int Length(List* list)
{
    return list->length;
}

//遍历操作
void PrintList(List* list)
{

    for(int i=0; i< list->length;i++)
    {
        printf("%d ",list->data[i]);//输出
    }
    printf("\n");
    
}


//按值查找(假设没有重复的值)
int Locate(List* list,DataType data)
{
    for(int i=0;i < list->length;i++)
    {
        if(list->data[i] == data)
        {
            return i+1;//找到返回序号
        }
    }
    return 0;//没有找到，返回0
}

//按位查找
int Get(List* list, int n)
{
    if(n<1 || n>list->length)
    {
        printf("此位数不存在");
        return 0;
    }
    else{
        printf("%d\n",list->data[n-1]);
        return 1;
    }
}


//中间插入
int Insert(List* list,int n,DataType data)
{
    if(list->length >= MAXSIZE)
    {
        printf("储存空间不足。");
        return 0;//不充足返回false
    }
    if(n<1 || n>list->length+1)
    {
        printf("插入位置出现错误。");
        return 0;     
    }
    for(int i=list->length;i>=n;i--)
    {
        list->data[i]=list->data[i-1];
    }
    list->data[n-1]=data;
    list->length++;
    return 1;
}

//最后插入
int Outsert(List* list,DataType data){
    if(list->length >= MAXSIZE)
    {
        printf("储存空间不足。");
        return 0;//不充足返回false
    }
    list->data[list->length++]=data;
    return 1;
}


//删除
int Delete(List* list,int n)
{
    if(list->length == 0)
    {
        printf("栈空，无法删除");
        return 0;
    }
    if(n<1 || n>list->length+1)
    {
        printf("插入位置出现错误。");
        return 0;     
    }
    for(int i=n;i<list->length-1;i++)
    {
        list->data[i-1]=list->data[i];
    }
    list->length--;
    return 1;
}

//清空表
void ClearList(List* list) {
    list->length = 0;
}

//获得前驱
int InLocate(List* list,DataType data)
{
    for(int i=0;i < list->length;i++)
    {
        if(list->data[i] == data)
        {
            return i-1;//找到返回序号
        }
    }
    return -1;//没有找到，返回-1
}

//获得后继
int OutLocate(List* list,DataType data)
{
    for(int i=0;i < list->length;i++)
    {
        if(list->data[i] == data)
        {
            return i+1;//找到返回序号
        }
    }
    return -1;//没有找到，返回-1
}

//打开并读取文件
int ReadFile(const char* filename,List* list)
{
    FILE* fp=fopen(filename,"r");
    if(fp==NULL){printf("打开文件失败。\n");return 0;}

    
    int n=0;
    char buffer[30];
    int datas[MAXSIZE];

    while (fgets(buffer,sizeof(buffer),fp) != NULL)
    {
        sscanf(buffer,"%d",&datas[n++]);
    }

    CreatList(list,datas,n);//n为存入的数据的个数
    fclose(fp);
    return 1;
}

//打开并存入文件
int WriteFile(const char* filename,List* list)
{
    FILE* fp=fopen(filename,"w");
    if(fp==NULL){printf("打开文件失败。\n");return 0;}  

    for(int i=0;i<list->length;i++)
    {
        printf("%d ",list->data[i]);
        fprintf(fp,"%d\n",list->data[i]);
    }
    fclose(fp);
    return 1;
}

//页面
void mainlist()
{
    printf("1.退出程序\t2.读取文本文件到列表\n");
    printf("3.清空列表\t4.存入文本文件\n");
    printf("5.获得前驱元素\t6.中间插入元素\n");
    printf("7.最后插入元素\t8.删除中间元素\n");
    printf("9.按位查找元素\t10.按值查找元素\n");
    printf("11.遍历列表\t12.获得列表元素个数\n");
    printf("13.获得后继元素\n");
}
