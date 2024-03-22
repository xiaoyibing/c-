#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//结构体储存一行数据
struct Student {
    int number;
    int id;//学号
    char name[50];//姓名
    char gender[10];
    char major[50];
    int score1;
    int score2;
    int score3;
    float average;//平均成绩
};


//----------------比较函数（升序）----------------
//通过平均成绩比较（升序）
int compareByAverage(const void *a, const void *b) {
    return ((struct Student *)a)->average - ((struct Student *)b)->average;
}
//通过学号比较
int compareById(const void *a, const void *b) {
    return ((struct Student *)a)->id - ((struct Student *)b)->id;
}
//通过姓名比较
int compareByName(const void *a, const void *b) {
    return strcmp(((struct Student *)a)->name, ((struct Student *)b)->name);
}


//----------------二分法查找-------------------
//查找学号
int SearchById(int targetId, struct Student students[], int count) {
    int left = 0, right = count - 1;//初始化左右边界

    while (left <= right) {//搜索范围有效
        int mid = left + (right - left) / 2;//计算中间行数
        if (students[mid].id == targetId) {
            return mid;// 找到了目标ID，返回元素在数组中的索引
        } else if (students[mid].id < targetId) {//升序排序
            left = mid + 1; // 目标ID在右半部分，缩小搜索范围
        } else {
            right = mid - 1; // 目标ID在左半部分，缩小搜索范围
        }
    }
    return -1; // 没有找到，返回-1表示未找到
}

//查找平均成绩
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
//查找姓名
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
//------------主函数-------------------
int main() {
//打开文件
    FILE *file = fopen("chengji.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
//读取文件
    int maxLines = 400; //假设最多共有400行
    struct Student students[maxLines];
    int count = 0;//记录真实的行数
//输入到数组中（非排序）
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
    fclose(file);//关闭文件

    int choice;
    while (1) {
 //主界面（选择）
        printf("\n主界面:\n");
        printf("1. 按平均成绩查询\n");
        printf("2. 按学号查询\n");
        printf("3. 按姓名查询\n");
        printf("0. 退出\n");
        printf("在这里输入你的选择: ");
        scanf("%d", &choice);
        //直接退出
        if (choice == 0) {
            break;
        }

//开始排序
        if (choice == 1) {

            qsort(students, count, sizeof(struct Student), compareByAverage);
        } else if (choice == 2) {

            qsort(students, count, sizeof(struct Student), compareById);
        }
		else if(choice == 3) {

            qsort(students, count, sizeof(struct Student), compareByName);
		} else {
            printf("请选择 0, 1,2, or 3.\n");
            continue; //没有按照规则输入（继续）
        }


  //开始查找
        int targetIndex;
        if (choice == 1) {
            float targetAverage;
            printf("在这里输入平均成绩: ");
            scanf("%f", &targetAverage);
            targetIndex = SearchByAverage(targetAverage, students, count);//调用函数查找
        } else if (choice == 2) {
            int targetId;
            printf("在这里输入学号: ");
            scanf("%d", &targetId);
            targetIndex = SearchById(targetId, students, count);
        }else if (choice ==3){
            char targetName[50];
            printf("在这里输入姓名: ");
            scanf("%49s", &targetName);
            targetIndex = SearchByName(targetName, students, count);
		}
//输出（以及所有平均成绩）
        if (targetIndex != -1) {//如果找到了
            printf("如下:\n");
            
            //输出用二分法查找的结果
            printf("   学号     姓名  性别    班级    进制转换 多进制转换 数值表达逻辑代数 平均成绩\n");
            printf("%d  %s  %s   %s      %d      %d             %d                %.2f\n",
                   students[targetIndex].id,
                   students[targetIndex].name,
                   students[targetIndex].gender,
                   students[targetIndex].major,
                   students[targetIndex].score1,
                   students[targetIndex].score2,
                   students[targetIndex].score3,
                   students[targetIndex].average);
                   
                   
            //平均成绩有多个（已经排好序了），继续向左查找
            int leftIndex = targetIndex - 1;
            //循环，当左边的一个不等于中间时停止（因为已经排好序了，相同的成绩都挨在一起）
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

            //向右查找
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
        } else {//二分法没找到
            printf("查无此人\n");
        }
    }
    return 0;
}

