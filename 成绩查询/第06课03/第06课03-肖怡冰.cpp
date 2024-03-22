#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEVEL 5 // 最大层数

// 定义跳表节点
typedef struct SkipNode {
    struct Student *data;
    struct SkipNode **forward;
} SkipNode;

// 定义学生结构体
struct Student {
    int number;
    int id;         // 学号
    char name[50];  // 姓名
    char gender[10];
    char major[50];
    int score1;
    int score2;
    int score3;
    float average;  // 平均成绩
};

// 定义跳表
typedef struct SkipList {
    int level;
    struct SkipNode *header;
} SkipList;

// 创建跳表节点
SkipNode* createNode(struct Student *data, int level) {
    SkipNode *node = (SkipNode*)malloc(sizeof(SkipNode));
    node->data = data;
    node->forward = (SkipNode**)malloc(sizeof(SkipNode*) * (level + 1));
    return node;
}

// 创建跳表
SkipList* createSkipList() {
    SkipList *list = (SkipList*)malloc(sizeof(SkipList));
    list->level = 0;
    list->header = createNode(NULL, MAX_LEVEL);
    for (int i = 0; i <= MAX_LEVEL; i++) {
        list->header->forward[i] = NULL;
    }
    return list;
}

// 生成随机层数
int randomLevel() {
    int level = 0;
    while (rand() % 2 && level < MAX_LEVEL) {
        level++;
    }
    return level;
}

// 插入节点
void insert(SkipList *list, struct Student *data) {
    SkipNode *update[MAX_LEVEL + 1];
    SkipNode *current = list->header;
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->data->average < data->average) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    current = current->forward[0];
    if (current == NULL || current->data->average != data->average) {
        int new_level = randomLevel();
        if (new_level > list->level) {
            for (int i = list->level + 1; i <= new_level; i++) {
                update[i] = list->header;
            }
            list->level = new_level;
        }
        SkipNode *new_node = createNode(data, new_level);
        for (int i = 0; i <= new_level; i++) {
            new_node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = new_node;
        }
    }
}

// 查找节点
struct Student* search(SkipList *list, float targetAverage) {
    SkipNode *current = list->header;
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->data->average < targetAverage) {
            current = current->forward[i];
        }
    }
    current = current->forward[0];
    if (current != NULL && current->data->average == targetAverage) {
        return current->data;
    }
    return NULL;
}

// 释放跳表
void freeSkipList(SkipList *list) {
    SkipNode *current = list->header->forward[0];
    while (current != NULL) {
        SkipNode *next = current->forward[0];
        free(current->forward);
        free(current);
        current = next;
    }
    free(list->header->forward);
    free(list->header);
    free(list);
}

// 按学号查询节点
struct Student* searchByStudentNumber(SkipList *list, int targetNumber) {
    SkipNode *current = list->header->forward[0]; // Start from the first node
    while (current != NULL) {
        if (current->data != NULL && current->data->id == targetNumber) {
            return current->data;
        }
        current = current->forward[0];
    }
    return NULL;
}




// 按姓名查询节点
struct Student* searchByStudentName(SkipList *list, const char *targetName) {
    SkipNode *current = list->header->forward[0];
    while (current != NULL) {
        if (current->data != NULL && strcmp(current->data->name, targetName) == 0) {
            return current->data;
        }
        current = current->forward[0];
    }
    return NULL;
}


// 主函数
int main() {
    // 打开文件
    FILE *file = fopen("chengji.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // 创建跳表
    SkipList *list = createSkipList();

    // 读取文件并插入到跳表中
    while (!feof(file)) {
        struct Student *student = (struct Student*)malloc(sizeof(struct Student));
        if (fscanf(file, "%d,%d,%49[^,],%9[^,],%49[^,],%d,%d,%d,%f",
                   &student->number,
                   &student->id,
                   student->name,
                   student->gender,
                   student->major,
                   &student->score1,
                   &student->score2,
                   &student->score3,
                   &student->average) == 9) {
            insert(list, student);
        } else {
            free(student);
        }
    }

    fclose(file); // 关闭文件
while(1){

    int choice;
    printf("\n主界面:\n");
    printf("1. 按平均成绩查询\n");
    printf("2. 按学号查询\n");
    printf("3. 按姓名查询\n");
    printf("0. 退出\n");
    printf("在这里输入你的选择: ");
    scanf("%d", &choice);

    switch (choice) {
        case 0:
            printf("退出程序。\n");
            break;
        case 1: {
            // 查找平均成绩
            float targetAverage;
            printf("请输入要查找的平均成绩: ");
            scanf("%f", &targetAverage);
            struct Student *result = search(list, targetAverage);
            if (result != NULL) {
            printf("   学号     姓名  性别    班级    进制转换 多进制转换 数值表达逻辑代数 平均成绩\n");
            printf("%d  %s  %s   %s      %d      %d             %d                %.2f\n",
                       result->id, result->name, result->gender, result->major,
                       result->score1, result->score2, result->score3, result->average);
                       printf("怎么弄都无法输出多个，要崩溃了，谁来救救我————\n"); 
            } else {
                printf("未找到该平均成绩的学生。\n");
            }
            break;
        }
        case 2: {
            // 按学号查询
            int targetNumber;
            printf("请输入要查找的学号: ");
            scanf("%d", &targetNumber);
            struct Student *result = searchByStudentNumber(list, targetNumber);
            if (result != NULL) {
            printf("   学号     姓名  性别    班级    进制转换 多进制转换 数值表达逻辑代数 平均成绩\n");
            printf("%d  %s  %s   %s      %d      %d             %d                %.2f\n",
                       result->id, result->name, result->gender, result->major,
                       result->score1, result->score2, result->score3, result->average);
                       
            } else {
                printf("未找到该学号的学生。\n");
            }
            break;
        }
        case 3: {
            // 按姓名查询
            char targetName[50];
            printf("请输入要查找的姓名: ");
            scanf("%s", targetName);
            struct Student *result = searchByStudentName(list, targetName);
            if (result != NULL) {
            printf("   学号     姓名  性别    班级    进制转换 多进制转换 数值表达逻辑代数 平均成绩\n");
            printf("%d  %s  %s   %s      %d      %d             %d                %.2f\n",
                       result->id, result->name, result->gender, result->major,
                       result->score1, result->score2, result->score3, result->average);
            } else {
                printf("未找到该姓名的学生。\n");
            }
            break;
        }
        default:
            printf("无效的选择。\n");
    }}

    // 释放跳表
    freeSkipList(list);

    return 0;
}


