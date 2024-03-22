#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LEN 100 // ����LENΪ100

// ����ѧ���ṹ��
struct Student {
    int id;
    long long int studentNumber;
    char name[20];
    char gender[5];
    char major[20];
    int score1;
    int score2;
    int score3;
    float average; // ƽ���ɼ�
    struct Student* next; // ָ����һ��ѧ����ָ��
};

int n;

struct Student* head = NULL;  // ȫ�ֱ���������ͷָ��

struct Student* creats(const char* filename) {
    struct Student* s1, *s2;

    FILE* filePointer;
    filePointer = fopen(filename, "r");

    if (filePointer == NULL) {
        perror("�޷����ļ�");
        return NULL;
    }

    char buffer[LEN];
    n = 0;

    // β�巨��������
    while (fgets(buffer, sizeof(buffer), filePointer) != NULL) {
        s1 = (struct Student*)malloc(sizeof(struct Student)); // ����ռ�

        if (s1 == NULL) {
            fprintf(stderr, "�ڴ����ʧ��\n");
            fclose(filePointer);
            return NULL;
        }

        // ���ַ����а���ָ���ĸ�ʽ�������ݲ�����洢��������
        sscanf(buffer, "%d,%lld,%19[^,],%4[^,],%19[^,],%d,%d,%d,%f",
            &s1->id, &s1->studentNumber, s1->name, s1->gender, s1->major,
            &s1->score1, &s1->score2, &s1->score3, &s1->average);

        n = n + 1;

        if (n == 1) { // ��һ��
            head = s1;
        }
        else {
            s2->next = s1;
        }

        s2 = s1;
        s1->next = NULL; // �ýڵ��������ĩβ��û����һ���ڵ�
    }

    fclose(filePointer); // �ر��ļ�
    return head; // ��������ͷָ��
}

// ����������ѯѧ����Ϣ
void queryStudentByName(struct Student* head, const char* queryname) {
    struct Student* current = head;
    int found = 0;

    // �����������ƥ��������ѧ��
    while (current != NULL) {
        if (strcmp(current->name, queryname) == 0) {
            printf("��ѯ��ѧ����Ϣ��\n");
            printf("ID   ѧ��    �Ա�   �༶       ����ת�� �����ת�� ��ֵ����߼����� ƽ���ɼ� \n");
            printf("%d    %lld  %s   %s      %d       %d         %d             %.2f\n", current->id, current->studentNumber, current->gender, current->major, current->score1, current->score2, current->score3, current->average);

            found = 1;
            break; // �ҵ�ƥ���ѧ�������ѭ��
        }

        current = current->next;
    }
}

// ���� ѧ�� ��ѯѧ����Ϣ
void queryStudentByNumber(struct Student* head, long long int querynumber) {
    struct Student* current = head;
    int found = 0;

    // �����������ƥ�� ѧ�� ��ѧ��
    while (current != NULL) {
        if (current->studentNumber == querynumber) {
            printf("��ѯ��ѧ����Ϣ��\n");
            printf("ID  ����   �Ա�   �༶       ����ת�� �����ת�� ��ֵ����߼����� ƽ���ɼ� \n");
            printf("%d  %s %s   %s      %d       %d         %d           %.2f\n", current->id, current->name, current->gender, current->major, current->score1, current->score2, current->score3, current->average);

            found = 1;
            break; // �ҵ�ƥ���ѧ�������ѭ��
        }

        current = current->next;
    }
}

bool determine(char x[]) {//�����ж��������ѧ�Ż�������
    if ('0' <= x[0] && x[0] <= '9') {
        return false;
    }
    return true;
}

void yn(char query[]) {
    // �ж�����������ѧ�ţ���������Ӧ�Ĳ�ѯ����
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
    // ����Ҫ��ѯ��ѧ����������ѧ��
    char query[20];
    char QQQ = '0';
    printf("������Ҫ��ѯ��ѧ����������ѧ�ţ�");
    scanf("%s", query);
    while (QQQ != 'N') {

        struct Student* head1 = creats("598854�γ�new.txt");
        yn(query);
        struct Student* head2 = creats("598856�γ�new.txt");
        yn(query);
        struct Student* head3 = creats("598858�γ�new.txt");
        // ���� yn �������в�ѯ
        yn(query);
        printf("������Ҫ��ѯ��ѧ����������ѧ��(��N�˳�)��");
        scanf("%s", query);
        if (strcmp(query, "N") == 0) {
            QQQ = 'N';
        }
    }

    return 0;
}


