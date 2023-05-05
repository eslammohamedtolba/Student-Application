#ifndef ASSIGNMENT3_TREES_H
#define ASSIGNMENT3_TREES_H
#include "bits/stdc++.h"
using namespace std;

class BSTree{};

//AVL Tree is a self-balancing binary search tree
//use rotations which are left and right rotation so
//the difference in height between the left and right subtrees of any node is always between 1 and -1
// so this remains the efficiency and then the Tree always becomes strictly balanced
class AVLTree {
private:
    struct AVLNode {
        int Id,Height;float Gpa;
        string Name,Department;
        AVLNode *left,*right;
        AVLNode();
        AVLNode(int id,string name,float gpa,string department);
        void print();
    };
    AVLNode* root;
    int length;
protected:
    int Bfactor(AVLNode *myNode);
    void updateHeight(AVLNode *myNode);
    AVLNode* left_rotation(AVLNode *myNode);
    AVLNode* right_rotation(AVLNode *myNode);
    AVLNode* balance(AVLNode *myNode);
    AVLNode* Insert(AVLNode *myNode,AVLNode *AddNode);
    AVLNode *findMax(AVLNode *myNode);
    AVLNode *findMin(AVLNode *myNode);
    AVLNode* Delete(AVLNode *myNode,int id);
    AVLNode* Search(AVLNode *myNode,int id);
    void TraversalinDepth(AVLNode *myNode);
public:
    AVLTree():root(nullptr),length(0){}
    void Insert(int id,string name,float gpa,string department);
    int findMax();
    int findMin();
    bool Delete(int id);
    bool Search(int id);
    void TraversalinDepth();
};

class MinHeapTree{};
class MaxHeapTree{};

#endif //ASSIGNMENT3_TREES_H
