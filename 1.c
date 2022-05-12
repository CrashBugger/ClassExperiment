#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define  MAXV 6
#define  MAXA 100
#define  INF 25535
typedef struct ANode {
    int adjvex;
    struct ANode *nextarc;
    int weight;
} ArcNode;
typedef struct Vnode {
    int info;
    ArcNode *firstarc;
} VNode;
typedef struct {
    VNode adjlist[MAXV];
    int n, e;
} AdjGraph;

void createAdj1(AdjGraph **G, int A[MAXV][MAXV], int n, int e) {
    int i, j;
    ArcNode *p;
    (*G) = malloc(sizeof(AdjGraph));
    for (i = 0; i < n; ++i) {
        (*G)->adjlist[i].firstarc = NULL;
    }
    for (i = 0; i < n; ++i) {
        for (int j = n - 1; j >= 0; j--) {
            if (A[i][j] != 0 && A[i][j] != INF) {
                p = malloc(sizeof(ArcNode));
                p->adjvex = j;
                p->nextarc = (*G)->adjlist[i].firstarc;
                p->weight = A[i][j];
                (*G)->adjlist[i].firstarc = p;
            }
        }
    }
    (*G)->n = n;
    (*G)->e = e;
}

void DispAdj(AdjGraph *G) {
    int i;
    ArcNode *p;
    for (i = 0; i < G->n; ++i) {
        p = G->adjlist[i].firstarc;
        printf("%3d: ", i);
        while (p != NULL) {
            printf("%3d[%d]->", p->adjvex, p->weight);
            p = p->nextarc;
        }
        printf("/\\");
        printf("\n");
    }
}

void DestroyAdj(AdjGraph **G) {
    int i;
    ArcNode *pre;
    ArcNode *p;
    for (i = 0; i < (*G)->n; ++i) {
        pre = (*G)->adjlist[i].firstarc;
        while (pre != NULL) {
            p = pre;
            pre = pre->nextarc;
            free(p);
        }
    }
    free((*G));
}

void createAdj2() {

}

void DispAdj2(int A[MAXV][MAXV], int n) {
    printf("%3d ", n);
    for (int i = 0; i < n; i++) {
        printf("%3d ", i);
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%3d ", i);
        for (int j = 0; j < n; ++j) {
            if (A[i][j] != INF)
                printf("%3d ", A[i][j]);
            else
                printf("INF ");
        }
        printf("\n");
    }
}

int main() {
    int A[MAXV][MAXV] = {
            {0,   5,   INF, 7,   INF, 3},
            {INF, 0,   4,   INF, INF, INF},
            {8,   INF, 0,   INF, INF, 9},
            {INF, INF, 5,   0,   INF, 6},
            {INF, INF, INF, 5,   0,   INF,},
            {3,   INF, INF, INF, 1,   0}
    };
    DispAdj2(A, 6);
    printf("\n");
    AdjGraph *G = malloc(sizeof(AdjGraph));
    createAdj1(&G, A, 6, 11);
    DispAdj(G);
    DestroyAdj(G);
}
