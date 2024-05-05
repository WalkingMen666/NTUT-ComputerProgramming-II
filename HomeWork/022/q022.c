// 懶得寫了所以抄easn的:)
// 連結：https://github.com/qazwsxdshb/ntut_cs1_2/blob/main/hw022.c
#include <stdio.h>
#include <string.h>

void sol(char input[51], int k){
    // count1為當前最大長度的指標
    // count2為更改大小寫判斷的flag
    int array[51] = {0}, ans[20] = {0};
    int status, count1, count2, max = 0;

    for(int i = 0; i < strlen(input); i++){
        if('a' <= input[i] && input[i] <= 'z') array[i] = 1;
        else if('A' <= input[i] && input[i] <= 'Z') array[i] = 2;
    }

    for(int i = 0; i < strlen(input); i++){
        // 重置判斷的初始值
        status = array[i];
        count1 = 0, count2 = 0;
        for(int u = i; u < strlen(input); u++){
            count1++, count2++;
            if(array[u] == status){
                // k*2 <= count1是避免誤判第一次大小寫輪替前的最大長度
                if(k*2 <= count1 && count1%k == 0 && max < count1) max = count1;
            }
            else break;
            if(count2 == k){
                status = (status == 1 ? 2 : 1);
                count2 = 0;
            }
        }
    }
    printf("%d\n",max);
}

int main(){
    char input[51];
    int N = 0, k = 0;

    // 輸入
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%s %d", input, &k);
        sol(input, k);
    }
    return 0;
}