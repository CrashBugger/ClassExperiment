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


void prim(int A[MAXV][MAXV], int n, int v) {
    int lowcost[MAXV];
    int MIN;
    int cloest[MAXV];
    for (int i = 0; i < n; ++i) {
        lowcost[i] = A[v][i];
        cloest[i] = v;
    }
    int k;
    for (int i = 1; i < n; i++) {
        MIN = INF;
        for (int j = 0; j < n; j++) {
            if (lowcost[j] != 0 && lowcost[j] < MIN) {
                MIN = lowcost[j];
                k = j;
            }
        }
        printf("edge(%d,%d)weights:%d\n", cloest[k], k, MIN);
        lowcost[k] = 0;
        for (int j = 0; j < n; j++) {
            if (lowcost[j] != 0 && lowcost[j] > A[k][j]) {
                lowcost[j] = A[k][j];
                cloest[j] = k;
            }
        }
    }
}

int main() {
    int A[MAXV][MAXV] = {
            {0, 5,     8,   7, INF, 3},
            {5, 0,     4, INF, INF, INF},
            {8, 4,     0,   5, INF, 9},
            {7,   INF, 5,   0, 5,   6},
            {INF, INF, INF, 5, 0,   1},
            {3,   INF, 9,   6, 1,   0}
    };
    AdjGraph *G = malloc(sizeof(AdjGraph));
    prim(A, 6, 0);
}
