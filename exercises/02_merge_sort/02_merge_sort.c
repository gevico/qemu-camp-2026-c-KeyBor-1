#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
    int score;
} Student;

Student students[MAX_STUDENTS];
Student temp[MAX_STUDENTS];
void merge(int l_s, int l_e, int r_s, int r_e) {
    int i = l_s;
    int j = r_s;
    int k = l_s;
    
    // 合并两个有序段
    while(i <= l_e && j <= r_e) {
        if(students[i].score >= students[j].score) {
            temp[k++] = students[i++];
        } else {
            temp[k++] = students[j++];
        }
    }
    
    // 复制左段剩余元素
    while(i <= l_e) {
        temp[k++] = students[i++];
    }
    
    // 复制右段剩余元素
    while(j <= r_e) {
        temp[k++] = students[j++];
    }
    
    // 用 memcpy 替代循环复制回原数组
    memcpy(&students[l_s], &temp[l_s], (r_e - l_s + 1) * sizeof(Student));
}

void merge_sort(int left, int right) {
    if(left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    // printf("left %d right %d mid %d\n", left, right, mid);
    merge_sort(left, mid);
    merge_sort(mid + 1, right);
    merge(left , mid , mid + 1, right);
}

int main(void) {
    FILE *file = fopen("02_students.txt", "r");
    if (!file) {
        printf("错误：无法打开文件 02_students.txt\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);

    if (n <= 0 || n > MAX_STUDENTS) {
        printf("学生人数无效：%d\n", n);
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%s %d", students[i].name, &students[i].score);
    }
    fclose(file);

    merge_sort(0, n - 1);
    printf("\n归并排序后按成绩从高到低排序的学生名单：\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].name, students[i].score);
    }

    return 0;
}