#include <stdio.h>
#include <stdlib.h>

#define MAX_M 100

// 結構定義
typedef struct {
    int days;      // 完成此項目所需的天數
    int numDeps;   // 此項目依賴的項目數量
    int dependencies[MAX_M]; // 此項目的依賴項目編號
} ProjectNode;

// 計算單個專案的所需時間
int calculateProjectTime(ProjectNode nodes[], int M) {
    int indegree[MAX_M] = {0}; // 入度數組
    int duration[MAX_M] = {0}; // 完成每個節點所需的最長時間數組
    int queue[MAX_M];          // 拓撲排序的隊列
    int front = 0, rear = 0;

    // 初始化入度和依賴天數
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < nodes[i].numDeps; j++) {
            int dep = nodes[i].dependencies[j] - 1;
            indegree[dep]++;
        }
    }

    // 將入度為 0 的節點加入隊列
    for (int i = 0; i < M; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
            duration[i] = nodes[i].days;
        }
    }

    // 拓撲排序過程
    while (front < rear) {
        int node = queue[front++];
        for (int i = 0; i < nodes[node].numDeps; i++) {
            int dep = nodes[node].dependencies[i] - 1;
            if (--indegree[dep] == 0) {
                queue[rear++] = dep;
            }
            if (duration[dep] < duration[node] + nodes[dep].days) {
                duration[dep] = duration[node] + nodes[dep].days;
            }
        }
    }

    // 計算最長時間
    int maxTime = 0;
    for (int i = 0; i < M; i++) {
        if (duration[i] > maxTime) {
            maxTime = duration[i];
        }
    }

    return maxTime;
}

int main() {
    int N;
    scanf("%d", &N); // 讀取專案組數

    for (int i = 0; i < N; i++) {
        int M;
        scanf("%d", &M); // 讀取每組專案的工作事項數量

        ProjectNode nodes[MAX_M];
        for (int j = 0; j < M; j++) {
            scanf("%d %d", &nodes[j].days, &nodes[j].numDeps); // 讀取每個項目所需天數和依賴數量
            for (int k = 0; k < nodes[j].numDeps; k++) {
                scanf("%d", &nodes[j].dependencies[k]); // 讀取依賴的項目編號
            }
        }

        // 計算並輸出每組專案的最長時間
        int result = calculateProjectTime(nodes, M);
        printf("%d\n", result);
    }

    return 0;
}
