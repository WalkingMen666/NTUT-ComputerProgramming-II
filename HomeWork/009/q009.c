#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int binary2Decimal(char n[10]){
    int num = 0;
    for(int i = 9; i > -1; i--){
        if(n[i] == '1') num += (1<<(9-i));
    }
    return num;
}

char *decimal2Binary(int n){
    char ans[] = "00000000000000";
    for(int i = 13; i > -1; i--){
        if(n == 0) break;
        ans[i] = '0'+n%2;
        n/=2;
    }
    char *result = malloc(sizeof(ans));
    strcpy(result, ans);
    return result;
}

int recursion(int n){
    if(n < 2){
        return 0;
    }
    else if(n%2 == 0){
        return 1+recursion(n/2);
    }
    else{
        return 1+recursion((1+n)/2);
    }
}

int main(){
    while(1){
        char n[11];
        int ans = 0, count = 0, gap = 0;
        scanf("%s %d", n, &gap);
        count = binary2Decimal(n);
        for(int i = 0; i < count+1; i++){
            ans += recursion(i);
        }
        char *temp = decimal2Binary(ans);
        printf("%14s\n", temp);
        free(temp);
        if(gap == -1) break;
    }
    return 0;
}