#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct BTNode {
    char data;
    struct BTNode *lchild;
    struct BTNode *rchild;
} BTNode;

BTNode *creatNode(char e) {
    BTNode *cur = malloc(sizeof(BTNode));
    cur->lchild = cur->rchild = NULL;
    cur->data = e;
    return cur;
}

BTNode *creatTree(char *str) {
    int i = 0;
    char ch = str[i];
    BTNode **valueSt = malloc(sizeof(BTNode) * 100);
    BTNode **symbolSt = malloc(sizeof(BTNode) * 100);
    int valueIndex = 0;
    int symbolIndex = 0;
    while (ch != 0) {
        switch (ch) {
            case '+':
            case '-': {
                if (symbolIndex > 0) {
                    BTNode *root = symbolSt[--symbolIndex];
                    BTNode *right = valueSt[--valueIndex];
                    BTNode *left = valueSt[--valueIndex];
                    root->lchild = left;
                    root->rchild = right;
                    valueSt[valueIndex++] = root;
                }
                BTNode *symbol = creatNode(ch);
                symbolSt[symbolIndex++] = symbol;
                break;
            }
            case '*' :
            case '/' : {
                BTNode *cur = creatNode(ch);
                i++;
                BTNode *nextVal = creatNode(str[i]);
                cur->lchild = valueSt[valueIndex - 1];
                valueIndex--;
                cur->rchild = nextVal;
                valueSt[valueIndex++] = cur;
                break;
            }
            default: {
                BTNode *val = creatNode(ch);
                valueSt[valueIndex++] = val;
                break;
            }
        }
        i++;
        ch = str[i];
    }
    if (symbolIndex > 0) {
        BTNode *root = symbolSt[--symbolIndex];
        BTNode *right = valueSt[--valueIndex];
        BTNode *left = valueSt[--valueIndex];
        root->lchild = left;
        root->rchild = right;
        valueSt[valueIndex++] = root;
    }
    return valueSt[0];
}

float calculate(BTNode *b) {
    if (b == NULL) {
        return 0;
    }
    int ch = b->data;
    if (ch <= '0' + 9 && ch >= '0') {
        return (float) ch - '0';
    }
    float l = calculate(b->lchild);
    float r = calculate(b->rchild);
    switch (ch) {
        case '+' :
            return l + r;
        case '-' :
            return l - r;
        case '*' :
            return l * r;
        case '/' :
            return l / r;
    }
}

int main() {
    char *str = "1+2*3-4/5";
    BTNode *equation = creatTree(str);
    float res = calculate(equation);
    printf("%s = %f", str, res);
}
