#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b){
    int ans = 1;
    for(int i = 1; i <= a && i <= b; i++){
        if(a%i == 0 && b%i == 0) ans = i;
    }
    return ans;
}

int main(){
    int rounds = 0;
    scanf("%d", &rounds);

    for(int i = 0; i < rounds; i++){        
        int x1 = 0, x2 = 0, y1 = 0, y2 = 0, de_m = 0, de_b = 0, nu_m = 0, nu_b = 0, GCD = 0;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

        nu_m = y1-y2;
        de_m = x1-x2;
        nu_b = x2*y1-x1*y2;
        de_b = x2-x1;
        
        GCD = gcd(abs(nu_m), abs(de_m));
        nu_m /= GCD;
        de_m /= GCD;
        GCD = gcd(abs(nu_b), abs(de_b));
        nu_b /= GCD;
        de_b /= GCD;

        printf("y = ");
        if(nu_m*de_m < 0) printf("-");
        if(nu_m != 0){
            if(nu_m == de_m || nu_m == -1*de_m) printf("x");
            else if(abs(de_m) == 1) printf("%dx", abs(nu_m));
            else printf("%d/%dx", abs(nu_m), abs(de_m));
            if(nu_b != 0){
                if(nu_b*de_b < 0) printf(" -");
                else printf(" +");
                if(abs(de_b) == 1) printf(" %d\n", abs(nu_b));
                else printf(" %d/%d\n", abs(nu_b), abs(de_b));
            }
            else printf("\n");
        }
        if(nu_m == 0){
            if(nu_b == 0) printf("0\n");
            else{
                if(nu_b/de_b < 0) printf("-");
                if(abs(de_b) == 1) printf("%d\n", abs(nu_b));
                else printf("%d/%d\n", abs(nu_b), abs(de_b));
            }
        }
    }
    return 0;
}