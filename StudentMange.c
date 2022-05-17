#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    int score;
    char *name;
    char *id;
    struct Student *next;
} Student;

void create(Student *manage, int score, char *name, char *id) {
    Student *stu = malloc(sizeof(Student));
    stu->score = score;
    stu->name = calloc(10, sizeof(char));
    stu->id = calloc(10, sizeof(char));
    strcpy(stu->name, name);
    strcpy(stu->id, id);
    stu->next = manage->next;
    manage->next = stu;
}

void delete(Student *manage, char *res) {
    Student *pre;
    Student *cur;
    pre = manage;
    cur = manage->next;
    //删除节点
    while (cur != NULL) {
        if (strcmp(cur->name, res) == 0 || strcmp(cur->id, res) == 0) {
            pre->next = cur->next;
            free(cur);
            return;
        } else {
            pre = pre->next;
            cur = cur->next;
        }
    }
}

void display(struct Student *manage) {
    Student *cur = manage->next;
    while (cur != NULL) {
        printf("name:%s Id:%s  score:%d\n", cur->name, cur->id, cur->score);
        cur = cur->next;
    }
}

void dispAverageScore(struct Student *manage) {
    Student *cur = manage->next;
    int sum = 0;
    int num = 0;
    while (cur != NULL) {
        sum += cur->score;
        cur = cur->next;
        num++;
    }
    float sum1 = sum;
    printf("\nAverage Score:%f\n", sum1 / num);
}

int main() {
    //manage为头结点，不储存信息
    Student *manage = malloc(sizeof(Student));
    manage->next = NULL;
    while (1) {
        int choice;
        printf("\n0:Quit 1:Insert 2:Average Score  3:Delete 4:Display   Your choice:");
        scanf("%d", &choice);
        getchar();
        char *name = calloc(10, sizeof(char));
        char *id = calloc(10, sizeof(char));
        int score;
        switch (choice) {
            case 0:
                return 1;
            case 1:
                printf("name:");
                gets(name);
                printf("Id:");
                gets(id);
                printf("Score:");
                scanf("%d", &score);
                getchar();
                create(manage, score, name, id);
                break;
            case 2:
                dispAverageScore(manage);
                break;
            case 3: {
                printf("Id or Name:");
                gets(name);
                delete(manage, name);
                break;
            }
            case 4:
                display(manage);
                break;
        }
        free(name);
        free(id);
    }
}
