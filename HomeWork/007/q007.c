#include <stdio.h>

int teamConvert(char team){
    if(team == 'A') return 0;
    if(team == 'B') return 1;
    if(team == 'C') return 2;
    return -1;
}

int main(){
    int sessions = 0, index = 0, tempWin = 0;
    int score[3] = {0, 0, 0}, win[3] = {0, 0, 0};
    scanf("%d", &sessions);
    getchar();

    for(int i = 0; i < sessions; i++){
        int team1 = -1, team2 = -1, score1 = 0, score2 = 0;
        char t1, t2;
        scanf("%c %c", &t1, &t2);
        getchar();
        team1 = teamConvert(t1);
        team2 = teamConvert(t2);
        for(int j = 0; j < 4; j++){
            int tempScore = 0;
            scanf("%d", &tempScore);
            getchar();
            score1+=tempScore;
            scanf("%d", &tempScore);
            getchar();
            score2+=tempScore;
        }
        if(score1 > score2) win[team1]++;
        else win[team2]++;
        score[team1] += score1;
        score[team2] += score2;
    }
    for(int i = 0; i < 3; i++){
        if(win[i] > tempWin){
            index = i;
            tempWin = win[i];
        }
    }
    if(index == 0) printf("A\n");
    if(index == 1) printf("B\n");
    if(index == 2) printf("C\n");
    printf("%d", score[index]);

    return 0;
}