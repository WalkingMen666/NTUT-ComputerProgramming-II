#include <stdio.h>
char encode(int a, int b, int c, int d){
    switch(a*1000+b*100+c*10+d) {
        case 101:
            return 'A';
        case 111:
            return 'B';
        case 10:
            return 'C';
        case 1101:
            return 'D';
        case 1000:
            return 'E';
        case 1100:
            return 'F';
    }
}
int main(){
    int a=0, b=0, c=0, d=0;
    scanf("%d %d %d %d",&a, &b, &c, &d);
    printf("%c\n", encode(a,b,c,d));
    return 0;
}