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
    int di;//方向参数，共4个方向
} Box;

//定义一个迷宫栈
typedef struct {
    Box Data[MAXSIZE];
    int top;
} Stack;

//输出迷宫
void printMaze(int mg[M + 2][N + 2], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; ++j) {
            printf("%2d ", mg[i][j]);
        }
        printf("\n");
    }
}
//栈的基本操作
bool Push(Stack *S, Box e) {
    if (S->top == MAXSIZE - 1)
        return false;
    S->top++;
    S->Data[S->top].i = e.i;
    S->Data[S->top].j = e.j;
    S->Data[S->top].di = e.di;
    return true;
}

bool Pop(Stack *S, Box *e) {
    if (S->top == -1)
        return false;
    (*e) = S->Data[S->top];
    S->top--;
    return true;
}

bool Empty(Stack *S) {
    return (S->top == -1);

}

bool GetTop(Stack *S, Box *e) {
    if (S->top == -1)
        return false;
    (*e) = S->Data[S->top];
    return true;
}
//入口的xy坐标，出口的xy坐标
bool solve(int mg[M + 2][N + 2], int xi, int yi, int xe, int ye) {
    Box e, path[MAXSIZE];
    int i, j, di, i1, j1, k;
    Stack *S = malloc(sizeof(Stack));
    S->top = -1;
    bool find;
    e.i = xi;
    e.j = yi;
    e.di = -1;
    Push(S, e);
    //入口已访问过
    mg[xi][yi] = -1;
    while (!Empty(S)) {
        GetTop(S, &e);
        i = e.i;
        j = e.j;
        di = e.di;
        //找到了路径
        if (i == xe && j == ye) {
            printf("One path is found!\n");
            k = 0;
            while (!Empty(S)) {
                Pop(S, &e);
                //当前栈就是一条路径
                path[k++] = e;
            }
            while (k >= 1) {
                k--;
                printf("(%d , %d) ", path[k].i, path[k].j);
                if ((k + 2) % 5 == 0) {
                    printf("\n");
                }
            }
            free(S);
            return true;
        }
        find = false;
        while (di < 4 && !find) {
            //选择方向
            di++;
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
            //找到了下一个方块
            if (mg[i1][j1] == 0)
                find = true;
        }
        //找到一条路，方块入栈
        if (find) {
            S->Data[S->top].di = di;
            //置为-1表示已经找过了
            mg[i][j] = -1;
            e.i = i1;
            e.j = j1;
            e.di = -1;
            Push(S, e);
        } else {
            Pop(S, &e);
            mg[i][j] = 0;
        }
    }
    free(S);
    return false;
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
    solve(mg, 1, 1, 8, 8);
}

