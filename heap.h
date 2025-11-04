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
        data[size] = idx; //stores index at end of heap
        upheap(size, weightArr); //calls upheap with size and weightArr as input parameters
        size++; //increments size to track num indices in data
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        if (size == 0) { //checks if size is 0 if so returns -1 to signal heap is empty
            return -1;
        }
        if (size == 1) { //checks if size is 1 to handle edge case of avoiding reassigning root to a index that doesnt exist
            int index = data[size - 1];
            size--;
            return index;
        }
        int index = data[0]; //stores root element of heap in index
        data[0] = data[size - 1]; //reassigns root to next node in heap essentially popping original root node from the heap
        size--; //decrements size because of pop
        downheap(0, weightArr); //calls downheap with root index 0 and weightArr
        return (index); //returns the original root index value
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        while (weightArr[data[pos]] < weightArr[data[pos/2]]) { //checks to see whether current child node has a smaller weight than its parent node
            int temp = data[pos]; //stores the child node value in a temp var
            data[pos] = data[pos/2]; //assigns the value of the parent node index to its child
            data[pos/2] = temp; //assigns the value of the child node index to its parent
            pos = pos/2; //updates position to the position of its parent to continue traversing upwards in the heap
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        while (2*pos+1 < size) { //condition to ensure left child accessed is not out of bounds
            if (2*pos+2 < size && weightArr[data[2*pos+2]] < weightArr[data[2*pos+1]] && weightArr[data[pos]] > weightArr[data[2*pos+2]]) { //ensures right child is not out of bounds, and right child weight is less than left child weight and parent weight, and parent weight is greater than right child weight
                int temp = data[pos]; //if all conditions met than swaps parent node with right child node
                data[pos] = data[2*pos+2];
                data[2*pos+2] = temp;
                pos = 2*pos+2;
            }
            else if (weightArr[data[pos]] > weightArr[data[2*pos+1]]) { //else swaps parent node with left child node
                int temp = data[pos];
                data[pos] = data[2*pos+1];
                data[2*pos+1] = temp;
                pos = 2*pos+1;
            }
            else {
                break; //if not swaps necessary than breaks while loop
            }
        }
    }
};

#endif