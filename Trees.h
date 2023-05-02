#ifndef ASSIGNMENT3_TREES_H
#define ASSIGNMENT3_TREES_H
#include "bits/stdc++.h"
using namespace std;

//Node
struct Node {
    int Id;float Gpa;
    string Name,Department;
    Node *left,*right;
    Node();
    void print();
};
class BSTree{};

//AVL Tree is a Binary Tree
// consists of many nodes that connected by each other
// and the Balance factor of each Node is between 1 and -1
// so the Tree is strictly balanced
class AVLTree {
private:
    struct NodeAVL:public Node{
        int Height;
        NodeAVL *left,*right;
        NodeAVL(Node *myNode);
    };
    NodeAVL* root;
    int length;
protected:
    int Bfactor(NodeAVL *myNode);
    void updateHeight(NodeAVL *myNode);
    NodeAVL* left_rotation(NodeAVL *myNode);
    NodeAVL* right_rotation(NodeAVL *myNode);
    NodeAVL* balance(NodeAVL *myNode);
    NodeAVL* Insert(NodeAVL *myNode,NodeAVL *AddNode);
    NodeAVL *findMax(NodeAVL *myNode);
    NodeAVL *findMin(NodeAVL *myNode);
    NodeAVL* Delete(NodeAVL *myNode,int id);
    NodeAVL* Search(NodeAVL *myNode,int id);
    void TraversalinDepth(NodeAVL *myNode);
public:
    AVLTree():root(nullptr),length(0){}
    void Insert(Node *AddNode);
    int findMax();
    int findMin();
    bool Delete(int id);
    bool Search(int id);
    void TraversalinDepth();
};

class MinHeapTree{};
class MaxHeapTree{};

#endif //ASSIGNMENT3_TREES_H
