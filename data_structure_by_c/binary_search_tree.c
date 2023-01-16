#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum OrderType {
    PRE_ORDER = 0,
    IN_ORDER = 1,
    POST_ORDER = 2
};

typedef struct BinarySearchTreeNode {
    struct BinarySearchTreeNode *left, *right;
    int data;
} BinarySearchTreeNode;

BinarySearchTreeNode *noSuchElementException() {
    printf("no such element\n");
    return NULL;
}

BinarySearchTreeNode *getBinaryTree(int data) {

    BinarySearchTreeNode *newNode = (BinarySearchTreeNode *) malloc(sizeof(BinarySearchTreeNode));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

BinarySearchTreeNode *insert(BinarySearchTreeNode *node, int data) {

    if (node == NULL) {
        BinarySearchTreeNode *newNode = getBinaryTree(data);
        return newNode;
    } else if (data < node->data) {
        node->left = insert(node->left, data);
    } else if (node->data < data) {
        node->right = insert(node->right, data);
    } else {
        printf("duplicated data\n");
    }

    return node;
}

BinarySearchTreeNode *search(BinarySearchTreeNode *node, int targetData) {

    if (node->data == targetData) {
        return node;
    } else if (targetData < node->data) {
        if (node->left != NULL) {
            BinarySearchTreeNode *foundLeftNode = search(node->left, targetData);
            return foundLeftNode;
        }
    } else if (node->data < targetData) {
        if (node->right != NULL) {
            BinarySearchTreeNode *foundRightNode = search(node->right, targetData);
            return foundRightNode;
        }
    }

    return noSuchElementException();

}

BinarySearchTreeNode *searchParent(BinarySearchTreeNode *node, int targetData) {

    BinarySearchTreeNode *parentNode = NULL;
    BinarySearchTreeNode *targetNode = node;

    while ((targetNode != NULL) && (targetNode->data != targetData)) {
        parentNode = targetNode;
        if (targetData < targetNode->data) {
            targetNode = targetNode->left;
        } else {
            targetNode = targetNode->right;
        }
    }

    if (targetNode == NULL) {
        printf("no such element\n");
    }

    return parentNode;
}

void preOrder(BinarySearchTreeNode *node) {

    BinarySearchTreeNode *root = node;
    if (root == NULL) return;

    printf("%d ", root->data);
    preOrder(node->left);
    preOrder(node->right);

}

void inOrder(BinarySearchTreeNode *node) {

    BinarySearchTreeNode *root = node;
    if (root == NULL) return;

    inOrder(node->left);
    printf("%d ", root->data);
    inOrder(node->right);

}

void postOrder(BinarySearchTreeNode *node) {

    BinarySearchTreeNode *root = node;
    if (root == NULL) return;

    postOrder(node->left);
    postOrder(node->right);
    printf("%d ", root->data);

}

void order(BinarySearchTreeNode *node, enum OrderType orderType) {

    switch (orderType) {
        case PRE_ORDER:
            preOrder(node);
            printf("\n");
            break;
        case IN_ORDER:
            inOrder(node);
            printf("\n");
            break;
        case POST_ORDER :
            postOrder(node);
            printf("\n");
            break;
    }
}

void deleteSingleChildNode(BinarySearchTreeNode *parentNode, BinarySearchTreeNode *targetNode) {
    if (parentNode->left == targetNode) {
        if (targetNode->left != NULL) {
            parentNode->left = targetNode->left;
        } else {
            parentNode->left = targetNode->right;
        }
    } else {
        if (targetNode->left != NULL) {
            parentNode->right = targetNode->left;
        } else {
            parentNode->right = targetNode->right;
        }
    }
}

bool isLeafNode(BinarySearchTreeNode *node) {
    return node != NULL && node->left == NULL && node->right == NULL;
}

bool isBinaryNode(BinarySearchTreeNode *node) {
    return node != NULL && node->left != NULL && node->right != NULL;
}

BinarySearchTreeNode *getLeastFromRight(BinarySearchTreeNode *node) {
    BinarySearchTreeNode *leastNode = node->right;

    while (leastNode->left != NULL) {
        leastNode = leastNode->left;
    }
    return leastNode;
}

void delete(BinarySearchTreeNode *node, int targetData) {

    BinarySearchTreeNode *target = search(node, targetData);

    if (target != NULL) {

        BinarySearchTreeNode *parentOfTarget = searchParent(node, targetData);

        // 삭제할 노드가 루트 노드일 경우
        if (parentOfTarget == NULL) {
            printf("is root \n");
            return;
        }

        // 삭제할 노드가 리프 노드일 경우
        if (isLeafNode(target)) {

            if (parentOfTarget->left == target) {
                parentOfTarget->left = NULL;
            } else {
                parentOfTarget->right = NULL;
            }

            // 삭제할 노드가 자식이 두 개인 노드일 경우
            // 삭제할 노드의 오른쪽 트리에서 최솟값을 찾아서 대체하기
        } else if (isBinaryNode(target)) {

            BinarySearchTreeNode *least = getLeastFromRight(target);
            BinarySearchTreeNode *parentOfLeast = searchParent(node, least->data);

            // 최솟값 노드가 리프 노드일 경우
            if (isLeafNode(least)) {

                least->left = target->left;

                if (parentOfTarget->left == target) {
                    parentOfTarget->left = least;
                } else {
                    parentOfTarget->right = least;
                }
                parentOfLeast->left = NULL;

                // 최솟값 노드가 하나의 자식을 가질 경우
            } else {
                least->left = target->left;
                if (parentOfTarget->left == target) {
                    parentOfTarget->left = least;
                } else {
                    parentOfTarget->right = least;
                }
                parentOfLeast->left = least->right;
                least->right = target->right;

            }

            // 삭제할 노드가 자식이 하나인 노드일 경우
        } else {
            deleteSingleChildNode(parentOfTarget, target);
        }

        free(target);
    }

}

void testOrders() {

    BinarySearchTreeNode *root = getBinaryTree(1);
    root->left = getBinaryTree(2);
    root->right = getBinaryTree(3);
    root->left->left = getBinaryTree(4);
    root->left->right = getBinaryTree(5);
    // root : 1
    // node 1 : left 2, right 3
    // node 2 : left 4, right 5
    // node 3 : leaf

    order(root, PRE_ORDER);
    // expect: 1 2 4 5 3

    order(root, IN_ORDER);
    // expect: 4 2 5 1 3

    order(root, POST_ORDER);
    // expect: 4 5 2 3 1
}

void testBinarySearchTree() {

    BinarySearchTreeNode *root = getBinaryTree(100);
    insert(root, 50);
    insert(root, 40);
    insert(root, 120);
    insert(root, 1000);
    insert(root, 1);
    insert(root, 170);
    insert(root, 60);
    insert(root, 70);
    insert(root, 45);
    insert(root, 9999);

    order(root, PRE_ORDER);
    // expect: 100 50 40 1 2 45 60 70 120 1000 170 9999

    printf("is %d leafNode? : %s \n", 1000, isLeafNode(search(root, 1000)) ? "true" : "false");
    // expect: is 1000 leafNode? : false
    printf("is %d leafNode? : %s \n", 2, isLeafNode(search(root, 2)) ? "true" : "false");
    // expect: is 2 leafNode? : true

    search(root, 7);
    // expect: no such element

    // delete leaf node
    delete(root, 9999);
    order(root, PRE_ORDER);
    // expect: 100 50 40 1 2 45 60 70 120 1000 170

    searchParent(root, 654165);
    // expect: no such element

    int targetNodeData = 170;
    printf("%d parent is %d\n", targetNodeData, searchParent(root, targetNodeData)->data);
    // expect: 170 parent is 1000

    // delete single child node
    delete(root, 60);
    order(root, PRE_ORDER);
    // expect: 100 50 40 1 2 45 60 70 120 1000 170

    insert(root, 9999);
    order(root, PRE_ORDER);
    // expect: 100 50 40 1 45 70 120 1000 170 9999

    // delete binary node that leastNode is leafNode (targetNode from parent's left)
    delete(root, 50);
    order(root, PRE_ORDER);
    // expect: 100 70 40 1 45 120 1000 170 9999

    // delete binary node that leastNode is leafNode (targetNode from parent's right)
    delete(root, 1000);
    order(root, PRE_ORDER);
    // expect: 100 70 40 1 45 120 9999 170

    insert(root, 41);
    insert(root, 43);
    order(root, PRE_ORDER);
    // expect : 100 70 40 1 45 41 43 120 9999 170

    // delete binary node that leafNode has single child (targetNode from parent's left)
    delete(root, 40);
    order(root, PRE_ORDER);
    // expect: 100 70 41 1 45 43 120 9999 170

    insert(root, 100000);
    insert(root, 10000);
    insert(root, 20000);
    order(root, PRE_ORDER);
    // expect: 100 70 41 1 45 43 120 9999 170 100000 10000 20000

    // delete binary node that leafNode has single child (targetNode from parent's right)
    delete(root, 9999);
    order(root, PRE_ORDER);
    // expect : 100 70 41 1 45 43 120 10000 170 100000 20000

}
