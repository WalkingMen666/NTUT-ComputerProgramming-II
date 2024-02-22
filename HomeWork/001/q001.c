#include <stdio.h>

int main(){
    float weight = 0, height = 0;
    scanf("%f %f", &weight, &height);
    printf("%.1f", weight/(height*height*0.0001));

    return 0;
}