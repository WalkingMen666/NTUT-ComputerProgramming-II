#include <stdio.h>

int main(){
    int score = 0, out = 0;
    int pad[3] = {0};
    int player[5] = {0};

    for(int i = 0; i < 5; i++)
        scanf("%d", &player[i]);

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

    printf("%d\n", score);
    for(int i = 0; i < 3; i++)
        printf("%d ", pad[i]);

    return 0;
}