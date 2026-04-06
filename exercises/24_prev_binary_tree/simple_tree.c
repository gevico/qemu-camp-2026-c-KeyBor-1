#include "simple_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

Queue* create_queue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *q, TreeNode *tree_node) {
    QueueNode *node = (QueueNode*)malloc(sizeof(QueueNode));
    node->tree_node = tree_node;
    if(q->front == NULL) {
        q->rear = node;
        q->front = node;
        return;
    }
    q->rear->next = node;
    q->rear = node;
    return;
}

TreeNode* dequeue(Queue *q) {
    if(q->front == NULL) return NULL;
    QueueNode *node = q->front;
    TreeNode *tree_node = node->tree_node;
    q->front = q->front->next;
    if(q->front == NULL) {
        q->rear = NULL;
    }
    node->next = NULL;
    free(node);
    return tree_node;
}

TreeNode* createTreeNode(int val) {
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    if(node == NULL) return NULL;
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

bool is_empty(Queue *q) {
    return q->front == NULL;
}

void free_queue(Queue *q) {
    while (!is_empty(q)) {
        dequeue(q);
    }
    free(q);
}

TreeNode* build_tree_by_level(int *level_order, int size) {
    if(size == 0 || level_order[0] == INT_MIN) return NULL;
    Queue *q = create_queue();
    TreeNode* root = createTreeNode(level_order[0]);
    enqueue(q, root);
    int index = 1;
    while(!is_empty(q) && index < size) {
        TreeNode *cur = dequeue(q);
        if(index < size && level_order[index] != INT_MIN) {
            cur->left = createTreeNode(level_order[index]);
            enqueue(q, cur->left);
        } 
        index++;
        if(index < size && level_order[index] != INT_MIN) {
            cur->right = createTreeNode(level_order[index]);
            enqueue(q, cur->right);
        }
        index++;
    }
    return root;
}

void preorder_traversal(TreeNode *root) {
    if(root == NULL) return;
    printf("%d ", root->val);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

void preorder_traversal_iterative(TreeNode *root) {
    if(root == NULL) return;
    printf("%d ", root->val);
    preorder_traversal_iterative(root->left);
    preorder_traversal_iterative(root->right);
}

void free_tree(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
