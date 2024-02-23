#include <stdio.h>

void scoreCal(int pad, int *score){
    while(pad > 0){
        *score += pad&1;
        pad >>= 1;
    }
}

int main(){
    /* ========================= Bit Manipulation solution ========================= */
    int score = 0, out = 0, pad = 0, tempPad = 0;
    int player[5] = {0};
    
    for(int i = 0; i < 5; i++)
        scanf("%d", &player[i]);

    for(int i = 0; i < 5; i++){
        player[i] != 0 ? pad = (pad << player[i]) | (1 << (player[i] - 1)) : out++;
        if(out >= 3){
            scoreCal(pad>>3, &score);
            out = 0;
            pad = 0;
        }
    }
    scoreCal(pad>>3, &score);
    printf("%d\n%d %d %d", score, pad & 1 ? 1:0, pad & 2 ? 1:0, pad & 4 ? 1:0);
    
    return 0;

    /* ========================= Easier solution ========================= */
    // int score = 0, out = 0;
    // int pad[3] = {0};
    // int player[5] = {0};

    // for(int i = 0; i < 5; i++)
    //     scanf("%d", &player[i]);

    // for(int i = 0; i < 5; i++){
    //     if(player[i] > 0){
    //         if(pad[2] == 1) score++;
    //         pad[2] = pad[1];
    //         pad[1] = pad[0];
    //         pad[0] = 1;
    //         for(int j = 0; j < player[i]-1; j++){
    //             if(pad[2] == 1) score++;
    //             pad[2] = pad[1];
    //             pad[1] = pad[0];
    //             pad[0] = 0;
    //         }
    //     }
    //     else out++;

    //     if(out == 3){
    //         for(int j = 0; j < 3; j++) pad[j] = 0;
    //         out = 0;
    //     }
    // }

    // printf("%d\n", score);
    // for(int i = 0; i < 3; i++)
    //     printf("%d ", pad[i]);

    // return 0;
}