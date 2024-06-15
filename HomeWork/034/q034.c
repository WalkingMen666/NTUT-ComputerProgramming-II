#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s {
    char data;
    struct node_s *right, *left;
} tree_t;

typedef tree_t* btree;

// 創建新節點
btree new_node(char data) {
    btree node = (btree)malloc(sizeof(tree_t));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// 查找字符在中序序列中的索引
int search(char* str, int start, int end, char value) {
    for (int i = start; i <= end; i++) {
        if (str[i] == value) return i;
    }
    return -1;
}

// 使用前序和中序構建二元樹
btree build_tree_pre_in(char* pre, char* in, int in_start, int in_end, int* pre_index) {
    if (in_start > in_end) return NULL;
    
    btree node = new_node(pre[*pre_index]);
    (*pre_index)++;
    
    if (in_start == in_end) return node;
    
    int in_index = search(in, in_start, in_end, node->data);
    
    node->left = build_tree_pre_in(pre, in, in_start, in_index - 1, pre_index);
    node->right = build_tree_pre_in(pre, in, in_index + 1, in_end, pre_index);
    
    return node;
}

// 使用後序和中序構建二元樹
btree build_tree_post_in(char* post, char* in, int in_start, int in_end, int* post_index) {
    if (in_start > in_end) return NULL;
    
    btree node = new_node(post[*post_index]);
    (*post_index)--;
    
    if (in_start == in_end) return node;
    
    int in_index = search(in, in_start, in_end, node->data);
    
    node->right = build_tree_post_in(post, in, in_index + 1, in_end, post_index);
    node->left = build_tree_post_in(post, in, in_start, in_index - 1, post_index);
    
    return node;
}

// 廣度優先遍歷樹並輸出節點
void print_level_order(btree root) {
    if (root == NULL) return;
    
    btree queue[20];
    int front = 0, rear = 0;
    queue[rear++] = root;
    
    while (front < rear) {
        btree node = queue[front++];
        
        printf("%c", node->data);
        
        if (node->left != NULL) queue[rear++] = node->left;
        if (node->right != NULL) queue[rear++] = node->right;
    }
}

int main() {
    char order1, order2;
    char str1[21], str2[21];
    
    // 輸入遍歷方式和序列
    scanf(" %c", &order1);
    scanf("%s", str1);
    scanf(" %c", &order2);
    scanf("%s", str2);
    
    btree root = NULL;
    
    if (order1 == 'P' && order2 == 'I') {
        int pre_index = 0;
        root = build_tree_pre_in(str1, str2, 0, strlen(str2) - 1, &pre_index);
    } else if (order1 == 'I' && order2 == 'O') {
        int post_index = strlen(str2) - 1;
        root = build_tree_post_in(str2, str1, 0, strlen(str1) - 1, &post_index);
    } else if (order1 == 'O' && order2 == 'I') {
        int post_index = strlen(str1) - 1;
        root = build_tree_post_in(str1, str2, 0, strlen(str2) - 1, &post_index);
    } else if (order1 == 'I' && order2 == 'P') {
        int pre_index = 0;
        root = build_tree_pre_in(str2, str1, 0, strlen(str1) - 1, &pre_index);
    }
    
    // 輸出樹的節點
    print_level_order(root);
    printf("\n");
    
    return 0;
}
