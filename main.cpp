#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // TODO:
    // 1. Create a MinHeap object.
    // 2. Push all leaf node indices into the heap.
    // 3. While the heap size is greater than 1:
    //    - Pop two smallest nodes
    //    - Create a new parent node with combined weight
    //    - Set left/right pointers
    //    - Push new parent index back into the heap
    // 4. Return the index of the last remaining node (root)
    MinHeap heap; //created MinHeap object
    for (int i = 0; i < nextFree; i++) {
        heap.push(i, weightArr); //pushes all leaf node indices to heap
    }
    while (heap.size > 1) { //while heap size greater than 1
        int small1 = heap.pop(weightArr); //pops smallest node
        int small2 = heap.pop(weightArr); //pops second smallest node
        weightArr[nextFree] = weightArr[small1] + weightArr[small2]; //combines smallest node weights into a parent node
        leftArr[nextFree] = small1; //assigns parent node left child to smallest node
        rightArr[nextFree] = small2; //assigns parent node right child to second smallest node
        heap.push(nextFree, weightArr); //pushes new parent index back into heap
        nextFree++; //increments nextFree to make space for creation of new parent nodes
    }
    return (heap.pop(weightArr)); //returns the index value stored in the root node of the heap
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.
    stack< pair<int, string> > stack; //created Stack object
    stack.push(pair<int, string>(root, "")); //pushes root pair to stack
    while (!stack.empty()) { //checks while stack still has nodes
        pair<int, string> rootNode = stack.top(); //assigns a pair to the root node of stack
        stack.pop(); //pops the root from stack

        int index = rootNode.first; //stores the index of the root node
        string code = rootNode.second; //initializes the code string associated with the node

        if (leftArr[index] == -1 && rightArr[index] == -1) { //checks to see if the node is a leaf node
            char c = charArr[index]; //if leaf node assigns corresponding char value to char variable
            codes[c - 'a'] = code; //stores corresponding code in the order that the char is found in the alphabet
        }
        else {
            if (rightArr[index] != -1) { //if the node is not a leaf node and has a right child
                stack.push(pair<int,string>(rightArr[index], code + "1")); //pushes right child to stack and adds 1 to code for right edge traversal
            }
            if (leftArr[index] != -1) {
                stack.push(pair<int,string>(leftArr[index], code + "0")); //pushes left child to stack and adds 0 to code for left edge traversal
            }
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}