#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() {
        size = 0;
    }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        data[size] = idx;
        upheap(size, weightArr);
        size++;
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        int index = data[0];
        data[0] = data[size - 1];
        size--;
        downheap(0, weightArr);
        return (index);
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        while (pos > 0) {
            int p = pos/2;
            if (weightArr[data[pos]] < weightArr[data[p]]) {
                int temp = data[pos];
                data[pos] = data[p];
                data[p] = temp;
                pos = p;
            }
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        int index = pos;
        while (weightArr[index] > weightArr[pos/2]) {

        }
    }
};

#endif