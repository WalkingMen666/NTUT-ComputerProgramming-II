#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 链表节点结构体
typedef struct Node {
    int coeff;  // 系数
    int exp;    // 指数
    struct Node* next;  // 指向下一项
} Node;

// 创建新节点
Node* createNode(int coeff, int exp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

// 添加节点到链表末尾
void appendNode(Node** head, int coeff, int exp) {
    Node* newNode = createNode(coeff, exp);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// 打印多项式
void printPolynomial(Node* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }
    Node* temp = head;
    int first = 1; // 用于控制正负号的输出
    while (temp != NULL) {
        if (temp->coeff != 0) {
            if (!first && temp->coeff > 0) {
                printf("+");
            }
            if (temp->exp == 0) {
                printf("%d", temp->coeff);
            } else if (temp->exp == 1) {
                if (temp->coeff == 1) {
                    printf("x");
                } else if (temp->coeff == -1) {
                    printf("-x");
                } else {
                    printf("%dx", temp->coeff);
                }
            } else {
                if (temp->coeff == 1) {
                    printf("x^%d", temp->exp);
                } else if (temp->coeff == -1) {
                    printf("-x^%d", temp->exp);
                } else {
                    printf("%dx^%d", temp->coeff, temp->exp);
                }
            }
            first = 0;
        }
        temp = temp->next;
    }
    printf("\n");
}

// 解析输入的多项式
Node* parsePolynomial(int* arr, int n) {
    Node* head = NULL;
    for (int i = 0; i < n; ++i) {
        if (arr[i] != 0) {
            appendNode(&head, arr[i], n - 1 - i);
        }
    }
    return head;
}

// 多项式加法
Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;
    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exp > poly2->exp) {
            appendNode(&result, poly1->coeff, poly1->exp);
            poly1 = poly1->next;
        } else if (poly1->exp < poly2->exp) {
            appendNode(&result, poly2->coeff, poly2->exp);
            poly2 = poly2->next;
        } else {
            int sum = poly1->coeff + poly2->coeff;
            if (sum != 0) {
                appendNode(&result, sum, poly1->exp);
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }
    while (poly1 != NULL) {
        appendNode(&result, poly1->coeff, poly1->exp);
        poly1 = poly1->next;
    }
    while (poly2 != NULL) {
        appendNode(&result, poly2->coeff, poly2->exp);
        poly2 = poly2->next;
    }
    return result;
}

// 多项式减法
Node* subtractPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;
    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exp > poly2->exp) {
            appendNode(&result, poly1->coeff, poly1->exp);
            poly1 = poly1->next;
        } else if (poly1->exp < poly2->exp) {
            appendNode(&result, -poly2->coeff, poly2->exp);
            poly2 = poly2->next;
        } else {
            int diff = poly1->coeff - poly2->coeff;
            if (diff != 0) {
                appendNode(&result, diff, poly1->exp);
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }
    while (poly1 != NULL) {
        appendNode(&result, poly1->coeff, poly1->exp);
        poly1 = poly1->next;
    }
    while (poly2 != NULL) {
        appendNode(&result, -poly2->coeff, poly2->exp);
        poly2 = poly2->next;
    }
    return result;
}

// 多项式乘法
Node* multiplyPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;
    for (Node* ptr1 = poly1; ptr1 != NULL; ptr1 = ptr1->next) {
        Node* temp = NULL;
        for (Node* ptr2 = poly2; ptr2 != NULL; ptr2 = ptr2->next) {
            int coeff = ptr1->coeff * ptr2->coeff;
            int exp = ptr1->exp + ptr2->exp;
            appendNode(&temp, coeff, exp);
        }
        result = addPolynomials(result, temp);
    }
    return result;
}

// 从用户输入中读取多项式
void readPolynomial(int** arr, int* n) {
    char input[1000];
    fgets(input, sizeof(input), stdin);

    char* token = strtok(input, " ");
    *n = 0;
    while (token != NULL) {
        (*arr)[(*n)++] = atoi(token);
        token = strtok(NULL, " ");
    }
}

int main() {
    // 从用户输入读取两个多项式
    int* arr1 = (int*)malloc(1000 * sizeof(int));
    int* arr2 = (int*)malloc(1000 * sizeof(int));
    int n1, n2;

    readPolynomial(&arr1, &n1);
    readPolynomial(&arr2, &n2);

    Node* poly1 = parsePolynomial(arr1, n1);
    Node* poly2 = parsePolynomial(arr2, n2);

    Node* sum = addPolynomials(poly1, poly2);
    Node* diff = subtractPolynomials(poly1, poly2);
    Node* prod = multiplyPolynomials(poly1, poly2);

    printPolynomial(sum);
    printPolynomial(diff);
    printPolynomial(prod);

    free(arr1);
    free(arr2);
    return 0;
}
