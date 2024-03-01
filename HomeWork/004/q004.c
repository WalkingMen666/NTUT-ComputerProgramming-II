#include <stdio.h>
#include <string.h>

int count(char input[], char symbols){
    int ans = 0;
    for(int i = 0; i < strlen(input); i++)
        if(input[i] == symbols) ans++;
    return ans;
}

int rightFindIndex(char input[], char symbols){
    for(int i = strlen(input)-1; i > -1; i--)
        if(input[i] == symbols) return i;
    return -1;
}

const char *typeJudge(char userInput[]){
    int dotCount = 0, length = strlen(userInput);
    if(strpbrk(userInput, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()_+={}[]|\\:;\"'<,>?/") == NULL && length <= 50){
        if(count(userInput, '-') != 0 && rightFindIndex(userInput, '-') != 0) return "string";
        else if(count(userInput, '-') != 0 && rightFindIndex(userInput, '-') == 0 && userInput[1] == '0') return "string";
        else if(count(userInput, '-') > 1) return "string";
        if(strpbrk(userInput, ".") == NULL && length >= 1){
            if(length != 1 && userInput[0] == '0') return "string";
            return "integer";
        }
        else if(length >= 3){
            if(count(userInput, '.') > 1) return "string";
            else if(count(userInput, '.') > 0 && (rightFindIndex(userInput, '.') == 0 || rightFindIndex(userInput, '.') == length-1)) return "string";
            else if(userInput[0] == '0' && userInput[1] == '0') return "string";
            return "float";
        }
        return "string";
    }
    if(length <= 10 && length >= 1 && strpbrk(userInput, "!@#$%^&*()-+={}[]|\\:;\"'<,>.?/") == NULL){
        if(strpbrk(&userInput[0], "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_") == NULL) return "string";
        return "variable";
    }
    return "string";
}

int main(){
    int sets = 0;
    scanf("%d", &sets);
    char userInput[sets][50];

    for(int i = 0; i < sets; i++)
        scanf("%s", userInput[i]);
    
    for(int i = 0; i < sets; i++)
        printf("%s\n", typeJudge(userInput[i]));

    return 0;
}