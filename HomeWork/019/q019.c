#include <stdio.h>
#define max(a, b) (((a) > (b)) ? (a) : (b))

void forward(int diceNum[], int temp){
    diceNum[0] = diceNum[4];
    diceNum[4] = diceNum[2];
    diceNum[2] = diceNum[5];
    diceNum[5] = temp;
}

void backward(int diceNum[], int temp){
    diceNum[0] = diceNum[5];
    diceNum[5] = diceNum[2];
    diceNum[2] = diceNum[4];
    diceNum[4] = temp;
}

void right(int diceNum[], int temp){
    diceNum[0] = diceNum[3];
    diceNum[3] = diceNum[2];
    diceNum[2] = diceNum[1];
    diceNum[1] = temp;
}

void left(int diceNum[], int temp){
    diceNum[0] = diceNum[1];
    diceNum[1] = diceNum[2];
    diceNum[2] = diceNum[3];
    diceNum[3] = temp;
}

void rollDice(int input, int diceNum[]){
    if(input == 1) forward(diceNum, diceNum[0]);
    else if(input == 2) backward(diceNum, diceNum[0]);
    else if(input == 3) right(diceNum, diceNum[0]);
    else left(diceNum, diceNum[0]);
}

int main(){
    int diceNum[4][6] = {{1, 2, 6, 5, 3, 4},
                         {1, 2, 6, 5, 3, 4},
                         {1, 2, 6, 5, 3, 4},
                         {1, 2, 6, 5, 3, 4}};
    int N = 0, temp = 0;
    scanf("%d", &N);

    for(int i = 0; i < N; i++){
        for(int j = 0; j < 4; j++){
            scanf("%d", &temp);
            rollDice(temp, diceNum[j]);
        }
    }
    
    if(diceNum[0][0] == diceNum[1][0] && diceNum[1][0] == diceNum[2][0] && diceNum[2][0] == diceNum[3][0]) printf("18");
    else if(diceNum[0][0] == diceNum[1][0] && diceNum[1][0] == diceNum[2][0]) printf("0");
    else if(diceNum[0][0] == diceNum[2][0] && diceNum[2][0] == diceNum[3][0]) printf("0");
    else if(diceNum[1][0] == diceNum[2][0] && diceNum[2][0] == diceNum[3][0]) printf("0");
    else if(diceNum[0][0] == diceNum[1][0]){
        if(diceNum[2][0] == diceNum[3][0]) printf("%d", max(diceNum[0][0], diceNum[2][0])*2);
        else printf("%d", diceNum[2][0]+diceNum[3][0]);
    }else if(diceNum[0][0] == diceNum[2][0]){
        if(diceNum[1][0] == diceNum[3][0]) printf("%d", max(diceNum[0][0], diceNum[1][0])*2);
        else printf("%d", diceNum[1][0]+diceNum[3][0]);
    }else if(diceNum[0][0] == diceNum[3][0]){
        if(diceNum[1][0] == diceNum[2][0]) printf("%d", max(diceNum[0][0], diceNum[1][0])*2);
        else printf("%d", diceNum[1][0]+diceNum[2][0]);
    }else if(diceNum[1][0] == diceNum[2][0]){
        if(diceNum[0][0] == diceNum[3][0]) printf("%d", max(diceNum[0][0], diceNum[1][0])*2);
        else printf("%d", diceNum[0][0]+diceNum[3][0]);
    }else if(diceNum[1][0] == diceNum[3][0]){
        if(diceNum[0][0] == diceNum[2][0]) printf("%d", max(diceNum[0][0], diceNum[1][0])*2);
        else printf("%d", diceNum[0][0]+diceNum[2][0]);
    }else if(diceNum[2][0] == diceNum[3][0]){
        if(diceNum[0][0] == diceNum[1][0]) printf("%d", max(diceNum[0][0], diceNum[2][0])*2);
        else printf("%d", diceNum[0][0]+diceNum[1][0]);
    }else printf("0");

    return 0;
}