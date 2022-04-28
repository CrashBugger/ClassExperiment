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

int countNode(BTNode *b) {
    if (b == NULL) {
        return 0;
    }
    int lNum = countNode(b->lchild);
    int rNum = countNode(b->rchild);
    return lNum + rNum + 1;
}

int countLeafNode(BTNode *b) {
    if (b == NULL) {
        return 0;
    }
    if (!b->lchild && !b->rchild) {
        return 1;
    } else {
        return countLeafNode(b->lchild) + countLeafNode(b->rchild);
    }

}

int countFloor(BTNode *b, char e, int floor) {
    if (b == NULL) {
        return -1;
    }
    if (b->data == e) {
        return floor;
    }
    int left = countFloor(b->lchild, e, floor + 1);
    int right = countFloor(b->rchild, e, floor + 1);
    return left > 0 ? left : right;
}

int countWidth(BTNode *b) {
    BTNode **queue = malloc(sizeof(BTNode) * MaxSize);
    int head = 0, tail = 0;
    queue[tail++] = b;
    int max = 0;
    while (head != tail) {
        int size = tail - head;
        max = size > max ? size : max;
        for (int i = 0; i < size; i++) {
            BTNode *cur = queue[head++];
            if (cur->lchild != NULL) {
                queue[tail++] = cur->lchild;
            }
            if (cur->rchild != NULL) {
                queue[tail++] = cur->rchild;
            }
        }
    }
    return max;
}

int main() {
    char *str = "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))";
    BTNode *b = malloc(sizeof(BTNode));
    CreatBTree(&b, str);
    DispBTree(b);
    printf("\nNode num is %d", countNode(b));
    printf("\nLeaf node num is %d", countLeafNode(b));
    char ch = 'H';
    printf("\nLeaf node %c is %dth floor", ch, countFloor(b, ch, 1));
    printf("\nWidth is %d", countWidth(b));
}


