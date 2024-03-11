#include <stdio.h>
#include <stdlib.h>

char* grayCode(int n, int k) {
    if(n == 1) {
        char* result = malloc(2 * sizeof(char));
        sprintf(result, "%d", k);
        return result;
    }
    else if(k < (1 << (n-1))) {
        char* result = malloc((n+1) * sizeof(char));
        result[0] = '0';
        char* subResult = grayCode(n-1, k);
        sprintf(result+1, "%s", subResult);
        free(subResult);
        return result;
    }
    else {
        char* result = malloc((n+1) * sizeof(char));
        result[0] = '1';
        char* subResult = grayCode(n-1, (1 << n) - 1 - k);
        sprintf(result+1, "%s", subResult);
        free(subResult);
        return result;
    }
}

int main() {
    int inputList[100][2];
    int inputCount = 0;

    while (1) {
        int n, k;
        scanf("%d", &n);
        if (n == -1) {
            break;
        }
        scanf("%d", &k);
        inputList[inputCount][0] = n;
        inputList[inputCount][1] = k;
        inputCount++;
    }

    for (int i = 0; i < inputCount; i++) {
        char* result = grayCode(inputList[i][0], inputList[i][1]);
        printf("%s\n", result);
        free(result);
    }

    return 0;
}