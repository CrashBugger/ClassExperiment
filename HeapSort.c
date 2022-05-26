#include <stdlib.h>
#include <stdio.h>


void sift(int *arr, int low, int high) {
    int i = low;
    int j = 2 * i;
    int base = arr[i];
    while (j <= high) {
        if (j < high && arr[j] < arr[j + 1]) {
            j++;
        }
        if (base < arr[j]) {
            arr[i] = arr[j];
            i = j;
            j = 2 * i;
        } else
            break;
    }
    arr[i] = base;
}

void printArr(int *arr, int i, int j) {
    for (int k = 0; k < i; ++k) {
        printf(" ");
    }
    for (i; i <= j; ++i) {
        printf("%d ", arr[i]);
    }
}

int count = 1;

void swap(int *arr, int i, int j) {
    int tem = arr[i];
    arr[i] = arr[j];
    arr[j] = tem;
}

void printNode(int *arr, int i, int j, int root) {
    if (root > j) {
        return;
    }
    printf("%d", arr[root]);
    int child = root * 2;
    if (child <= j) {
        printf("(");
        printNode(arr, i, j, child);
        printf(",");
        printNode(arr, i, j, child + 1);
        printf(")");
    }
}

void HeapSort(int *arr, int n) {
    int i;
    for (i = n / 2; i >= 1; i--) {
        sift(arr, i, n);
    }
    for (i = n; i >= 2; i--) {
        printf("\n��%d������: ", count++);
        printf("����%d��%d,", arr[1], arr[i]);
        printf("������");
        printArr(arr, 1, 10);
        swap(arr, 1, i);
        sift(arr, 1, i - 1);
        printf("ɸѡ�õ���");
        printNode(arr, 1, i - 1, 1);
    }
}


int main() {
    count = 1;
    //��һ��λ��������䣬ʵ�������߼�λ�õ�������λ��
    int arr[] = {-1, 6, 8, 7, 9, 0, 1, 2, 3, 4, 5};
    printf("����ǰ");
    printArr(arr, 1, 10);
    printf("\n��ʼ�� ");
    printNode(arr, 1, 10, 1);
    HeapSort(arr, 10);
    printf("\n�����");
    printArr(arr, 1, 10);
}


