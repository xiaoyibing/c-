#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//�ṹ�崢��һ������
struct Student {
    int number;
    int id;//ѧ��
    char name[50];//����
    char gender[10];
    char major[50];
    int score1;
    int score2;
    int score3;
    float average;//ƽ���ɼ�
};


//----------------�ȽϺ���������----------------
//ͨ��ƽ���ɼ��Ƚϣ�����
int compareByAverage(const void *a, const void *b) {
    return ((struct Student *)a)->average - ((struct Student *)b)->average;
}
//ͨ��ѧ�űȽ�
int compareById(const void *a, const void *b) {
    return ((struct Student *)a)->id - ((struct Student *)b)->id;
}
//ͨ�������Ƚ�
int compareByName(const void *a, const void *b) {
    return strcmp(((struct Student *)a)->name, ((struct Student *)b)->name);
}


//----------------���ַ�����-------------------
//����ѧ��
int SearchById(int targetId, struct Student students[], int count) {
    int left = 0, right = count - 1;//��ʼ�����ұ߽�

    while (left <= right) {//������Χ��Ч
        int mid = left + (right - left) / 2;//�����м�����
        if (students[mid].id == targetId) {
            return mid;// �ҵ���Ŀ��ID������Ԫ���������е�����
        } else if (students[mid].id < targetId) {//��������
            left = mid + 1; // Ŀ��ID���Ұ벿�֣���С������Χ
        } else {
            right = mid - 1; // Ŀ��ID����벿�֣���С������Χ
        }
    }
    return -1; // û���ҵ�������-1��ʾδ�ҵ�
}

//����ƽ���ɼ�
int SearchByAverage(float targetAverage, struct Student students[], int count) {
    int left = 0, right = count - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (students[mid].average == targetAverage) {
            return mid; 
        } else if (students[mid].average < targetAverage) {
            left = mid + 1; 
        } else {
            right = mid - 1;
        }
    }

    return -1; 
}
//��������
int SearchByName(const char *targetName, struct Student students[], int count) {
    int left = 0, right = count - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmpResult = strcmp(students[mid].name, targetName);
        if (cmpResult == 0) {
            return mid; 
        } else if (cmpResult < 0) {
            left = mid + 1; 
        } else {
            right = mid - 1; 
        }
    }

    return -1; 
}
//------------������-------------------
int main() {
//���ļ�
    FILE *file = fopen("chengji.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
//��ȡ�ļ�
    int maxLines = 400; //������๲��400��
    struct Student students[maxLines];
    int count = 0;//��¼��ʵ������
//���뵽�����У�������
    while (count < maxLines &&
           fscanf(file, "%d,%d,%49[^,],%9[^,],%49[^,],%d,%d,%d,%f",
                  &students[count].number,
                  &students[count].id,
                  students[count].name,
                  students[count].gender,
                  students[count].major,
                  &students[count].score1,
                  &students[count].score2,
                  &students[count].score3,
                  &students[count].average) == 9) {
        count++;
    }
    fclose(file);//�ر��ļ�

    int choice;
    while (1) {
 //�����棨ѡ��
        printf("\n������:\n");
        printf("1. ��ƽ���ɼ���ѯ\n");
        printf("2. ��ѧ�Ų�ѯ\n");
        printf("3. ��������ѯ\n");
        printf("0. �˳�\n");
        printf("�������������ѡ��: ");
        scanf("%d", &choice);
        //ֱ���˳�
        if (choice == 0) {
            break;
        }

//��ʼ����
        if (choice == 1) {

            qsort(students, count, sizeof(struct Student), compareByAverage);
        } else if (choice == 2) {

            qsort(students, count, sizeof(struct Student), compareById);
        }
		else if(choice == 3) {

            qsort(students, count, sizeof(struct Student), compareByName);
		} else {
            printf("��ѡ�� 0, 1,2, or 3.\n");
            continue; //û�а��չ������루������
        }


  //��ʼ����
        int targetIndex;
        if (choice == 1) {
            float targetAverage;
            printf("����������ƽ���ɼ�: ");
            scanf("%f", &targetAverage);
            targetIndex = SearchByAverage(targetAverage, students, count);//���ú�������
        } else if (choice == 2) {
            int targetId;
            printf("����������ѧ��: ");
            scanf("%d", &targetId);
            targetIndex = SearchById(targetId, students, count);
        }else if (choice ==3){
            char targetName[50];
            printf("��������������: ");
            scanf("%49s", &targetName);
            targetIndex = SearchByName(targetName, students, count);
		}
//������Լ�����ƽ���ɼ���
        if (targetIndex != -1) {//����ҵ���
            printf("����:\n");
            
            //����ö��ַ����ҵĽ��
            printf("   ѧ��     ����  �Ա�    �༶    ����ת�� �����ת�� ��ֵ����߼����� ƽ���ɼ�\n");
            printf("%d  %s  %s   %s      %d      %d             %d                %.2f\n",
                   students[targetIndex].id,
                   students[targetIndex].name,
                   students[targetIndex].gender,
                   students[targetIndex].major,
                   students[targetIndex].score1,
                   students[targetIndex].score2,
                   students[targetIndex].score3,
                   students[targetIndex].average);
                   
                   
            //ƽ���ɼ��ж�����Ѿ��ź����ˣ��������������
            int leftIndex = targetIndex - 1;
            //ѭ��������ߵ�һ���������м�ʱֹͣ����Ϊ�Ѿ��ź����ˣ���ͬ�ĳɼ�������һ��
            while (leftIndex >= 0 && students[leftIndex].average == students[targetIndex].average) { 
				printf("%d  %s  %s   %s      %d      %d             %d                %.2f\n",
                       students[leftIndex].id,
                       students[leftIndex].name,
                       students[leftIndex].gender,
                       students[leftIndex].major,
                       students[leftIndex].score1,
                       students[leftIndex].score2,
                       students[leftIndex].score3,
                       students[leftIndex].average);
                leftIndex--;
            }

            //���Ҳ���
            int rightIndex = targetIndex + 1;
            while (rightIndex < count && students[rightIndex].average == students[targetIndex].average) {
				printf("%d  %s  %s   %s      %d      %d             %d                %.2f\n",
                       students[rightIndex].id,
                       students[rightIndex].name,
                       students[rightIndex].gender,
                       students[rightIndex].major,
                       students[rightIndex].score1,
                       students[rightIndex].score2,
                       students[rightIndex].score3,
                       students[rightIndex].average);
                rightIndex++;
            }
        } else {//���ַ�û�ҵ�
            printf("���޴���\n");
        }
    }
    return 0;
}

