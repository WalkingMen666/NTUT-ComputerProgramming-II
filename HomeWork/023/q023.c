// 不用看了，我抄easn的
#include <stdio.h>
#include <string.h>

typedef struct student_s{
    char id[10];
    char type[10][10];
} student_t;

void sol(student_t stu[10],int co,int type_co){
    char *finid[10];
    int finans[10] = {0};
    char Grade[11][3] = {"A+","A","A-","B+","B","B-","C+","C","C-","F","X"};
    char GPA[11][4] = {"4.3","4.0","3.7","3.3","3.0","2.7","2.3","2.0","1.7","1","0"};
    char per[11][10] = {"90-100","85-89","80-84","77-79","73-76","70-72","67-69","63-66","60-62","1-59","0"};
    int ans[11] = {95,87,82,78,75,70,68,65,60,50,0};
    for(int sel = 0; sel < co; sel++){
        int fin = 0;
        for(int i = 0; i < type_co; i++){
            if('A' <= stu[sel].type[i][0] && stu[sel].type[i][0] <= 'X'){
                for(int u = 0; u < 11; u++){
                    if(strcmp(Grade[u], stu[sel].type[i]) == 0) fin += ans[u];
                }
            }
            else if('.' == stu[sel].type[i][1]){
                for(int u = 0; u < 11; u++){
                    if(strcmp(GPA[u], stu[sel].type[i])==0) fin += ans[u];
                }
            }
            else if('-' == stu[sel].type[i][2] || '-' == stu[sel].type[i][1]){
                for(int u = 0; u < 11; u++){
                    if(strcmp(per[u], stu[sel].type[i])==0) fin += ans[u];
                }
            }
            else if('1' == stu[sel].type[i][0]) fin += 50;
        }
        finid[sel] = stu[sel].id;
        finans[sel] = fin / type_co;
    }
    for(int i = 0; i < co; i++){
        int min = 0;
        for(int u = 1; u < co; u++){
            if(finans[min] > finans[u]) min = u;
        }
        printf("%s %d\n", finid[min], finans[min]);
        finans[min] = 1000;
    }
}

int main(){
    int type_co = 0, count = 0;
    char type[10][10];

    student_t stu[10];
    scanf("%d",&type_co);

    for(int i=0;i<type_co;i++) scanf("%s",type[i]);

    scanf("%d",&count);

    for(int i = 0; i < count; i++){
        scanf("%s", stu[i].id);
        for(int u = 0; u < type_co; u++){
            scanf("%s", stu[i].type[u]);
        }
    }
    sol(stu, count, type_co);

    return 0;
}