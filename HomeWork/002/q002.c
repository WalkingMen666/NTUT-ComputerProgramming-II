#include <stdio.h>
#include <math.h>

int main(){
    float a = 0, b = 0, c = 0, realRoot = 0, imaginary = 0;

    scanf("%f %f %f", &a, &b, &c);

    realRoot = -b/(2*a);
    imaginary = b*b-4*a*c;

    if(imaginary < 0){
        imaginary = sqrt(fabs(imaginary))/(2*a);
        printf("%.1f+%.1fi\n", realRoot, imaginary);
        printf("%.1f-%.1fi\n", realRoot, imaginary);
    }
    else{
        if(realRoot == -0.0) realRoot = 0.0;
        printf("%.1f\n", realRoot+(sqrt(imaginary)/(2*a)));
        printf("%.1f\n", realRoot-(sqrt(imaginary)/(2*a)));
    }

    return 0;
}