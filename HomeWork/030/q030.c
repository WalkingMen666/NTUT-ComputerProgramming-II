#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s {
    int data;
    struct node_s *next;
} node_t;

typedef node_t *nodep_t;

typedef struct {
    nodep_t front;
    nodep_t rear;
} Queue;

// 初始化Queue
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

// push操作
void push(Queue* q, int data) {
    nodep_t temp = (nodep_t)malloc(sizeof(node_t));
    temp->data = data;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

// pop操作
void pop(Queue* q) {
    if (q->front == NULL) {
        printf("Queue is empty\n");
        return;
    }
    nodep_t temp = q->front;
    printf("%d\n", q->front->data);
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
}

// front操作
void front(Queue* q) {
    if (q->front == NULL) {
        printf("Queue is empty\n");
    } else {
        printf("%d\n", q->front->data);
    }
}

// empty操作
void empty(Queue* q) {
    if (q->front == NULL) {
        printf("Queue is empty\n");
        return;
    }
    nodep_t temp;
    while (q->front != NULL) {
        temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    q->rear = NULL;
}

// print操作
void print(Queue* q) {
    if (q->front == NULL) {
        printf("Queue is empty\n");
        return;
    }
    nodep_t temp = q->front;
    while (temp != NULL) {
        printf("%d\n", temp->data);
        temp = temp->next;
    }
}

int main() {
    int N;
    scanf("%d", &N);
    Queue* q = createQueue();

    char operation[10];
    int data;

    for (int i = 0; i < N; ++i) {
        scanf("%s", operation);
        if (strcmp(operation, "push") == 0) {
            scanf("%d", &data);
            push(q, data);
        } else if (strcmp(operation, "pop") == 0) {
            pop(q);
        } else if (strcmp(operation, "front") == 0) {
            front(q);
        } else if (strcmp(operation, "empty") == 0) {
            empty(q);
        } else if (strcmp(operation, "print") == 0) {
            print(q);
        }
    }

    // 清理記憶體
    // empty(q);
    free(q);

    return 0;
}
