#include <stdio.h>
#include <stdlib.h>

# define SWAP_INT(a, b) {int temp; temp=a; a=b; b=temp;}
# define SWAP_LLD(a, b) {long long int temp; temp=a; a=b; b=temp;}

void sort_int(int input[], int length){
    for(int i = 0; i < length; i++) 
        for(int j = i+1; j < length; j++)
            if(input[j] > input[i]) 
                SWAP_INT(input[j], input[i]);
}

void sort_LLD(long long int input[], int length){
    for(int i = 0; i < length; i++) 
        for(int j = i+1; j < length; j++)
            if(input[j] < input[i])
                SWAP_LLD(input[j], input[i]);
}

int doRepeat(int tempAns[], int length){
    int *temp = calloc(length, sizeof(int));
    for(int i = 0; i < length; i++) temp[i] = tempAns[i];
    sort_int(temp, length);
    for(int i = 1; i < length; i++)
        if(temp[i] == temp[i-1]){
            free(temp);
            return 1;
        }
    free(temp);
    return 0;
}

long long int array2longlong(int tempAns[], int length){
    long long int ans = 0, multiplier = 1;
    for(int i = length-1; i > -1; i--){
        ans += tempAns[i] * multiplier;
        multiplier *= 10LL;
    }
    return ans;
}

void printAns(long long int input, int length){
    long long int multiplier = 1;
    for(int i = 0; i < length-1; i++) multiplier *= 10;
    for(int i = 0; i < length; i++, multiplier/=10){
        printf("%lld ", (input/multiplier)%10);
    }printf("\n");
}

int main(){
    int m = 0, ansCount = 0, userInput[20] = {0}, index = 0, temp = 0, index2 = 0, multiplier = 1;
    scanf("%d", &m);    

    while(scanf("%d", &temp)){
        if(temp == -1) break;
        userInput[index] = temp;
        index++;
    }

    long long int *ans = calloc((index-1), sizeof(long long int));
    for(int i = 0; i < index-m+1; i++){
        int *tempAns = calloc(m, sizeof(int));
        for(int j = 0; j < m; j++)
            tempAns[j] = userInput[i+j];

        if(doRepeat(tempAns, m) == 0){
            ans[index2] = array2longlong(tempAns, m);
            index2++;
        }
    }
    
    printf("%d\n", index2);
    
    sort_LLD(ans, index2);
    printAns(ans[0], m);
    for(int i = 1; i < index2; i++)
        if(ans[i] != ans[i-1])
            printAns(ans[i], m);

    return 0;
}