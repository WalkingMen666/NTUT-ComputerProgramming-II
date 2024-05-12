#include <stdio.h>
#include <string.h>
typedef struct student_s{
    char name[50];
    int score;
}student_t;

void input(student_t s[], int n){
    for(int i = 0; i < n; i++) scanf("%s %d", s[i].name, &(s[i].score));
}

void getHigh(student_t s[], int n, char name[]){
    int tempAns = 0;
    for(int i = 0; i < n; i++){
        if(s[i].score > tempAns){
            tempAns = s[i].score;
            strcpy(name, s[i].name);
        }
    }
}

int getAverage(student_t s[], int n){
    int ans = 0;
    for(int i = 0; i < n; i++){
        ans += s[i].score;
    }
    return ans/n;
}

int main(){
    int N = 0, ans2 = 0;
    char ans1[100];

    scanf("%d", &N);
    student_t stu[N];
    
    input(stu, N);
    getHigh(stu, N, ans1);
    ans2 = getAverage(stu, N);

    printf("%s\n%d\n", ans1, ans2);
    return 0;
}