#include <stdio.h>
#include <string.h>
#include <math.h>

void string2int(char fraction[50], int *index, int *bounds, int *num){
    while(*index > -1 && fraction[*index] >= '0' && fraction[*index] <= '9'){
        *num += pow(10, *bounds)*(fraction[*index] - '0');
        (*bounds)++;
        (*index)--;
    }
}
void getNumeratorAndDenominator(char fraction[50], int *numerator, int *denominator){
    int index = strlen(fraction)-1, bounds = 0;
    if(fraction[strlen(fraction)-1] == ')'){
        int temp = 0;
        index--;
        string2int(fraction, &index, &bounds, denominator);
        index--;
        bounds = 0;
        string2int(fraction, &index, &bounds, numerator);
        index--;
        bounds = 0;
        string2int(fraction, &index, &bounds, &temp);
        *numerator += temp*(*denominator);
    }
    else{
        string2int(fraction, &index, &bounds, denominator);
        index--;
        bounds = 0;
        string2int(fraction, &index, &bounds, numerator);
    }
    if(fraction[0] == '-'){
        *numerator *= -1;
    }
}
void symbolRecognize(int *numerator_ans, int *denominator_ans, int numerator1, int numerator2, int denominator1, int denominator2, char symbol){
    if(symbol == '*'){
        *numerator_ans = numerator1 * numerator2;
        *denominator_ans = denominator1 * denominator2;
    }
    else if(symbol == '/'){
        *numerator_ans = numerator1 * denominator2;
        *denominator_ans = denominator1 * numerator2;
    }
    else if(symbol == '+'){
        *numerator_ans = (numerator1*denominator2)+(numerator2*denominator1);
        *denominator_ans = denominator1 * denominator2;
    }
    else{
        *numerator_ans = (numerator1*denominator2)-(numerator2*denominator1);
        *denominator_ans = denominator1 * denominator2;
    }
}
int gcd(int a, int b){
    int ans = 1;
    for(int i = 1; i <= a && i <= b; i++){
        if(a%i == 0 && b%i == 0) ans = i;
    }
    return ans;
}
int main(){
    while(1){
        char fraction1[50] = "", fraction2[50] = "", symbol[1], goOn[1];
        int numerator1 = 0, denominator1 = 0, numerator2 = 0, denominator2 = 0;
        scanf("%s %c %s %c", fraction1, symbol, fraction2, goOn);
        getNumeratorAndDenominator(fraction1, &numerator1, &denominator1);
        getNumeratorAndDenominator(fraction2, &numerator2, &denominator2);
        if(denominator1 == 0 || denominator2 == 0) printf("error\n");
        else{
            int numerator_ans = 0, denominator_ans = 0, leader = 0, GCD = 0, negative_ans = 0;
            symbolRecognize(&numerator_ans, &denominator_ans, numerator1, numerator2, denominator1, denominator2, symbol[0]);
            if(denominator_ans == 0) printf("error\n");
            else{
                if(numerator_ans < 0){
                    numerator_ans *= -1;
                    negative_ans = 1;
                }
                leader = numerator_ans / denominator_ans;
                numerator_ans %= denominator_ans;
                GCD = gcd(numerator_ans, denominator_ans);
                numerator_ans /= GCD;
                denominator_ans /= GCD;
                if(negative_ans == 1) printf("-");
                if(numerator_ans == 0 && leader > 0) printf("%d\n", leader);
                else if(numerator_ans == 0) printf("0\n");
                else if(leader > 0){
                    printf("%d(%d/%d)\n", leader, numerator_ans, denominator_ans);
                }
                else{
                    printf("%d/%d\n", numerator_ans, denominator_ans);
                }
            }
        }
        if(goOn[0] == 'n') break;
    }
    return 0;
}