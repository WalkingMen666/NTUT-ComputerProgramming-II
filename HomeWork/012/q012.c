#include <stdio.h>

void calScore(int outTarget, int strike[], int base[], char strikeRecord[9][5]){
    int outCount = 0, pad[3] = {-1, -1, -1}, score = 0, endGame = 0, out = 0, sortScore[3] = {-1, -1, -1}, sort[3];

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 9; j++){
            int temp = strikeRecord[j][i] - '0';
            if(strikeRecord[j][i] == 'H') temp = 4;

            if(temp > 0 && temp <= 4){
                strike[j]++;
                for(int x = 0; x < 3; x++)
                    if(pad[x] != -1)
                        base[pad[x]]++;
                base[j]++;
                if(pad[0] != -1) score++;

                pad[0] = pad[1];
                pad[1] = pad[2];
                pad[2] = j;

                for(int x = 0; x < temp-1; x++){
                    for(int y = 0; y < 3; y++)
                        if(pad[y] != -1)
                            base[pad[y]]++;
                    if(pad[0] != -1) score++;
                    pad[0] = pad[1];
                    pad[1] = pad[2];
                    pad[2] = -1;
                }
            }
            else if(strikeRecord[j][i] == 'x'){
                endGame = 1;
                break;
            }
            else{
                outCount++;
                out++;
            }
            if(outCount == 3){
                for(int x = 0; x < 3; x++)
                    pad[x] = -1;
                outCount = 0;
            }
            if(out == outTarget) break;
        }
        if(endGame != 0 || out == outTarget) break;
    }
    
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 3; j++){
            if(base[i] > sortScore[j]){
                for(int x = 2; x > j; x--){
                    sortScore[x] = sortScore[x-1];
                    sort[x] = sort[x-1];
                }
                sortScore[j] = base[i];
                sort[j] = i;
                break;
            }
        }
    }
    printf("%d\n", score);
    for(int i = 0; i < 3; i++){
        printf("%d %d %d\n", sort[i]+1, strike[sort[i]], sortScore[i]);
    }
}

int main(){
    char strikeRecord[9][5];
    int outTarget = 0, strikes[9] = {0}, base[9] = {0};
    
    for(int i = 0; i < 9; i++) for(int j = 0; j < 5; j++) strikeRecord[i][j] = 'x';

    for(int i = 0; i < 9; i++){
        int rounds = 0;
        scanf("%d", &rounds);
        for(int j = 0; j < rounds; j++){
            char score[2];
            scanf("%s", score);
            strikeRecord[i][j] = score[0];
        }
    }
    scanf("%d", &outTarget);
    calScore(outTarget, strikes, base, strikeRecord);

    return 0;
}