#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define  M 8
#define  N 8
#define  MAXSIZE 100
//表示迷宫的每一个方格
typedef struct Box {
    int i;//x坐标
    int j;//y坐标
    int pre;//上一个方块在队列中的下标
} Box;


typedef struct {
    Box data[MAXSIZE];
    int front;//队头指针
    int rear;//队尾指针
} SqQueue;

//队列基本操作
void InitQueue(SqQueue **q) {
    (*q) = (SqQueue *) malloc(sizeof(SqQueue));
    (*q)->front = -1;
    (*q)->rear = -1;
}

bool QueueEmpty(SqQueue *q) {
    return (q->front == q->rear);
}

bool enQueue(SqQueue *q, Box e) {
    if (q->rear == MAXSIZE - 1) {
        return false;
    }
    q->rear++;
    q->data[q->rear] = e;
    return true;
}

bool deQueue(SqQueue *q, Box *e) {
    if (q->front == q->rear) {
        return false;
    }
    q->front++;
    (*e) = q->data[q->front];
    return true;
}

void printPath(SqQueue *qu, int front) {
    int k = front, j, ns = 0;  //front值为终点在队列中的下标
    printf("\n");
    do {
        j = k;              //j为该方块在队列中的下标
        k = qu->data[k].pre;//k为前一个方块在队列中的下标
        qu->data[j].pre = -1;
    } while (k != 0);
    k = 0;
    printf("One oath is found:\n");
    while (k < MAXSIZE) {
        if (qu->data[k].pre == -1) {
            ns++;
            printf("(%d,%d)", qu->data[k].i, qu->data[k].j);
            if (ns % 5 == 0) {
                printf("\n");
            }
        }
        k++;
    }
    printf("\n");
}

bool mgpath(int mg[M + 2][N + 2], int xi, int yi, int xe, int ye) {
    Box e;
    int i, j, di, i1, j1;
    SqQueue *qu;
    InitQueue(&qu);
    e.i = xi;
    e.j = yi;
    e.pre = -1;
    enQueue(qu, e);
    mg[xi][yi] = -1;
    while (!QueueEmpty(qu)) {
        //只是将front++取出队中元素,该元素仍在队列（数组）中
        deQueue(qu, &e);
        i = e.i;
        j = e.j;
        //出口找到了
        if (i == xe && j == ye) {
            printPath(qu, qu->front);
            return true;
        }
        //四个方向探路
        for (di = 0; di < 4; di++) {
            switch (di) {
                case 0:
                    i1 = i - 1;
                    j1 = j;
                    break;
                case 1:
                    i1 = i;
                    j1 = j + 1;
                    break;
                case 2:
                    i1 = i + 1;
                    j1 = j;
                    break;
                case 3:
                    i1 = i;
                    j1 = j - 1;
                    break;
            }
            //找到一个未访问过的，入队列
            if (mg[i1][j1] == 0) {
                e.i = i1;
                e.j = j1;
                //前一个方块的队列中的位置需要记录，后来输出路径需要
                e.pre = qu->front;
                enQueue(qu, e);
                mg[i1][j1] = -1;
            }
        }
    }
    return false;
}


//输出迷宫
void printMaze(int mg[M + 2][N + 2], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; ++j) {
            printf("%2d ", mg[i][j]);
        }
        printf("\n");
    }
}

int main() {
    //迷宫定义，1表示围墙，0表示通路
    int mg[M + 2][N + 2] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
            {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 1, 1, 0, 0, 1},
            {1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
            {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
            {1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
            {1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    printMaze(mg, M + 2, N + 2);
    //定义出口为(8,8)
    //入口为(1,1)
    mgpath(mg, 1, 1, 8, 8);
}

