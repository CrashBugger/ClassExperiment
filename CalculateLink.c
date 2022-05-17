#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define  expMax 20
typedef struct Node {
    int coe;//系数
    int exp;//指数
    struct Node *next;//后继
} Node;


//插入算数表达式，coe系数，exp指数
void insert(Node *head, int coe, int exp) {
    Node *cur = head->next;
    while (cur) {
        if (cur->exp == exp) {
            cur->coe = coe;
            return;
        }
        cur = cur->next;
    }
}

//根据最高次项创建链表
void initial(Node *head) {
    int exp = expMax;
    while (exp >= 0) {
        Node *cur = malloc(sizeof(Node));
        cur->next = head->next;
        cur->exp = exp;
        cur->coe = 0;
        head->next = cur;
        exp--;
    }
}

//输出表达式
void printExpr(Node *head) {
    Node *cur = head->next;
    while (cur) {
        if (cur->coe != 0) {
            if (cur->exp > 1) {
                printf("%+dx^%d ", cur->coe, cur->exp);
            } else if (cur->exp == 1) {
                printf("%+dx ", cur->coe);
            } else {
                printf("%+d", cur->coe);
            }
        }
        cur = cur->next;
    }
}

//查找另一个表达式指定次数的系数
int find(Node *head, int exp) {
    Node *cur = head->next;
    while (cur) {
        if (cur->exp == exp) {
            return cur->coe;
        }
        cur = cur->next;
    }
}

void calcu(Node *head1, Node *head2) {
    Node *cur = head1->next;
    while (cur) {
        int add = find(head2, cur->exp);
        cur->coe += add;
        cur = cur->next;
    }
}

void parseWord(Node *expr, char *str, int i, int j, bool isNegative) {
    int coe = 0;
    if (j == i && str[i] != 'x') {
        coe = str[i] - '0';
        if (isNegative) {
            coe = 0 - coe;
        }
        insert(expr, coe, 0);
    } else if (j - i <= 1) {
        if (j == i) {
            if (isNegative)
                insert(expr, -1, 1);
            else
                insert(expr, 1, 1);
        } else {
            coe = str[i] - '0';
            if (isNegative) {
                insert(expr, 0 - coe, 1);
            } else {
                insert(expr, coe, 1);
            }
        }
    } else {
        if (str[i] == 'x') {
            coe = 1;
        } else {
            coe = str[i] - '0';
        }
        int exp = str[j] - '0';
        if (isNegative) {
            insert(expr, 0 - coe, exp);
        } else {
            insert(expr, coe, exp);
        }

    }
}

void parseStr(Node *pNode, char *str) {
    bool isNe;
    int i = 0;
    while (str[i] != 0) {
        isNe = false;
        if (str[i] == '-') {
            isNe = true;
            i++;
        } else if (str[i] == '+') {
            i++;
        }
        int pre = i;
        while (str[i] != '+' && str[i] != '-' && str[i] != 0) {
            i++;
        }
        parseWord(pNode, str, pre, i - 1, isNe);
    }
}

int main() {
    //创建两个头结点,存储两个表达式
    Node *expre1 = malloc(sizeof(Node));
    Node *expre2 = malloc(sizeof(Node));
    expre1->next = NULL;
    expre2->next = NULL;
    initial(expre1);
    initial(expre2);
    char *str1 = calloc(40, sizeof(char));
    char *str2 = calloc(40, sizeof(char));
    printf("Expr1: ");
    gets(str1);
//    str1 = "3x^4+5x^2+2";
    printf("Expr2: ");
    gets(str2);
//    str2 = "7x^8+5x^6+9x^4+3";
    parseStr(expre1, str1);
    parseStr(expre2, str2);
    calcu(expre1, expre2);
    printExpr(expre1);
}


