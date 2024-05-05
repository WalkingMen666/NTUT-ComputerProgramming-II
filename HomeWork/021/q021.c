#include <stdio.h>
#include <string.h>

// 將input內以空格作為分隔的單字加入到ans內，並計數(count)
void split_word(char input[], char ans[10][100], int *count){
    char *token = strtok(input, " ");
    
    while(token != NULL){
        for(int index = 0; index < strlen(token); index++) 
            ans[*count][index] = token[index];
        ans[*count][strlen(token)] = '\0';
        (*count)++;
        token = strtok(NULL, " ");
    }
}

// 檢查S1、S2是否出現相同的字，若否則回傳1
int stage1(char s1[10][100], char s2[10][100], int s1_word_count, int s2_word_count){
    for(int i = 0; i < s1_word_count; i++){
        for(int j = 0; j < s2_word_count; j++){
            if(strcmp(s1[i], s2[j]) == 0) return -1;
        }
    }
    return 1;
}

// 檢查S內的字是否都出現在S1或S2中，若是則回傳1
int stage2(char s[10][100], char s1[10][100], char s2[10][100], int s_word_count, int s1_word_count, int s2_word_count){
    int flag = 0, index = 0;
    for(int i = 0; i < s_word_count; i++, flag = 0){
        for(index = 0; index < s1_word_count; index++){
            if(strcmp(s[i], s1[index]) == 0){
                flag = 1;
                break;
            }
        }
        if(flag != 1){
            for(index = 0; index < s2_word_count; index++){
                if(strcmp(s[i], s2[index]) == 0){
                    flag = 1;
                    break;
                }
            }
            if(flag != 1) return 0;
        }
    }
    return 1;
}

int main(){
    char input[1000], input_word[10][100];;
    int n = 0, ans = 0, input_word_count = 0;

    // 輸入及清空暫存區
    fgets(input, sizeof(input), stdin);
    scanf("%d", &n);
    getchar();

    // 將input最後一個字元\n替換成\0
    input[strlen(input)-1] = '\0';
    char compare_str[n][100];

    // 輸入要比對的字串S1~Sn
    for(int i = 0; i < n; i++){
        fgets(compare_str[i], sizeof(compare_str[i]), stdin);
        compare_str[i][strlen(compare_str[i])-1] = '\0';
    }
    
    // 將input內的單字拆進input_word
    split_word(input, input_word, &input_word_count);

    // 遍歷所有可能
    for(int i = 0; i < n; i++){
        // 因為split_word()內的strtok()會改變傳入的string1，因此使用tmp_s1作為替代
        char s1[10][100], tmp_s1[100];
        int s1_word_count = 0;
        strcpy(tmp_s1, compare_str[i]);
        split_word(tmp_s1, s1, &s1_word_count);
        
        for(int j = i+1; j < n; j++){
            char s2[10][100], tmp_s2[100];
            int s2_word_count = 0;
            strcpy(tmp_s2, compare_str[j]);
            split_word(tmp_s2, s2, &s2_word_count);
            
            // 如果符合條件一則繼續判斷，否則進行下一次循環
            if(stage1(s1, s2, s1_word_count, s2_word_count) > 0){
                ans += stage2(input_word, s1, s2, input_word_count, s1_word_count, s2_word_count);
            }
        }
    }
    
    // 輸出
    printf("%d\n", ans);
    return 0;
}