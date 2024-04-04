# include <stdio.h>
# include <stdlib.h>

int main(){
    int N = 0, W = 0;
    scanf("%d", &N);

    int *array = malloc(N*sizeof(int));
    for(int i = 0; i < N; i++) scanf("%d", &array[i]);

    for(int i = 0; i < N; i++)
        for(int j = i; j < N; j++)
            if(array[i] > array[j]) W++;

    printf("%d", W);
    return 0;
}