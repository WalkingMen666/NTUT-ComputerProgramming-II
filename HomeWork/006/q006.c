#include <stdio.h>

void printFunc(int times, char symbol){
    for(int i = 0; i < times; i++)
        printf("%c", symbol);
}

void pattern1(int height){
    char letter[3] = "CAB";
    if(height < 2 || height > 9) printf("error");
    else{
        for(int i = 0; i < height; i++){
            printFunc(height-i-1, '#');
            for(int j = 0; j < i; j++){
                printf("*%c", letter[i%3]);
            }
            printf("*");
            printFunc(height-i-1, '#');
            printf("\n");
        }
    }
}
void pattern2(int height){
    if(height < 2 || height > 9) printf("error");
    else{
        for(int i = 0; i < height; i++){
            for(int j = 1; j < i+2; j++) printf("%d", j);
            printFunc((height-i)*2, '*');
            for(int j = i+1; j > 0; j--) printf("%d", j);
            printf("\n");
        }
    }
}

int main(){
    int type = 0, height = 0;;
    scanf("%d %d", &type, &height);
    if(type == 1) pattern1(height);
    else if(type == 2) pattern2(height);
    else printf("error");

    return 0;
}