#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 100 // ����LENΪ100

// ����ѧ���ṹ��
struct Student {
    int id;
    long long studentNumber; // �޸�Ϊlong long���ͣ�ƥ���ļ��е�ѧ�Ÿ�ʽ
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

void Line_line(char *str) {
    // �����ַ��������ո��滻Ϊ0
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
        perror("�޷����ļ�");
        return NULL;
    }

    char buffer[LEN]; // �޸�Ϊ�����LEN
    head = s1 = s2 = NULL; // ɾ��highest��lowest������������δ����
    n = 0;

    // ȥ����һ�еġ�����������ѧ�š�
    if (fgets(buffer, sizeof(buffer), filePointer) != NULL) {
        //Line_line(buffer);
        strcpy(namee, buffer);//strcat(namee, "ƽ����");  // ��"ƽ����"ƴ�ӵ�namee
            char *newlinePos = strstr(namee, "\n");
        // ���ҵ��Ļ��з��滻Ϊ"aa\n"
        strncpy(newlinePos, ",ƽ����\n", 9);
        //printf("%s",namee);
         //printf("%s",buffer);
    }

    // β�巨��������
    while (fgets(buffer, sizeof(buffer), filePointer) != NULL) {
        Line_line(buffer);

        s1 = (struct Student *)malloc(sizeof(struct Student)); // ����ռ�
        // ���ַ����а���ָ���ĸ�ʽ�������ݲ�����洢��������
        sscanf(buffer, "%d,%lld,%19[^,],%4[^,],%19[^,],%d,%d,%d",
               &s1->id, &s1->studentNumber, s1->name, s1->gender, s1->major,
               &s1->score1, &s1->score2, &s1->score3);
        s1->average = (s1->score1 + s1->score2 + s1->score3) / 3.0;
        n = n + 1;

        if (n == 1) { // ��һ��
            head = s1;
        } else {
            s2->next = s1;
        }

        s2 = s1;
        s1->next = NULL; // �ýڵ��������ĩβ��û����һ���ڵ�
    }

    fclose(filePointer); // �ر��ļ�
    return head; // ��������ͷָ��
}

// ��ѧ����Ϣд���ļ��ĺ���
void writeStudentsToFile(const char *filename,struct Student* head) {
    FILE* file = fopen(filename, "w"); // ���ļ���"w"��ʾд��ģʽ

    if (file == NULL) {
        fprintf(stderr, "�޷����ļ�\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file,"%s",namee);
    // ����������ѧ����Ϣд���ļ�
    struct Student* current = head;
    while (current != NULL) {
        fprintf(file, "%d,%lld,%s,%s,%s,%d,%d,%d,%.2f\n", current->id,current->studentNumber,current->name,current->gender,current->major,current->score1,current->score2,current->score3,current->average);
        
        current = current->next;
    }

    fclose(file); // �ر��ļ�
}
// �������
void clearList(struct Student* head) {
    struct Student* current = head;
    struct Student* nextStudent;

    while (current != NULL) {
        nextStudent = current->next;
        free(current);  // �ͷŵ�ǰ�ڵ���ڴ�
        current = nextStudent;
    }
}
int main() {
	
    // �����һ���ļ�
    struct Student *head1 = creats("598854�γ�.txt");
    writeStudentsToFile("598854�γ�new.txt", head1);
    clearList(head1);

    // ����ڶ����ļ�
    struct Student *head2 = creats("598856�γ�.txt");
    writeStudentsToFile("598856�γ�new.txt", head2);
    clearList(head2);

    // ����������ļ�
    struct Student *head3 = creats("598858�γ�.txt");
    writeStudentsToFile("598858�γ�new.txt", head3);
    clearList(head3);


    
   return 0;
}

