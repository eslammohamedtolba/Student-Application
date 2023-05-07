#ifndef BST_H
#define BST_H

#include <iostream>

template <typename Object>
class BST {
private:
    class Node {
    public:
        Node(const Object& element, Node* left, Node* right)
            : element{ element }
            , left{ left }
            , right{ right }
        {
            
        }

        Object element;
        Node* left;
        Node* right;
    };
    
public:
    BST() : root{ nullptr } {
        // empty body
    }

    ~BST() {
        
    }

    void insert(const Object& element) {
        insert(element, root);
    }

    void print() {
        print(root);
        std::cout << "\n";
    }

    const Object* find(const Object& element) {
        return find(element, root);
    }

    void remove(const Object& element) {
        remove(element, root);
    }

private:
    Node* root;

    // internal functions
    Node* insert(const Object& element, Node* & r) {
        if (r == nullptr)
            r = new Node(element, nullptr, nullptr);
        else if (element < r->element)
            r->left = insert(element, r->left);
        else if (r->element < element)
            r->right = insert(element, r->right);
        else // already exists
            ;

        return r;
    }

    void print(Node* r) {
        if (r == nullptr)
            return;

        print(r->left);
        std::cout << r->element << " ";
        print(r->right);
    }

    const Object* find(const Object& element, Node* r) {
        if (r == nullptr)
            return nullptr;
        else if (element < r->element)
            return find(element, r->left);
        else if (r->element < element)
            return find(element, r->right);
        else
            return &(r->element);
    }

    void remove(const Object& element, Node* & r) {
        if (r == nullptr)
            return;
        else if (element < r->element)
            remove(element, r->left);
        else if (r->element < element)
            remove(element, r->right);
        else { // found

            // two children
            if (r->left != nullptr && r->right != nullptr) {
                // replace removed node with minimum node in the right subtree
                r->element = findMin(r->right)->element;

                // remove the minimum node from the right subtree
                remove(r->element, r->right);
            }
            // one child
            else {
                Node* old = r;

                // replace removed node with its child
                if (r->left != nullptr)
                    r = r->left;
                else
                    r = r->right;

                delete old;
            }
        }
            
    }

    Node* findMin(Node* r) {
        if (r != nullptr) {
            while (r->left != nullptr)
                r = r->left;
        }

        return r;
    }
};

#endif // BST_H