#include <stdlib.h>
#include <stdio.h>


int partition(int *arr, int s, int t) {
    int i = s, j = t;
    int base = arr[i];
    while (i < j) {
        while (j > i && arr[j] > base) {
            j--;
        }
        arr[i] = arr[j];
        while (i < j && arr[i] < base) {
            i++;
        }
        arr[j] = arr[i];
    }
    arr[i] = base;
    return i;
}

void printArr(int *arr, int i, int j) {
    for (int k = 0; k < i; ++k) {
        printf(" ");
    }
    for (i; i <= j; ++i) {
        printf("%d ", arr[i]);
    }
}

int count;

void quickSort(int *arr, int s, int t) {
    int i;
    if (s < t) {
        i = partition(arr, s, t);
        printf("\n第%d次划分 ", count++);
        printArr(arr, s, t);
        quickSort(arr, s, i - 1);
        quickSort(arr, i + 1, t);
    }
}


int main() {
    count = 1;
    int arr[] = {6, 8, 7, 9, 0, 1, 2, 3, 4, 5};
    printf("排序前");
    printArr(arr, 0, 9);
    quickSort(arr, 0, 9);
    printf("\n排序后");
    printArr(arr, 0, 9);
}
