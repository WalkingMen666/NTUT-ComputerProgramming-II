#include <stdio.h>

int main(){
    float weight = 0, height = 0, bmi = 0;
    scanf("%f", &weight);
    scanf("%f", &height);
    bmi = weight/((height/100)*(height/100));
    printf("%.1f", bmi);

    return 0;
}