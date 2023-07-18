//merge in decart tree
#include <stdio.h>
#include <stdlib.h>

// Структура для представления узла в Декартовом дереве
struct Node {
    int key;           // Ключ узла
    int priority;      // Приоритет узла
    struct Node* left; // Левое поддерево
    struct Node* right;// Правое поддерево
};

// Создание нового узла
struct Node* createNode(int key, int priority) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->priority = priority;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Разделение Декартова дерева на два поддерева по ключу
void split(struct Node* root, int key, struct Node** left, struct Node** right) {
    if (root == NULL) {
        *left = NULL;
        *right = NULL;
    } else if (root->key <= key) {
        split(root->right, key, &(root->right), right);
        *left = root;
    } else {
        split(root->left, key, left, &(root->left));
        *right = root;
    }
}

// Слияние двух Декартовых деревьев
struct Node* merge(struct Node* left, struct Node* right) {
    if (left == NULL)
        return right;
    if (right == NULL)
        return left;

    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    } else {
        right->left = merge(left, right->left);
        return right;
    }
}

// Вспомогательная функция для печати Декартова дерева (обход в порядке inorder)
void printTree(struct Node* node) {
    if (node == NULL)
        return;

    printTree(node->left);
    printf("Key: %d, Priority: %d\n", node->key, node->priority);
    printTree(node->right);
}

int main() {
    struct Node* root1 = createNode(1, 5);
    root1->left = createNode(2, 3);
    root1->right = createNode(3, 7);

    struct Node* root2 = createNode(4, 2);
    root2->left = createNode(5, 8);
    root2->right = createNode(6, 6);

    printf("Декартово дерево 1:\n");
    printTree(root1);

    printf("\nДекартово дерево 2:\n");
    printTree(root2);

    struct Node* merged = merge(root1, root2);

    printf("\nРезультат слияния двух Декартовых деревьев:\n");
    printTree(merged);

    return 0;
}
