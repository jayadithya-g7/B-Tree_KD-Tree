#include <iostream>
#include <vector>
#include <queue>
#include<chrono>
#include<stdio.h>
using namespace std;

struct Node {
    int *keys;
    Node **childPointers;
    int numKeys;
    bool leaf;
};

Node *createNode(int degree, bool leaf) {
    Node *node = new Node;
    node->numKeys = 0;
    node->leaf = leaf;
    node->keys = new int[2 * degree - 1];
    node->childPointers = new Node *[2 * degree];
    for (int i = 0; i < 2 * degree; i++) {
        node->childPointers[i] = NULL;
    }
    return node;
}

Node *search(Node *root, int key) {
    int i = 0;
    while (i < root->numKeys && key > root->keys[i]) {
        i++;
    }
    if (root->keys[i] == key) {
        return root;
    }
    if (root->leaf) {
        return NULL;
    }
    return search(root->childPointers[i], key);
}

void splitChild(Node *parent, int index, Node *child, int degree) {
    Node *newChild = createNode(degree, child->leaf);
    newChild->numKeys = degree - 1;

    for (int i = 0; i < degree - 1; i++) {
        newChild->keys[i] = child->keys[i + degree];
    }

    if (!child->leaf) {
        for (int i = 0; i < degree; i++) {
            newChild->childPointers[i] = child->childPointers[i + degree];
        }
    }

    child->numKeys = degree - 1;

    for (int i = parent->numKeys; i >= index + 1; i--) {
        parent->childPointers[i + 1] = parent->childPointers[i];
    }

    parent->childPointers[index + 1] = newChild;

    for (int i = parent->numKeys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }

    parent->keys[index] = child->keys[degree - 1];

    parent->numKeys++;
}

void insertNonFull(Node *node, int key, int degree) {
    int i = node->numKeys - 1;

    if (node->leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->numKeys++;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;

        if (node->childPointers[i]->numKeys == 2 * degree - 1) {
            splitChild(node, i, node->childPointers[i], degree);

            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->childPointers[i], key, degree);
    }
}

Node *insert(Node *root, int key, int degree){
    if (root == NULL) {
        root = createNode(degree, true);
        root->keys[0] = key;
        root->numKeys = 1;
        return root;
    }

    if (root->numKeys == 2 * degree - 1) {
        Node *newRoot = createNode(degree, false);
        newRoot->childPointers[0] = root;
        splitChild(newRoot, 0, root, degree);
        int i = 0;
        if (newRoot->keys[0] < key) {
            i++;
        }
        insertNonFull(newRoot->childPointers[i], key, degree);
        return newRoot;
    } else {
        insertNonFull(root, key, degree);
        return root;
    }
}

void traverse(Node *root) {
    if (root != NULL) {
        for (int i = 0; i < root->numKeys; i++) {
            traverse(root->childPointers[i]);
            cout << root->keys[i] << " ";
        }
        traverse(root->childPointers[root->numKeys]);
    }
}

void print2DUtil(Node *root, int space, int degree) {
    const int spacing = 10;
    if (root == NULL) return;

    space += spacing;

    for (int i = root->numKeys - 1; i >= 0; i--) {
        print2DUtil(root->childPointers[i + 1], space, degree);
        cout << endl;
        for (int j = spacing; j < space; j++) {
            cout << " ";
        }
        cout << root->keys[i] << endl;
    }

    print2DUtil(root->childPointers[0], space, degree);
}

void print2D(Node *root, int degree) {
    print2DUtil(root, 0, degree);
}

int main() {
    int degree;
    cout << "Enter the degree of the B-tree: ";
    cin >> degree;
    
    Node *root = NULL;
    
     while(1){
        cout << "1-INSERT\n2-SEARCH\n3-TRAVERSE\n4-PRINT 2D\n5-EXIT\n";
        cout << "Enter your choice: ";
        int ch;
        cin>>ch;

        if(ch==1){
            int key;
            cout << "Enter key to insert: ";
            cin >> key;
            auto start = std::chrono::high_resolution_clock::now();
            root = insert(root, key, degree);
            auto end = std::chrono::high_resolution_clock::now();
            double time_taken_insert = chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            time_taken_insert *= 1e-9; 
            printf("Time taken to insert node %d is %f nanoseconds\n ",key,time_taken_insert);
        }
        else if(ch==2){
            int key;
            cout << "Enter key to search: ";
            cin >> key;
            auto start = std::chrono::high_resolution_clock::now();
            if (search(root, key) != NULL) {
                    cout << "Key found\n";
            } 
            else {
                    cout << "Key not found\n";
            }
            auto end = std::chrono::high_resolution_clock::now();
            double time_taken_search = chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            time_taken_search *= 1e-9; 
            printf("Time taken to search node %d is %f nanoseconds\n ",key,time_taken_search);

        }
        else if(ch==3){
            cout << "B-tree traversal:\n";
            auto start = std::chrono::high_resolution_clock::now();
            traverse(root);
            auto end = std::chrono::high_resolution_clock::now();
            double time_taken_traverse= chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            time_taken_traverse *= 1e-9; 
            cout << endl;
            printf("Time taken for B-Tree traversal is %f nanoseconds\n ",time_taken_traverse);
            
        }
        else if(ch==4){
            cout << "B-tree in 2D format:\n";
            auto start = std::chrono::high_resolution_clock::now();
            print2D(root, degree);
            auto end = std::chrono::high_resolution_clock::now();
            double time_taken_print = chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            time_taken_print *= 1e-9; 
            cout << endl;
            printf("Time taken for 2D printing is %f nanoseconds\n ",time_taken_print);
        }
        else if(ch==5){
            break;
        }
     }
    return 0;
}
