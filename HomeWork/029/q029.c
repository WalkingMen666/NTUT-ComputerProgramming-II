#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义节点结构
typedef struct node_s {
    int data;
    struct node_s *next;
} node_t;
typedef node_t* nodep_t;

// 定义堆栈结构
typedef struct {
    nodep_t top;
} stack_t;

// 初始化堆栈
void init_stack(stack_t *stack) {
    stack->top = NULL;
}

// 判断堆栈是否为空
int is_empty(stack_t *stack) {
    return stack->top == NULL;
}

// push 操作
void push(stack_t *stack, int data) {
    nodep_t new_node = (nodep_t)malloc(sizeof(node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = stack->top;
    stack->top = new_node;
}

// pop 操作
void pop(stack_t *stack) {
    if (is_empty(stack)) {
        printf("Stack is empty\n");
        return;
    }
    nodep_t temp = stack->top;
    printf("%d\n", temp->data);
    stack->top = stack->top->next;
    free(temp);
}

// top 操作
void top(stack_t *stack) {
    if (is_empty(stack)) {
        printf("Stack is empty\n");
        return;
    }
    printf("%d\n", stack->top->data);
}

// empty 操作
void empty(stack_t *stack, int sign) {
    if (is_empty(stack) && sign != -1) {
        printf("Stack is empty\n");
        return;
    }
    while (!is_empty(stack)) {
        nodep_t temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
    // printf("Stack is empty\n"); // Add this line to ensure output when stack becomes empty
}

// print 操作
void print(stack_t *stack) {
    if (is_empty(stack)) {
        printf("Stack is empty\n");
        return;
    }
    nodep_t current = stack->top;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

int main() {
    int N;
    char operation[10];
    int data;

    // 读取操作数
    scanf("%d", &N);
    
    stack_t stack;
    init_stack(&stack);

    for (int i = 0; i < N; i++) {
        scanf("%s", operation);
        if (strcmp(operation, "push") == 0) {
            scanf("%d", &data);
            push(&stack, data);
        } else if (strcmp(operation, "pop") == 0) {
            pop(&stack);
        } else if (strcmp(operation, "top") == 0) {
            top(&stack);
        } else if (strcmp(operation, "empty") == 0) {
            empty(&stack, 0);
        } else if (strcmp(operation, "print") == 0) {
            print(&stack);
        }
    }

    // 清理堆栈
    empty(&stack,  -1);

    return 0;
}
