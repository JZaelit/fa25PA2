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
        size++;
        upheap(size, weightArr);
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        if (size == 0) {
            return -1;
        }
        if (size == 1) {
            int index = data[size - 1];
            size--;
            return index;
        }
        int index = data[0];
        data[0] = data[size - 1];
        size--;
        downheap(0, weightArr);
        return (index);
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        while (weightArr[data[pos]] < weightArr[data[pos/2]]) {
            int temp = data[pos];
            data[pos] = data[pos/2];
            data[pos/2] = temp;
            pos = pos/2;
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        while (2*pos+1 < size) {
            if (2*pos+2 < size && weightArr[data[2*pos+2]] < weightArr[data[2*pos+1]] && weightArr[data[pos]] > weightArr[data[2*pos+2]]) {
                int temp = data[pos];
                data[pos] = data[2*pos+2];
                data[2*pos+2] = temp;
                pos = 2*pos+2;
            }
            else if (weightArr[data[pos]] > weightArr[data[2*pos+1]]) {
                int temp = data[pos];
                data[pos] = data[2*pos+1];
                data[2*pos+1] = temp;
                pos = 2*pos+1;
            }
            else {
                break;
            }
        }
    }
};

#endif