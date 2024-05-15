#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define swap(x,y) {int t; t=x; x=y; y=t;}

// 排序用的比較function
int cmpfunc(const void * a, const void * b){return (*(int*)a - *(int*)b);}

// 排序
void sort(char word_array[100][1000], int count_array[], int length){
    // 不重複的出現次數陣列 & 記錄它的長度的變數
    int count = 0;
    int *appear_times = calloc(length, sizeof(int));

    for(int i = 0; i < length; i++){
        int j = 0;
        for(; j < count; j++){
            if(count_array[i] == appear_times[j]) break;
        }
        if(j == count) appear_times[count++] = count_array[i];
    }
    // 對出現次數陣列做排序(小->大 = 出現次數少->出現次數多)
    qsort(appear_times, count, sizeof(int), cmpfunc);

    // 從出現次數最多的往下遍歷，找出所有符合當前出現次數的單字的index，並加入到index_array做紀錄
    // 針對index_array對應的單字做bubble-sort，接著印出當前出現次數的答案再進入下一個循環
    for(int i = count-1; i > -1; i--){
        // 紀錄符合當前出現次數的單字
        int index = 0;
        int *index_array = calloc(length, sizeof(int));
        for(int j = 0; j < length; j++)
            if(count_array[j] == appear_times[i]) 
                index_array[index++] = j;
        // 對index_array對應的單字做bubble-sort
        for(int x = 0; x < index; x++){
            for(int y = x+1; y < index; y++){
                int minLen = min(strlen(word_array[index_array[x]]), strlen(word_array[index_array[y]]));
                int j = 0;
                for(; j < minLen; j++){
                    if(word_array[index_array[x]][j] > word_array[index_array[y]][j]){
                        swap(index_array[x], index_array[y]);
                        break;
                    }
                    else if(word_array[index_array[x]][j] < word_array[index_array[y]][j]) break;
                }
                if(j == minLen){
                    if(strlen(word_array[index_array[x]]) > strlen(word_array[index_array[y]]))
                        swap(index_array[x], index_array[y]);
                }
            }
        }
        // 印出當前出現次數的答案
        for(int j = 0; j < index; j++){
            printf("%s %d\n", word_array[index_array[j]], count_array[index_array[j]]);
        }
    }
}

// mod1 = 將字串s中的old_word取代為new_word
// mod2 = 在字串s中的old_word前加入new_word及空格
// mod3 = 刪除在字串s中出現的old_word及空格
char* replaceWord(const char* s, const char* old_word, const char* new_word, int mod)
{
    char* result;
    int i, cnt = 0;
    int newWlen = strlen(new_word);
    int oldWlen = strlen(old_word);
  
    // 計算old_word出現的次數(不一定為正確值)
    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], old_word) == &s[i]) {
            cnt++;
            i += oldWlen - 1;
        }
    }
    if(mod == 1){
        // 動態分配結果的記憶體大小
        result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);
        i = 0;
        while (*s){
            // 將符合條件的old_word替換為new_word
            if (strstr(s, old_word) == s && ((*(s-1) == ' ' && (*(s+oldWlen) == ' ' || *(s+oldWlen) == '\0')) || (i == 0 && (*(s+oldWlen) == ' ' || *(s+oldWlen) == '\0')))) {
                strcpy(&result[i], new_word);
                i += newWlen;
                s += oldWlen;
            }
            else result[i++] = *(s++);
        }
    }
    else if(mod == 2){
        result = (char*)malloc(i + cnt*(newWlen+1) + 1);
        i = 0; 
        while (*s){
            if (strstr(s, old_word) == s && ((*(s-1) == ' ' && (*(s+oldWlen) == ' ' || *(s+oldWlen) == '\0')) || (i == 0 && (*(s+oldWlen) == ' ' || *(s+oldWlen) == '\0')))) {
                strcpy(&result[i], new_word);
                i += newWlen;
                result[i] = ' ';
                i++;
            }
            result[i++] = *(s++);
        }
    }
    else if(mod == 3){
        result = (char*)malloc(i - cnt*(oldWlen+1) + 1);
        i = 0;
        while (*s){
            if (strstr(s, old_word) == s && ((*(s-1) == ' ' && (*(s+oldWlen) == ' ' || *(s+oldWlen) == '\0')) || (i == 0 && (*(s+oldWlen) == ' ' || *(s+oldWlen) == '\0')))) {
                s += oldWlen+1;
            }
            else result[i++] = *(s++);
        }
    }

    result[i] = '\0';
    return result;
}

void sol4(char *article){
    // 紀錄單字及其出現次數的陣列們
    char ans4_word[100][1000];
    int ans4_count[100] = {0}, index = 0, count = 0;
    
    // 取得在article中出現的空格的指針
    char *token = strtok(article, " ");
//1234\05678\05757
    // 如果此單字已經出現過，將它對應的出現次數+1，否則將它新增到陣列中
    do{
        for(index = 0; index < count; index++){
            if(strcmp(ans4_word[index], token) == 0){
                ans4_count[index]+=1;
                break;
            }
        }
        if(index == count){
            for(int i = 0; i < strlen(token); i++) ans4_word[count][i] = token[i];
            ans4_word[count][strlen(token)] = '\0';
            ans4_count[count++] = 1;
        }
        // 找到下一個空格的指針
        token = strtok(NULL, " ");
    }while(token != NULL);

    // 排序
    sort(ans4_word, ans4_count, count);
}

int main(){
    char article[1000], P[100], Q[100];
    int voc_cnt = 0, wordCount = 0;
    // 輸入，使用fgets最後一個字元會是\n
    fgets(article, sizeof(article), stdin);
    scanf("%s %s", P, Q);
    
    // 將article的最後一個字元替換為\0
    article[strlen(article)-1] = '\0';

    // 取得各問題的答案
    char *ans1 = replaceWord(article, P, Q, 1);
    char *ans2 = replaceWord(article, P, Q, 2);
    char *ans3 = replaceWord(article, P, Q, 3);

    // 輸出 & 計算問題4答案
    printf("%s\n%s\n%s\n", ans1, ans2, ans3);
    sol4(article);

    return 0;
}