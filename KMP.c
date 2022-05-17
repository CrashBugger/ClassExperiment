#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100
//定义字符串，
typedef struct {
    //字符串长度
    int length;
    //字符串数据
    char *data;
} str;

//kmp算法求next数组
void GetNext(str *p, int *next) {
    int i = 0, k = -1;
    next[0] = -1;
    while (i < p->length - 1) {
        //k回溯
        while (k >= 0 && p->data[i] != p->data[k]) {
            k = next[k];
        }
        //回溯停止
        i++, k++;
        //相同则
        if (p->data[i] == p->data[k])
            next[i] = next[k];
        else
            next[i] = k;
    }
}

int KMPIndex(str *s, str *pattern) {
    int next[MAXSIZE];
    int i = 0;
    int j = 0;
    //拿到模式串pattern的next数组
    GetNext(pattern, next);
    while (i < s->length && j < pattern->length) {
        //若j为-1.表示pattern模式串需要跟主串下一位置重新开始匹配
        //相等则继续向前匹配
        if (j == -1 || s->data[i] == pattern->data[j]) {
            i++;
            j++;
        } else {
            //不相等时根据next数组回溯
            j = next[j];
        }
    }
    if (j >= pattern->length) {
        return (i - pattern->length);//若字串在主串中，返回字串在主串中的第一个位置。
    } else {
        return (-1);//若字串不存在，则返回—1；
    }
}

void init(str **s) {
    (*s) = malloc(sizeof(str));
    (*s)->data = calloc(MAXSIZE, sizeof(char));
}

int main() {
    str *target, *pattern;
    init(&target);
    init(&pattern);
    //创建target目标字符串
    printf("Target:");
    gets(target->data);
    target->length = strlen(target->data);
    //创建pattern模式串
    printf("pattern:");
    gets(pattern->data);
    pattern->length = strlen(pattern->data);
    char *ans = calloc(MAXSIZE, sizeof(char));
    int len = strlen(pattern->data);
    //i表示步长,j表示遍历坐标
    //构建pattern子串
    for (int i = 2; i <= len; i++) {
        for (int j = 0; j <= len - i; j++) {
            str *cur;
            init(&cur);
            strncpy(cur->data, pattern->data + j, i);
            cur->length = i;
            if (KMPIndex(target, cur) != -1) {
                strcpy(ans, cur->data);
            }
            free(cur->data);
            free(cur);
        }
    }
    if (strlen(ans) != 0) {
        printf("Longest :%s", ans);
    } else {
        printf("Not found");
    }
}


