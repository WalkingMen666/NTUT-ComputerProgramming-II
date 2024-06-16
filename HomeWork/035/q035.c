#include <stdio.h>
#include <stdlib.h>

typedef struct node_s {
    int time;
    int waiteNodeNum;
    int waiteNode[100];
    struct node_s* next;
} node_t;
typedef node_t* node_p;

void freeList(node_p head) {
    node_p tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int calculateProjectTime(node_p head, int M) {
    int maxTime[101] = {0};
    int indegree[101] = {0};
    node_p nodes[101];
    
    node_p cur = head;
    for (int i = 1; i <= M; i++) {
        nodes[i] = cur;
        for (int j = 0; j < cur->waiteNodeNum; j++) {
            indegree[cur->waiteNode[j]]++;
        }
        cur = cur->next;
    }

    int queue[101], front = 0, rear = 0;
    
    for (int i = 1; i <= M; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
            maxTime[i] = nodes[i]->time;
        }
    }

    while (front < rear) {
        int current = queue[front++];
        node_p curNode = nodes[current];
        for (int i = 0; i < curNode->waiteNodeNum; i++) {
            int nextNode = curNode->waiteNode[i];
            if (--indegree[nextNode] == 0) {
                queue[rear++] = nextNode;
            }
            if (maxTime[nextNode] < maxTime[current] + nodes[nextNode]->time) {
                maxTime[nextNode] = maxTime[current] + nodes[nextNode]->time;
            }
        }
    }

    int maxProjectTime = 0;
    for (int i = 1; i <= M; i++) {
        if (maxProjectTime < maxTime[i]) {
            maxProjectTime = maxTime[i];
        }
    }

    return maxProjectTime;
}

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        int M;
        scanf("%d", &M);

        node_p head = NULL, tail = NULL;

        for (int j = 0; j < M; j++) {
            int time, K;
            node_p newNode = (node_p)malloc(sizeof(node_t));
            newNode->next = NULL;

            scanf("%d %d", &time, &K);
            newNode->time = time;
            newNode->waiteNodeNum = K;

            for (int k = 0; k < K; k++) {
                scanf("%d", &newNode->waiteNode[k]);
            }

            if (head == NULL) {
                head = newNode;
            } else {
                tail->next = newNode;
            }
            tail = newNode;
        }

        int projectTime = calculateProjectTime(head, M);
        printf("%d\n", projectTime);

        freeList(head);
    }

    return 0;
}
