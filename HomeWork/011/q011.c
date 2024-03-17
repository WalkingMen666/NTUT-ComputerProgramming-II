#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int char2int(char a){
    if(isalpha(a)) return ((int)a-55);
    return a-'0';
}

char int2char(int a){
    if(a > 9) return (char)(a+55);
    return (char)(a+48);
}

long long M_2_10(int M, char userInput[50]){
    long long ans = 0;
    int length = strlen(userInput);
    for(int i = length-1; i > -1; i--)
        ans += pow(M, length-i-1)*char2int(userInput[i]);
    return ans;
}

int main(){
    int M = 0, N = 0;
    char userInput[50] = "", ans[50] = "";

    scanf("%d %s %d", &M, userInput, &N);
    
    if(M == N) printf("%s", userInput);
    else{
        long long tempAns = M_2_10(M, userInput);
        if(tempAns == 0) printf("%c", '0');
        else{
            int i = 0;
            while(1){
                int tempInt = tempAns%N;
                ans[i] = int2char(tempInt);
                i++;
                tempAns /= N;
                if(tempAns < N){
                    ans[i] = int2char((int)tempAns);
                    i++;
                    break;
                }
            }
            for(int j = i-1; j > -1; j--){
                printf("%c", ans[j]);
            }
        }
    }
    
    return 0;
}