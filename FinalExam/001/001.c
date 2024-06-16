#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void bubbleSort(char* arr[], int cou[], int size){
    for(int i = 0 ; i < size ; i++){
        for(int j = i + 1; j < size ; j++){
            if(cou[i] == cou[j] && strcmp(arr[i],arr[j]) > 0 ){
                char* tempword = arr[j];
                arr[j] == arr[i];
                arr[i] = tempword;

                int tempCount = cou[j];
                cou[j] = cou[i];
                cou[i] = tempCount;
            }

            else if(cou[i] < cou[j]){
                char* tempword = arr[i];
                arr[i] = arr[j];
                arr[j] = tempword;

                int tempCount = cou[i];
                cou[i] = cou[j];
                cou[j] = tempCount;

            }
        }
    }
}
void count(char* arr[], int cou[], int size){
    for(int i = 0 ; i < size ; i++){
        int count = 1 ;
        for(int k = 0 ; k < i ; k++){
            if(strcmp(arr[k],arr[i]) == 0){
                count = 0 ; 
                break;
            }
        }
        if(count == 1 ){
            for(int j = i + 1 ; j < size ; j++){
                if(strcmp(arr[i],arr[j]) == 0)count++;
            }
        }
        cou[i] = count;
    }
}   

int main(){
    char sentence[200]; 
    char *word[50];
    char word1[20];
    char word2[20];
    int Cou[50];
    int C , size;

    fgets(sentence,sizeof(sentence), stdin);
    scanf("%s %s", word1,word2);

    sentence[strlen(sentence) - 1] = '\0';
    sentence[strlen(sentence) + 1] = '\0';
    
    int i = 0;
    char* token = strtok(sentence, " ");
    while (token != NULL && i < 50) { //拆解句子
        word[i] = malloc(strlen(token) + 1); 
        strcpy(word[i], token); 
        token = strtok(NULL, " ");
        i++;
    }
    scanf("%d",&C);
    if(C == 1){
        for(int j = 0 ; j < i ; j++){
            if(strcmp(word[j],word1) == 0)printf("%s ",word2);
            printf("%s ",word[j]);
        }
    }else if(C == 2){
        for(int j = 0 ; j < i ; j++){
            if(strcmp(word[j],word1) == 0)printf("%s ",word2);
            else printf("%s ",word[j]);
        }
    }else if(C == 3){
        for(int j = 0 ; j < i ; j ++){
            if(strcmp(word[j],word1) == 0)continue;
            else printf("%s ",word[j]);
        }
    }else if(C == 4){
        count(word,Cou,i);
        int N;
        scanf("%d",&N);
       for(int j = 0 ; j < i ; j ++){ 
            if(Cou[j] >= N) {
                printf("%s ", word[j]);
            }
        }
    }else if(C == 5){
        count(word,Cou,i);
        bubbleSort(word,Cou,i);
        for(int j = i ;j > i-3;j--){
            printf("%s %d",word[j],Cou[j]);
        }
    }
}