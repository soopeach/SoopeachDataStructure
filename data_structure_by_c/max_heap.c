#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct HeapNodeType {
    int data;
} HeapNode;

typedef struct HeapType {
    int max_count;
    int current_count;
    HeapNode *heap_data;
} Heap;

Heap *createHeap(int heap_size) {
    Heap *heap = (Heap *) malloc(sizeof(Heap));
    heap->max_count = heap_size;
    heap->current_count = 0;
    // 인덱스 관리가 편하게 1부터 시작하므로 max_count + 1개의 크기를 동적으로 할당
    heap->heap_data = (HeapNode *) malloc(sizeof(HeapNode) * (heap_size + 1));
    return heap;
}

HeapNode *getRoot(Heap *heap) {
    return &heap->heap_data[1];
}

HeapNode *getLast(Heap *heap) {
    return &heap->heap_data[heap->current_count];
}

bool isFull(Heap *heap) {
    return heap->max_count == heap->current_count;
}

bool isNotEmpty(Heap *heap) {
    return heap->current_count != 0;
}

void swap(Heap *heap, int target_a, int target_b) {
    HeapNode temp = heap->heap_data[target_a];
    heap->heap_data[target_a] = heap->heap_data[target_b];
    heap->heap_data[target_b] = temp;
}

void insert(Heap *heap, int data) {
    if (isFull(heap)) {
        printf("heap is full!");
        return;
    } else {

        int index = ++heap->current_count;

        // 부모보다 크다면 부모와 위치를 바꿔준다.
        while ((index != 1) && data > heap->heap_data[index / 2].data) {
            heap->heap_data[index] = heap->heap_data[index / 2];
            index /= 2;
        }

        heap->heap_data[index].data = data;
    }
}

void showAll(Heap *heap) {

    if (isNotEmpty(heap)) {
        printf("[ ");
        for (int i = 1; i <= heap->current_count; ++i) {
            printf("%d, ", heap->heap_data[i].data);
        }
        printf("]\n");

    } else {
        printf("heap is empty!");
        return;
    }
}

int delete(Heap *heap) {

    if (isNotEmpty(heap)) {

        HeapNode *root_node = getRoot(heap);
        int root_data = root_node->data;
        HeapNode *last_node = getLast(heap);
        int last_data = last_node->data;

        root_node->data = last_data;
        last_node->data = 0;

        int cur_heap_size = heap->current_count;
        int cur_index = 1;
        int left_child_index = 2;
        int right_child_index = 3;

        while (left_child_index <= cur_heap_size && right_child_index <= cur_heap_size) {

            int left_child = heap->heap_data[left_child_index].data;
            int right_child = heap->heap_data[right_child_index].data;
            int cur_data = heap->heap_data[cur_index].data;

            if (left_child < right_child) {
                if (right_child <= cur_data) break;
                swap(heap, right_child_index, cur_index);
                cur_index = right_child_index;
            } else {
                if (left_child <= cur_data) break;
                swap(heap, left_child_index, cur_index);
                cur_index = left_child_index;
            }

            left_child_index = cur_index * 2;
            right_child_index = left_child_index + 1;

        }

        heap->current_count--;
        return root_data;
    } else {
        printf("heap is empty!");
        return -1;
    }

}

void testMaxHeap() {

    Heap *heap = createHeap(50);
    insert(heap, 50);
    insert(heap, 100);
    insert(heap, 1000);
    insert(heap, 678678);
    insert(heap, 1);
    insert(heap, 2);
    insert(heap, 3);
    insert(heap, 4);
    insert(heap, 5);
    insert(heap, 7);
    insert(heap, 9);
    insert(heap, 8);

    showAll(heap);
    // expect: [ 678678, 1000, 100, 50, 9, 8, 3, 4, 5, 1, 7, 2, ]

    delete(heap); // return 678678
    showAll(heap);
    // expect: [ 1000, 50, 100, 5, 9, 8, 3, 4, 2, 1, 7, ]

    delete(heap); // return 1000
    showAll(heap);
    // expect: [ 100, 50, 8, 5, 9, 7, 3, 4, 2, 1, ]

    while (isNotEmpty(heap)) {
        printf("return %d \n", delete(heap));
    }
    // expect :
    // return 100
    // return 50
    // return 9
    // return 8
    // return 7
    // return 5
    // return 4
    // return 3
    // return 1
    // return 2

    delete(heap);
    // expect: heap is empty!
}

int main() {
    testMaxHeap();
    return 0;
}