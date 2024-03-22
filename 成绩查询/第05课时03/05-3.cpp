#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LEN 100 // 定义LEN为100

// 定义学生结构体
struct Student {
    int id;
    long long int studentNumber;
    char name[20];
    char gender[5];
    char major[20];
    int score1;
    int score2;
    int score3;
    float average; // 平均成绩
    struct Student* next; // 指向下一个学生的指针
};

int n;

struct Student* head = NULL;  // 全局变量，链表头指针

struct Student* creats(const char* filename) {
    struct Student* s1, *s2;

    FILE* filePointer;
    filePointer = fopen(filename, "r");

    if (filePointer == NULL) {
        perror("无法打开文件");
        return NULL;
    }

    char buffer[LEN];
    n = 0;

    // 尾插法构建链表
    while (fgets(buffer, sizeof(buffer), filePointer) != NULL) {
        s1 = (struct Student*)malloc(sizeof(struct Student)); // 分配空间

        if (s1 == NULL) {
            fprintf(stderr, "内存分配失败\n");
            fclose(filePointer);
            return NULL;
        }

        // 从字符串中按照指定的格式解析数据并将其存储到变量中
        sscanf(buffer, "%d,%lld,%19[^,],%4[^,],%19[^,],%d,%d,%d,%f",
            &s1->id, &s1->studentNumber, s1->name, s1->gender, s1->major,
            &s1->score1, &s1->score2, &s1->score3, &s1->average);

        n = n + 1;

        if (n == 1) { // 第一行
            head = s1;
        }
        else {
            s2->next = s1;
        }

        s2 = s1;
        s1->next = NULL; // 该节点是链表的末尾，没有下一个节点
    }

    fclose(filePointer); // 关闭文件
    return head; // 返回链表头指针
}

// 根据姓名查询学生信息
void queryStudentByName(struct Student* head, const char* queryname) {
    struct Student* current = head;
    int found = 0;

    // 遍历链表查找匹配姓名的学生
    while (current != NULL) {
        if (strcmp(current->name, queryname) == 0) {
            printf("查询到学生信息：\n");
            printf("ID   学号    性别   班级       进制转换 多进制转换 数值表达逻辑代数 平均成绩 \n");
            printf("%d    %lld  %s   %s      %d       %d         %d             %.2f\n", current->id, current->studentNumber, current->gender, current->major, current->score1, current->score2, current->score3, current->average);

            found = 1;
            break; // 找到匹配的学生后结束循环
        }

        current = current->next;
    }
}

// 根据 学号 查询学生信息
void queryStudentByNumber(struct Student* head, long long int querynumber) {
    struct Student* current = head;
    int found = 0;

    // 遍历链表查找匹配 学号 的学生
    while (current != NULL) {
        if (current->studentNumber == querynumber) {
            printf("查询到学生信息：\n");
            printf("ID  姓名   性别   班级       进制转换 多进制转换 数值表达逻辑代数 平均成绩 \n");
            printf("%d  %s %s   %s      %d       %d         %d           %.2f\n", current->id, current->name, current->gender, current->major, current->score1, current->score2, current->score3, current->average);

            found = 1;
            break; // 找到匹配的学生后结束循环
        }

        current = current->next;
    }
}

bool determine(char x[]) {//用来判断输入的是学号还是姓名
    if ('0' <= x[0] && x[0] <= '9') {
        return false;
    }
    return true;
}

void yn(char query[]) {
    // 判断是姓名还是学号，并调用相应的查询函数
    if (determine(query)) {
        queryStudentByName(head, query);
    }
    else {
        long long int number;
        sscanf(query, "%lld", &number);
        queryStudentByNumber(head, number);
    }
}

int main() {
    // 输入要查询的学生姓名或者学号
    char query[20];
    char QQQ = '0';
    printf("请输入要查询的学生姓名或者学号：");
    scanf("%s", query);
    while (QQQ != 'N') {

        struct Student* head1 = creats("598854课程new.txt");
        yn(query);
        struct Student* head2 = creats("598856课程new.txt");
        yn(query);
        struct Student* head3 = creats("598858课程new.txt");
        // 调用 yn 函数进行查询
        yn(query);
        printf("请输入要查询的学生姓名或者学号(按N退出)：");
        scanf("%s", query);
        if (strcmp(query, "N") == 0) {
            QQQ = 'N';
        }
    }

    return 0;
}


