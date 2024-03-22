#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 100 // 定义LEN为100

// 定义学生结构体
struct Student {
    int id;
    long long studentNumber; // 修改为long long类型，匹配文件中的学号格式
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

void Line_line(char *str) {
    // 遍历字符串，将空格替换为0
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ' ') {
            str[i] = '0';
        }
    }
}
char namee[100];
struct Student *creats(const char *filename) {
    struct Student *head, *s1, *s2;

    FILE *filePointer;
    filePointer = fopen(filename, "r");

    if (filePointer == NULL) {
        perror("无法打开文件");
        return NULL;
    }

    char buffer[LEN]; // 修改为定义的LEN
    head = s1 = s2 = NULL; // 删除highest和lowest，这两个变量未定义
    n = 0;

    // 去除第一行的“姓名”，“学号”
    if (fgets(buffer, sizeof(buffer), filePointer) != NULL) {
        //Line_line(buffer);
        strcpy(namee, buffer);//strcat(namee, "平均分");  // 将"平均分"拼接到namee
            char *newlinePos = strstr(namee, "\n");
        // 将找到的换行符替换为"aa\n"
        strncpy(newlinePos, ",平均分\n", 9);
        //printf("%s",namee);
         //printf("%s",buffer);
    }

    // 尾插法构建链表
    while (fgets(buffer, sizeof(buffer), filePointer) != NULL) {
        Line_line(buffer);

        s1 = (struct Student *)malloc(sizeof(struct Student)); // 分配空间
        // 从字符串中按照指定的格式解析数据并将其存储到变量中
        sscanf(buffer, "%d,%lld,%19[^,],%4[^,],%19[^,],%d,%d,%d",
               &s1->id, &s1->studentNumber, s1->name, s1->gender, s1->major,
               &s1->score1, &s1->score2, &s1->score3);
        s1->average = (s1->score1 + s1->score2 + s1->score3) / 3.0;
        n = n + 1;

        if (n == 1) { // 第一行
            head = s1;
        } else {
            s2->next = s1;
        }

        s2 = s1;
        s1->next = NULL; // 该节点是链表的末尾，没有下一个节点
    }

    fclose(filePointer); // 关闭文件
    return head; // 返回链表头指针
}

// 将学生信息写入文件的函数
void writeStudentsToFile(const char *filename,struct Student* head) {
    FILE* file = fopen(filename, "w"); // 打开文件，"w"表示写入模式

    if (file == NULL) {
        fprintf(stderr, "无法打开文件\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file,"%s",namee);
    // 遍历链表并将学生信息写入文件
    struct Student* current = head;
    while (current != NULL) {
        fprintf(file, "%d,%lld,%s,%s,%s,%d,%d,%d,%.2f\n", current->id,current->studentNumber,current->name,current->gender,current->major,current->score1,current->score2,current->score3,current->average);
        
        current = current->next;
    }

    fclose(file); // 关闭文件
}
// 清空链表
void clearList(struct Student* head) {
    struct Student* current = head;
    struct Student* nextStudent;

    while (current != NULL) {
        nextStudent = current->next;
        free(current);  // 释放当前节点的内存
        current = nextStudent;
    }
}
int main() {
	
    // 处理第一个文件
    struct Student *head1 = creats("598854课程.txt");
    writeStudentsToFile("598854课程new.txt", head1);
    clearList(head1);

    // 处理第二个文件
    struct Student *head2 = creats("598856课程.txt");
    writeStudentsToFile("598856课程new.txt", head2);
    clearList(head2);

    // 处理第三个文件
    struct Student *head3 = creats("598858课程.txt");
    writeStudentsToFile("598858课程new.txt", head3);
    clearList(head3);


    
   return 0;
}

