#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100

bool isBracket(char *str, int len) {
    //定义栈
    char *stack = malloc(sizeof(char) * MAXSIZE);
    int top = 0;
    for (int i = 0; i < len; i++) {
        //左括号入栈
        if (str[i] == '(') {
            stack[top++] = str[i];
        } else if (str[i] == ')') {
            //无左括号，栈为空，无法匹配
            if (top == 0) {
                return false;
            } else {
                //若当前有左括号，则可以匹配
                top--;
            }
        }
    }
    //当前站是否为空，为空则匹配完毕
    if (top == 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    char *str1 = calloc(MAXSIZE, sizeof(char));
    printf("Input:\n");
    gets(str1);
    if (isBracket(str1, strlen(str1))) {
        printf("%s is true.\n", str1);
    } else {
        printf("%s is false.\n", str1);
    }
}

