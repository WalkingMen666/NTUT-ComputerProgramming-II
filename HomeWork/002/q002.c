#include <stdio.h>
#include <math.h>

int main(){
    float a = 0, b = 0, c = 0, realRoot = 0, virtualRoot = 0;

    scanf("%f %f %f", &a, &b, &c);

    realRoot = -b/(2*a);
    virtualRoot = b*b-4*a*c;

    if(virtualRoot < 0){
        virtualRoot = sqrt(fabs(virtualRoot))/(2*a);
        printf("%.1f+%.1fi\n", realRoot, virtualRoot);
        printf("%.1f-%.1fi\n", realRoot, virtualRoot);
    }
    else{
        if(realRoot == -0.0) realRoot = 0.0;
        printf("%.1f\n", realRoot+(sqrt(virtualRoot)/(2*a)));
        printf("%.1f\n", realRoot-(sqrt(virtualRoot)/(2*a)));
    }

    return 0;
}