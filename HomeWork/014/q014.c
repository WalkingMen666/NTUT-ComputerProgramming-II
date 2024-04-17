#include <stdio.h>
#include <string.h>

void plus(char num1[200], char num2[200], char ans[201]){
    int carry = 0, temp = 0, index1 = 0, index2 = 0;
    char tempAns[2] = {'0', '\0'};
    for(int i = strlen(num1)-1, j = strlen(num2)-1; i>-1 || j>-1; i--, j--){
        if(i < 0) index1 = 0;
        else index1 = num1[i] - '0';
        if(j < 0) index2 = 0;
        else index2 = num2[j] - '0';

        temp = index1 + index2 + carry;
        if(temp > 9){
            carry = 1;
            temp -= 10;
        }
        else carry = 0;

        tempAns[0] = (char)(temp+'0');

        strcat(ans, tempAns);
    }
    if(carry == 1) strcat(ans, "1");
}

void my_strrev(char input[1000]){
    char temp[1000] = {0}, tempAns[2] = {'0', '\0'};
    for(int i = strlen(input); i > -1; i--){
        tempAns[0] = input[i];
        strcat(temp, tempAns);
    }
    strcpy(input, temp);
}

void minus(char temp1[200], char temp2[200], char ans[201]){
    int borrow = 0, temp = 0, index1 = 0, index2 = 0;
    char tempAns[2] = {'0', '\0'}, negative = 0, num1[200] = {0}, num2[200] = {0}, ans2[201] = {0};

    if(strlen(temp2) > strlen(temp1)) negative = 1;
    else if(strlen(temp1) == strlen(temp2)){
        for(int i = 0, j = 0; i < strlen(temp1) && j < strlen(temp2); i++, j++){
            if(temp1[i] > temp2[j]) break;
            else if(temp1[i] < temp2[j]){
                negative = 1;
                break;
            }
        }
    }
    if(negative == 1){
        strcpy(num1, temp2);
        strcpy(num2, temp1);
    }
    else{
        strcpy(num1, temp1);
        strcpy(num2, temp2);
    }

    for(int i = strlen(num1)-1, j = strlen(num2)-1; i > -1 || j > -1; i--, j--){
        index1 = num1[i] - '0';
        if(j < 0) index2 = 0;
        else index2 = num2[j] - '0';

        if(borrow == 1){
            index1--;
            borrow = 0;
        }
        if(index2 > index1){
            borrow = 1;
            temp = (index1 + 10) - index2;
        }
        else temp = index1 - index2;

        tempAns[0] = (char)(temp + '0');

        strcat(ans2, tempAns);
    }
    for(int i = strlen(ans2)-1; i > -1; i--){
        if(ans2[i] != '0'){
            strncpy(ans, ans2, i+1);
            break;
        }
    }
    if(negative == 1) strcat(ans, "-");
}

void multiple(char num1[200], char num2[200], char ans[201]){
    int carry = 0, index1 = 0, index2 = 0, temp = 0, index = 0;
    char buffer[2] = {'0', '\0'};
    for(int i = strlen(num2)-1; i > -1; i--){
        char temp2[201] = {0}, ansBuffer[201] = {0}, tempAns[201] = {0};
        index2 = num2[i] - '0';
        for(int j = 0; j < index; j++) strcat(tempAns, "0");
        for(int j = strlen(num1)-1; j > -1; j--){
            index1 = num1[j] - '0';
            temp = index1 * index2 + carry;
            if(temp > 9){
                carry = temp/10;
                temp %= 10;
            }
            else carry = 0;
            buffer[0] = (char)(temp + '0');
            strcat(tempAns, buffer);
        }
        if(carry > 0){
            buffer[0] = (char)(carry + '0');
            strcat(tempAns, buffer);
        }
        index++;
        strcpy(temp2, ans);
        my_strrev(tempAns);
        plus(tempAns, temp2, ansBuffer);
        my_strrev(ansBuffer);
        strcpy(ans, ansBuffer);
        carry = 0;
    }
}

int main(){
    char num1[200] = {0}, num2[200] = {0}, temp1[200] = {0}, temp2[200] = {0}, ans1[201] = {0}, ans2[201] = {0}, ans3[201] = {0};
    int negative1 = 0, negative2 = 0;
    scanf("%s %s", temp1, temp2);
    
    if(temp1[0] == '-'){
        strcpy(num1, &temp1[1]);
        negative1 = 1;
    }
    else strcpy(num1, temp1);
    if(temp2[0] == '-'){
        strcpy(num2, &temp2[1]);
        negative2 = 1;
    }
    else strcpy(num2, temp2);

    if(negative1 == 0 && negative2 == 0){
        plus(num1, num2, ans1);
        minus(num1, num2, ans2);
        multiple(num1, num2, ans3);
    }
    else if(negative1 == 0 && negative2 == 1){
        minus(num1, num2, ans1);
        plus(num1, num2, ans2);
        multiple(num1, num2, ans3);
        my_strrev(ans3);
        strcat(ans3, "-");
        my_strrev(ans3);
    }
    else if(negative1 == 1 && negative2 == 0){
        minus(num2, num1, ans1);
        plus(num1, num2, ans2);
        strcat(ans2, "-");
        multiple(num1, num2, ans3);
        my_strrev(ans3);
        strcat(ans3, "-");
        my_strrev(ans3);
    }
    else{
        plus(num1, num2, ans1);
        strcat(ans1, "-");
        minus(num2, num1, ans2);
        multiple(num1, num2, ans3);
    }
    my_strrev(ans1);
    my_strrev(ans2);

    if(strpbrk(ans1, "123456789") == NULL) printf("0\n");
    else printf("%s\n", ans1);
    if(strpbrk(ans2, "123456789") == NULL) printf("0\n");
    else printf("%s\n", ans2);
    if(strpbrk(ans3, "123456789") == NULL) printf("0\n");
    else printf("%s\n", ans3);

    return 0;
}