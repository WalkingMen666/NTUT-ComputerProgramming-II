#include <stdio.h>
#include <stdlib.h>
#define SWAP(x, y) {int t; t = x; x = y; y = t;}

int getMinIndex(int d[], int left, int right, int *com) {
    int i = 0, minIndex = left;
    for ((i = left+1); i < right; i++) {
        (*com)++;
        if (d[i] < d[minIndex]) minIndex = i;
    }
    return minIndex;
}
void selectSort(int d[], int n, int *com, int *move) {
    int i = 0, index = 0;
    for (i = 0; i < n; i++) {
        index = getMinIndex(d, i, n, com);
        if(i != index) (*move) += 3;
        SWAP(d[i], d[index]);
    }
}

void insertionSort(int a[], int n, int *com, int *move) {
    int target=0, i=0, j=0;
    for (i = 1; i < n; i++) {
        target = a[i];
        (*move)++;
        (*com)++;
        for (j = i; j > 0 ; j--, (*com)++){
            (*com)++;
            if(a[j-1] > target){
                a[j] = a[j-1];
                (*move)++;
            }
            else break;
        }
        a[j] = target;
        (*move)++;
    }
}

int main(){
    int length = 0, selectCom = 0, selectMove = 0, insCom = 0, insMove = 0;
    scanf("%d", &length);

    int *array1 = malloc(length*sizeof(int));
    int *array2 = malloc(length*sizeof(int));

    for(int i = 0; i < length; i++) {
        scanf("%d", &array1[i]);
        array2[i] = array1[i];
    }

    selectSort(array1, length, &selectCom, &selectMove);
    insertionSort(array2, length, &insCom, &insMove);
    printf("%d %d\n", selectCom, selectMove);
    printf("%d %d\n", insCom, insMove);

    return 0;
}