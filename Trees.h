#ifndef ASSIGNMENT3_TREES_H
#define ASSIGNMENT3_TREES_H
#include "bits/stdc++.h"
using namespace std;

class BSTree{

};

//AVLTrees Node
struct Node {
    int Id,Height;
    string Name,Department;
    float Gpa;
    Node *left,*right;
    Node();
    Node(int id,string name,string department,float gpa);
    void print();
};
//AVL Tree is a Binary Tree
// consists of many nodes that connected by each other
// and the Balance factor of each Node is between 1 and -1
// so the Tree is strictly balanced
class AVLTree {
private:
    Node* root;
    int length;
    Node* Insert(Node *myNode,Node *AddNode);
    Node *findMax(Node *myNode);
    Node *findMin(Node *myNode);
    Node* Delete(Node *myNode,int id);
    Node* Search(Node *myNode,int id);
    void TraversalinDepth(Node *myNode);
public:
    AVLTree():root(nullptr),length(0){}
    int Bfactor(Node *myNode);
    void updateHeight(Node *myNode);
    Node* left_rotation(Node *myNode);
    Node* right_rotation(Node *myNode);
    Node* balance(Node *myNode);
    void Insert(Node *AddNode);
    int findMax();
    int findMin();
    bool Delete(int id);
    bool Search(int id);
    void TraversalinDepth();
};

class MinHeapTree{

};
class MaxHeapTree{

};

#endif //ASSIGNMENT3_TREES_H
