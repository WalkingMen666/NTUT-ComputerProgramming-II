#include <stdio.h>

int main(){
    int classNum[3] = {}, correct = 0;
    int classTime[3][3] = {{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}};
    for(int i = 0; i < sizeof(classNum)/sizeof(classNum[0]); i++){
        int hour = 0;
        scanf("%d%d", &classNum[i], &hour);

        for(int j = 0; j < hour; j++){
            scanf("%d", &classTime[i][j]);
        }
    }
    for(int a = 0; a < sizeof(classNum)/sizeof(classNum[0]); a++){
        for(int b = a+1; b < sizeof(classNum)/sizeof(classNum[0]); b++){
            for(int c = 0; c < sizeof(classTime[a])/sizeof(classTime[a][0]); c++){
                if(classTime[a][c] < 0) break;
                for(int d = 0; d < sizeof(classTime[b])/sizeof(classTime[b][0]); d++){
                    if(classTime[b][d] < 0) break;
                    if(classTime[a][c] == classTime[b][d]){
                        printf("%d,%d,%d\n", classNum[a], classNum[b], classTime[a][c]);
                        correct = 1;
                    }
                }
            }
        }
    }
    if(correct == 0) printf("correct");
    return 0;
}