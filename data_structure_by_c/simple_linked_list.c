#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct SimpleLinkedListNode {
    struct SimpleLinkedListNode *next;
    char *data;
} LinkedList;

void testLinkedList();

bool isEmpty(LinkedList *list) {
    if (list->next == NULL) {
        return true;
    } else {
        return false;
    }
}

LinkedList *getEmptyLinkedList() {
    LinkedList *linked_list = (LinkedList *) malloc(sizeof(LinkedList));
    linked_list->data = NULL;
    linked_list->next = NULL;
    return linked_list;
}

LinkedList *getNewLinkedListNode(char *data) {
    LinkedList *linked_list = (LinkedList *) malloc(sizeof(LinkedList));
    linked_list->data = data;
    linked_list->next = NULL;
    return linked_list;
}

void appendFirst(LinkedList *list, char *data) {
    LinkedList *newNode = getNewLinkedListNode(data);
    newNode->next = list->next;
    list->next = newNode;
}

void append(LinkedList *list, char *data) {
    LinkedList *last_node = list;

    while (last_node->next != NULL) {
        last_node = last_node->next;
    }

    LinkedList *new_node = getNewLinkedListNode(data);
    new_node->next = NULL;
    last_node->next = new_node;
}

void removeByIndex(LinkedList *list, int target_index) {

    if (isEmpty(list)) {
        printf("is empty\n");
        return;
    }

    LinkedList *pre = list;
    LinkedList *cur = list->next;
    int index = 0;

    while (index < target_index) {
        pre = cur;
        cur = cur->next;
        index++;
        if (cur == NULL) {
            printf("out of index\n");
            return;
        }
    }

    pre->next = cur->next;
    free(cur);

}

void removeByElement(LinkedList *list, char *data) {

    if (isEmpty(list)) {
        printf("is empty\n");
        return;
    }

    LinkedList *pre = list;
    LinkedList *cur = list->next;

    while (strcmp(cur->data, data) != 0) {
        pre = cur;
        cur = cur->next;
        if (cur == NULL) {
            printf("no such element\n");
            return;
        }
    }

    pre->next = cur->next;
    free(cur);

}

LinkedList *getNode(LinkedList *list, int target_index) {
    LinkedList *target_node = list->next;
    int index = 0;

    while (index < target_index) {
        target_node = target_node->next;
        index++;
    }
    return target_node;
}

void showLinkedList(LinkedList *list) {
    LinkedList *cur = list->next;

    if (isEmpty(list)) {
        printf("is empty\n");
        return;
    } else {
        printf("[ ");
        printf("%s ", cur->data);
        cur = cur->next;
    }

    while (cur != NULL) {
        printf(", ");
        printf("%s ", cur->data);
        cur = cur->next;
    }

    printf("]\n");

}

void freeLinkedList(LinkedList *list) {
    LinkedList *pre = list;
    LinkedList *cur = list->next;

    while (cur->next != NULL) {
        pre = cur;
        cur = cur->next;
        free(pre);
    }
}

void testLinkedList() {

    char *a = "111";
    char *b = "222";
    char *c = "333";
    char *d = "444";
    char *e = "555";
    char *f = "666";
    char *g = "777";

    LinkedList *my_linked_list = getEmptyLinkedList();

    append(my_linked_list, a);
    append(my_linked_list, b);
    append(my_linked_list, c);
    append(my_linked_list, d);
    append(my_linked_list, e);
    append(my_linked_list, f);
    showLinkedList(my_linked_list);
    // expect: [ 111, 222, 333, 444, 555, 666 ]

    printf("index: %d, data %s\n", 3, getNode(my_linked_list, 3)->data);
    // expect: index: 3, data 444

    removeByElement(my_linked_list, "9999");
    // expect: no such element

    removeByIndex(my_linked_list, 9999);
    // expect: out of bound

    appendFirst(my_linked_list, g);
    showLinkedList(my_linked_list);
    // expect: [ 777 , 111 , 222 , 333 , 444 , 555 , 666 ]

    removeByElement(my_linked_list, "444");
    showLinkedList(my_linked_list);
    // expect: [ 777 , 111 , 222 , 333 , 555 , 666 ];

    removeByElement(my_linked_list, "666");
    removeByElement(my_linked_list, "777");
    showLinkedList(my_linked_list);
    // expect: [ 111 , 222 , 333 , 555 ]

    removeByIndex(my_linked_list, 1);
    removeByIndex(my_linked_list, 0);
    showLinkedList(my_linked_list);
    // expect: [ 333 , 555 ]

    freeLinkedList(my_linked_list);

}
