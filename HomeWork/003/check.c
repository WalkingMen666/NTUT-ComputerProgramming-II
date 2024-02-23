//  ======================================================== 
//  ==========      測試你的程式在那些測資出錯      ==========
//  ======================================================== 

#include <stdio.h>

void scoreCal(int pad, int *score){
    while(pad > 0){
        *score += pad&1;
        pad >>= 1;
    }
}

int mySol(int player[5]){
    int score = 0, out = 0, pad = 0, tempPad = 0;

    for(int i = 0; i < 5; i++){
        player[i] != 0 ? pad = (pad << player[i]) | (1 << (player[i] - 1)) : out++;
        if(out >= 3){
            scoreCal(pad>>3, &score);
            out = 0;
            pad = 0;
        }
    }
    scoreCal(pad>>3, &score);
    
    return score;
}

int yourSol(int player[5]){
    // 把下面的程式碼換成自己的然後回傳分數
    // 打者的打擊情況要用player[5]操作
    int score = 0, out = 0;
    int pad[3] = {0};

    for(int i = 0; i < 5; i++){
        if(player[i] > 0){
            if(pad[2] == 1) score++;
            pad[2] = pad[1];
            pad[1] = pad[0];
            pad[0] = 1;
            for(int j = 0; j < player[i]-1; j++){
                if(pad[2] == 1) score++;
                pad[2] = pad[1];
                pad[1] = pad[0];
                pad[0] = 0;
            }
        }
        else out++;

        if(out == 3){
            for(int j = 0; j < 3; j++) pad[j] = 0;
            out = 0;
        }
    }

    return score;
}

int main(){
    int error = 0;
    for(int a = 0; a < 5; a++){
        for(int b = 0; b < 5; b++){
            for(int c = 0; c < 5; c++){
                for(int d = 0; d < 5; d++){
                    for(int e = 0; e < 5; e++){
                        int player[5] = {a, b, c, d, e};
                        int myAns = mySol(player);
                        int yourAns = yourSol(player);
                        if(myAns != yourAns){
                            for(int i = 0; i < 5; i++) printf("%d", player[i]);
                            printf("\nMySol: %d\nYourSol: %d\n==========\n", myAns, yourAns);
                            error++;
                        }
                    }
                }
            }    
        }
    }
    printf("You got %d errors!", error);
    return 0;
}