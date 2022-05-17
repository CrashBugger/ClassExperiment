#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define Link 0
#define Thread 1
typedef struct BitNode {
    //结点数据
    char data;
    //左右孩子指针
    struct BitNode *lchild;
    struct BitNode *rchild;
    int RTag;//表明是线索还是普通的左右节点
    int LTag;
} BitNode;

//插入值，node为当前节点,pre为父节点
BitNode *insert(BitNode *node, int e) {
    if (node == NULL) {
        //找到了恰当的位置
        BitNode *cur = malloc(sizeof(BitNode));
        cur->data = e;
        cur->lchild = NULL;
        cur->rchild = NULL;
        cur->RTag = Link;
        cur->LTag = Link;
        return cur;
    }
    //递归寻找恰当位置,并更新当前子树根节点的左右节点
    if (node->data < e) {
        node->rchild = insert(node->rchild, e);
    } else {
        node->lchild = insert(node->lchild, e);
    }
    //返回更新后的子树根节点
    return node;
}

//中序输出二叉树
void printNode(BitNode *node) {
    if (node == NULL) {
        return;
    }
    printNode(node->lchild);
    printf("%d ", node->data);
    printNode(node->rchild);
}

BitNode *pre;

//全局变量，始终指向刚刚访问过的结点
// 中序遍历进行中序线索化
void InThreading(BitNode *p) {
    if (p != NULL) {
        InThreading(p->lchild);     //递归左子树线索化
        if (p->lchild == NULL) {            //没有左孩子
            p->LTag = Thread;    //前驱线索
            p->lchild = pre;    //左孩子指针指向前驱
        }
        if (pre != NULL && pre->rchild == NULL) {        //前驱没有右孩子
            pre->RTag = Thread;    //后继线索
            pre->rchild = p;    //前驱右孩子指针指向后继(当前结点p)
        }
        //当前p节点的右节点留给后来判断
        pre = p;    //保持pre指向p的前驱
        InThreading(p->rchild);        //递归右子树线索化
    }
}

/* 中序遍历线索二叉树 */
void InOrderPrint(BitNode *b) {
    BitNode *p = b;
    while (p) {
        //从中序遍历的第一个结点开始遍历
        while (p->LTag == Link) {
            p = p->lchild;
        }
        printf("%d ", p->data);
        while (p->RTag == Thread) {
            //后继标志生效
            //当前结点指向后继结点
            p = p->rchild;
            printf("%d ", p->data);
        }
        //找到右子树下最左结点，循环遍历
        p = p->rchild;
    }
}

int main() {
    BitNode *root = NULL;
    int num;
    printf("Nums:");
    scanf("%d", &num);
    //插入值
    int val;
    for (int i = 0; i < num; i++) {
        printf("Insert Value:");
        scanf("%d", &val);
        root = insert(root, val);
    }
    //开始线索化
    //二叉树需要先创建后才能线索化!
    //pre表示前驱
    pre = root;
    InThreading(root);
    InOrderPrint(root);
}

