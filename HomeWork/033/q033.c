#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_CITIES 20

// Queue for BFS
typedef struct {
    int items[MAX_CITIES];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

bool isEmpty(Queue *q) {
    return q->front == -1;
}

bool isFull(Queue *q) {
    return q->rear == MAX_CITIES - 1;
}

void enqueue(Queue *q, int value) {
    if (isFull(q))
        return;
    if (isEmpty(q))
        q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue *q) {
    int item;
    if (isEmpty(q)) {
        // printf("Queue is empty\n");
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return item;
}

// Function to find the shortest path using BFS
void findShortestPath(int graph[MAX_CITIES][MAX_CITIES], int start, int end, int *dist, int *prev) {
    bool visited[MAX_CITIES] = {false};
    Queue q;
    initQueue(&q);

    for (int i = 0; i < MAX_CITIES; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }

    visited[start] = true;
    dist[start] = 0;
    enqueue(&q, start);

    while (!isEmpty(&q)) {
        int city = dequeue(&q);

        for (int i = 0; i < MAX_CITIES; i++) {
            if (graph[city][i] && !visited[i]) {
                visited[i] = true;
                dist[i] = dist[city] + 1;
                prev[i] = city;
                enqueue(&q, i);

                if (i == end)
                    return;
            }
        }
    }
}

// Utility function to print the path
void printPath(int *prev, int start, int end) {
    if (end == -1 || prev[end] == -1) {
        printf("NO\n");
        return;
    }

    int path[MAX_CITIES];
    int count = 0;
    for (int at = end; at != -1; at = prev[at]) {
        path[count++] = at;
    }

    for (int i = count - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i != 0) printf(" ");
    }
    printf("\n");
}

int main() {
    int N, X, Z, Y = -1;
    char buffer[100];

    fgets(buffer, sizeof(buffer), stdin);
    int numArgs = sscanf(buffer, "%d %d %d %d", &N, &X, &Z, &Y);

    int graph[MAX_CITIES][MAX_CITIES] = {0};

    for (int i = 0; i < N; i++) {
        int A, B;
        scanf("%d %d", &A, &B);
        graph[A][B] = 1;
        graph[B][A] = 1;
    }

    int dist1[MAX_CITIES], prev1[MAX_CITIES];
    findShortestPath(graph, X, Z, dist1, prev1);

    if (numArgs == 4 && Y != -1) {
        int dist2[MAX_CITIES], prev2[MAX_CITIES];
        findShortestPath(graph, X, Y, dist1, prev1);
        findShortestPath(graph, Y, Z, dist2, prev2);

        if (dist1[Y] != INT_MAX && dist2[Z] != INT_MAX) {
            printf("%d\n", dist1[Y] + dist2[Z]);
            int path1[MAX_CITIES], count1 = 0;
            for (int at = Y; at != -1; at = prev1[at]) {
                path1[count1++] = at;
            }
            for (int i = count1 - 1; i >= 0; i--) {
                printf("%d", path1[i]);
                if (i != 0) printf(" ");
            }
            int path2[MAX_CITIES], count2 = 0;
            for (int at = Z; at != -1 && at != Y; at = prev2[at]) {
                path2[count2++] = at;
            }
            for (int i = count2 - 1; i >= 0; i--) {
                printf(" %d", path2[i]);
            }
            printf("\n");
        } else {
            printf("NO\n");
        }
    } else {
        if (dist1[Z] != INT_MAX) {
            printf("%d\n", dist1[Z]);
            printPath(prev1, X, Z);
        } else {
            printf("NO\n");
        }
    }

    return 0;
}