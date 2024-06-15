#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定義雙向鏈結串列的節點結構
typedef struct dnode_s {
    int data;
    struct dnode_s *front;
    struct dnode_s *back;
} node_t;

typedef node_t* nodep_t;

// 在串列前端添加節點
void addFront(nodep_t* head, nodep_t* tail, int data) {
    nodep_t newNode = (nodep_t)malloc(sizeof(node_t));
    newNode->data = data;
    newNode->front = NULL;
    newNode->back = *head;
    if (*head != NULL) {
        (*head)->front = newNode;
    }
    *head = newNode;
    if (*tail == NULL) {
        *tail = newNode;
    }
}

// 在串列尾端添加節點
void addBack(nodep_t* head, nodep_t* tail, int data) {
    nodep_t newNode = (nodep_t)malloc(sizeof(node_t));
    newNode->data = data;
    newNode->back = NULL;
    newNode->front = *tail;
    if (*tail != NULL) {
        (*tail)->back = newNode;
    }
    *tail = newNode;
    if (*head == NULL) {
        *head = newNode;
    }
}

// 刪除串列最前端的節點
void removeFront(nodep_t* head, nodep_t* tail) {
    if (*head == NULL) {
        printf("Double link list is empty\n");
        return;
    }
    nodep_t temp = *head;
    *head = (*head)->back;
    if (*head != NULL) {
        (*head)->front = NULL;
    } else {
        *tail = NULL;
    }
    free(temp);
}

// 刪除串列最尾端的節點
void removeBack(nodep_t* head, nodep_t* tail) {
    if (*tail == NULL) {
        printf("Double link list is empty\n");
        return;
    }
    nodep_t temp = *tail;
    *tail = (*tail)->front;
    if (*tail != NULL) {
        (*tail)->back = NULL;
    } else {
        *head = NULL;
    }
    free(temp);
}

// 清空串列中的所有節點
void empty(nodep_t* head, nodep_t* tail) {
    if(*head == NULL) printf("Double link list is empty\n");
    else {
        while (*head != NULL) removeFront(head, tail);
    }
}

// 在第n個節點後插入新的資料
void insert(nodep_t* head, nodep_t* tail, int n, int data) {
    if (n <= 0) {
        printf("Invalid command\n");
        return;
    }
    nodep_t current = *head;
    for (int i = 1; i < n; i++) {
        if (current == NULL) {
            printf("Invalid command\n");
            return;
        }
        current = current->back;
    }
    if (current == NULL) {
        printf("Invalid command\n");
        return;
    }
    nodep_t newNode = (nodep_t)malloc(sizeof(node_t));
    newNode->data = data;
    newNode->front = current;
    newNode->back = current->back;
    if (current->back != NULL) {
        current->back->front = newNode;
    }
    current->back = newNode;
    if (newNode->back == NULL) {
        *tail = newNode;
    }
}

// 刪除第n個節點
void removeNode(nodep_t* head, nodep_t* tail, int n) {
    if (n <= 0) {
        printf("Invalid command\n");
        return;
    }
    nodep_t current = *head;
    for (int i = 1; i < n; i++) {
        if (current == NULL) {
            printf("Invalid command\n");
            return;
        }
        current = current->back;
    }
    if (current == NULL) {
        printf("Invalid command\n");
        return;
    }
    if (current->front != NULL) {
        current->front->back = current->back;
    } else {
        *head = current->back;
    }
    if (current->back != NULL) {
        current->back->front = current->front;
    } else {
        *tail = current->front;
    }
    free(current);
}

// 打印雙向鏈結串列中的所有節點
void print(nodep_t head) {
    if (head == NULL) {
        printf("Double link list is empty\n");
        return;
    }
    nodep_t current = head;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->back;
    }
}

int main() {
    int N;
    scanf("%d", &N);

    nodep_t head = NULL;
    nodep_t tail = NULL;

    char command[20];
    for (int i = 0; i < N; i++) {
        scanf("%s", command);
        if (strcmp(command, "addFront") == 0) {
            int data;
            scanf("%d", &data);
            addFront(&head, &tail, data);
        } else if (strcmp(command, "addBack") == 0) {
            int data;
            scanf("%d", &data);
            addBack(&head, &tail, data);
        } else if (strcmp(command, "removeFront") == 0) {
            removeFront(&head, &tail);
        } else if (strcmp(command, "removeBack") == 0) {
            removeBack(&head, &tail);
        } else if (strcmp(command, "empty") == 0) {
            empty(&head, &tail);
        } else if (strcmp(command, "insert") == 0) {
            int n, data;
            scanf("%d %d", &n, &data);
            insert(&head, &tail, n, data);
        } else if (strcmp(command, "remove") == 0) {
            int n;
            scanf("%d", &n);
            removeNode(&head, &tail, n);
        } else if (strcmp(command, "print") == 0) {
            print(head);
        }
    }

    // 清理所有剩餘的節點
    free(head);
    free(tail);

    return 0;
}
