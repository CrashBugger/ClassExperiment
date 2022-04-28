#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MaxSize 100
typedef struct node {
    char data;
    struct node *lchild;
    struct node *rchild;
} BTNode;


void CreatBTree(BTNode **b, char *str) {
    BTNode *St[MaxSize], *p;
    int top = -1;
    int k;
    int j = 0;
    char ch;
    (*b) = NULL;
    ch = str[j];
    while (ch != 0) {
        switch (ch) {
            case '(':
                top++;
                St[top] = p;
                k = 1;
                break;
            case ')':
                top--;
                break;
            case ',':
                k = 2;
                break;
            default:
                p = malloc(sizeof(BTNode));
                p->data = ch;
                p->lchild = p->rchild = NULL;
                if ((*b) == NULL) {
                    (*b) = p;
                } else {
                    switch (k) {
                        case 1:
                            St[top]->lchild = p;
                            break;
                        case 2:
                            St[top]->rchild = p;
                            break;
                    }
                }
        }
        j++;
        ch = str[j];
    }
}

void DispBTree(BTNode *b) {
    if (b != NULL) {
        printf("%c", b->data);
        if (b->lchild != NULL || b->rchild != NULL) {
            printf("(");
            DispBTree(b->lchild);
            if (b->rchild != NULL) {
                printf(",");
            }
            DispBTree(b->rchild);
            printf(")");
        }
    }
}

void DispChild(BTNode *b, char e) {
    if (b == NULL) {
        return;
    }
    if (b->data == e) {
        printf("\nlchild:%c ", b->lchild->data);
        printf("rchild:%c ", b->rchild->data);
        return;
    } else {
        DispChild(b->lchild, e);
        DispChild(b->rchild, e);
    }
}

int height(BTNode *b) {
    if (b == NULL) {
        return 0;
    }
    int lHeight = height(b->lchild);
    int rHeight = height(b->rchild);
    return lHeight > rHeight ? lHeight + 1 : rHeight + 1;
}

void DestroyTree(BTNode *b) {
    if (b == NULL) {
        return;
    }
    DestroyTree(b->lchild);
    DestroyTree(b->rchild);
    free(b);
}

int main() {
    char *str = "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))";
    BTNode *b = malloc(sizeof(BTNode));
    CreatBTree(&b, str);
    DispBTree(b);
    DispChild(b, 'H');
    printf("\nHeight is %d", height(b));
    DestroyTree(b);
    int a;
}


