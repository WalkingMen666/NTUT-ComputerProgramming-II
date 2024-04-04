#include <stdio.h>
#include <stdlib.h>

void fillUp(int **sqMatrix, int val, int baseX, int baseY, int stepX, int stepY){
    for(int i = baseY; i < baseY+stepY; i++)
        for(int j = baseX; j < baseX+stepX; j++)
            sqMatrix[i][j] = val;
}

void cal(int N, int **sqMatrix, char expression[], int *index, int baseX, int baseY, int stepX, int stepY){
    for(int y = 0; y < 2; y++){
        int tempBaseY = baseY + stepY*y;
        for(int x = 0; x < 2; x++){
            int tempBaseX = baseX + stepX*x;
            if(expression[*index] == '0'){
                fillUp(sqMatrix, 0, tempBaseX, tempBaseY, stepX, stepY);
                (*index)++;
            }
            else if(expression[*index] == '1'){
                fillUp(sqMatrix, 1, tempBaseX, tempBaseY, stepX, stepY);
                (*index)++;
            }
            else{
                (*index)++;
                cal(N, sqMatrix, expression, index, tempBaseX, tempBaseY, stepX/2, stepY/2);
            }
        }
    }
}

void printBlack(int N, int **sqMatrix){
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if(sqMatrix[i][j] == 1)
                printf("%d,%d\n", i, j);
}

int main(){
    char expression[101] = "";
    int N = 0;
    scanf("%s %d", expression, &N);

    int **sqMatrix = calloc(N, sizeof(int*));
    for(int i = 0; i < N; i++) sqMatrix[i] = calloc(N, sizeof(int));

    if(expression[0] == '1'){
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                sqMatrix[i][j] = 1;
        printBlack(N, sqMatrix);
    }
    else if(expression[0] == '2'){
        int index = 1;
        cal(N, sqMatrix, expression, &index, 0, 0, N/2, N/2);
        printBlack(N, sqMatrix);
    }
    else printf("all white");

    return 0;
}