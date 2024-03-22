#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEVEL 5 // ������

// ��������ڵ�
typedef struct SkipNode {
    struct Student *data;
    struct SkipNode **forward;
} SkipNode;

// ����ѧ���ṹ��
struct Student {
    int number;
    int id;         // ѧ��
    char name[50];  // ����
    char gender[10];
    char major[50];
    int score1;
    int score2;
    int score3;
    float average;  // ƽ���ɼ�
};

// ��������
typedef struct SkipList {
    int level;
    struct SkipNode *header;
} SkipList;

// ��������ڵ�
SkipNode* createNode(struct Student *data, int level) {
    SkipNode *node = (SkipNode*)malloc(sizeof(SkipNode));
    node->data = data;
    node->forward = (SkipNode**)malloc(sizeof(SkipNode*) * (level + 1));
    return node;
}

// ��������
SkipList* createSkipList() {
    SkipList *list = (SkipList*)malloc(sizeof(SkipList));
    list->level = 0;
    list->header = createNode(NULL, MAX_LEVEL);
    for (int i = 0; i <= MAX_LEVEL; i++) {
        list->header->forward[i] = NULL;
    }
    return list;
}

// �����������
int randomLevel() {
    int level = 0;
    while (rand() % 2 && level < MAX_LEVEL) {
        level++;
    }
    return level;
}

// ����ڵ�
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

// ���ҽڵ�
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

// �ͷ�����
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

// ��ѧ�Ų�ѯ�ڵ�
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




// ��������ѯ�ڵ�
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


// ������
int main() {
    // ���ļ�
    FILE *file = fopen("chengji.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // ��������
    SkipList *list = createSkipList();

    // ��ȡ�ļ������뵽������
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

    fclose(file); // �ر��ļ�
while(1){

    int choice;
    printf("\n������:\n");
    printf("1. ��ƽ���ɼ���ѯ\n");
    printf("2. ��ѧ�Ų�ѯ\n");
    printf("3. ��������ѯ\n");
    printf("0. �˳�\n");
    printf("�������������ѡ��: ");
    scanf("%d", &choice);

    switch (choice) {
        case 0:
            printf("�˳�����\n");
            break;
        case 1: {
            // ����ƽ���ɼ�
            float targetAverage;
            printf("������Ҫ���ҵ�ƽ���ɼ�: ");
            scanf("%f", &targetAverage);
            struct Student *result = search(list, targetAverage);
            if (result != NULL) {
            printf("   ѧ��     ����  �Ա�    �༶    ����ת�� �����ת�� ��ֵ����߼����� ƽ���ɼ�\n");
            printf("%d  %s  %s   %s      %d      %d             %d                %.2f\n",
                       result->id, result->name, result->gender, result->major,
                       result->score1, result->score2, result->score3, result->average);
                       printf("��ôŪ���޷���������Ҫ�����ˣ�˭���Ⱦ��ҡ�������\n"); 
            } else {
                printf("δ�ҵ���ƽ���ɼ���ѧ����\n");
            }
            break;
        }
        case 2: {
            // ��ѧ�Ų�ѯ
            int targetNumber;
            printf("������Ҫ���ҵ�ѧ��: ");
            scanf("%d", &targetNumber);
            struct Student *result = searchByStudentNumber(list, targetNumber);
            if (result != NULL) {
            printf("   ѧ��     ����  �Ա�    �༶    ����ת�� �����ת�� ��ֵ����߼����� ƽ���ɼ�\n");
            printf("%d  %s  %s   %s      %d      %d             %d                %.2f\n",
                       result->id, result->name, result->gender, result->major,
                       result->score1, result->score2, result->score3, result->average);
                       
            } else {
                printf("δ�ҵ���ѧ�ŵ�ѧ����\n");
            }
            break;
        }
        case 3: {
            // ��������ѯ
            char targetName[50];
            printf("������Ҫ���ҵ�����: ");
            scanf("%s", targetName);
            struct Student *result = searchByStudentName(list, targetName);
            if (result != NULL) {
            printf("   ѧ��     ����  �Ա�    �༶    ����ת�� �����ת�� ��ֵ����߼����� ƽ���ɼ�\n");
            printf("%d  %s  %s   %s      %d      %d             %d                %.2f\n",
                       result->id, result->name, result->gender, result->major,
                       result->score1, result->score2, result->score3, result->average);
            } else {
                printf("δ�ҵ���������ѧ����\n");
            }
            break;
        }
        default:
            printf("��Ч��ѡ��\n");
    }}

    // �ͷ�����
    freeSkipList(list);

    return 0;
}


