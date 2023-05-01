#include "Trees.h"
// AVLTree Node empty constructor
Node::Node():left(nullptr),right(nullptr),Height(0){}
// AVLTree Node parameterize constructor
Node::Node(int id,string name,string department,float gpa){
    Id=id;
    Name=name;
    Gpa=gpa;
    Department=department;
    Height=0;
    left=right=nullptr;
}
//printing the Node
void Node::print() {
    cout<<"[ "<<Id<<" "<<Name<<" "<<Gpa<<" "<<Department<<" "<<Height<<" ]"<<endl;
}
//AVL Tree balance factor function
int AVLTree::Bfactor(Node *myNode){
    return ((myNode->left==nullptr?-1:myNode->left->Height)-(myNode->right==nullptr?-1:myNode->right->Height));
}
void AVLTree::updateHeight(Node *myNode){
    myNode->Height=max((myNode->left==nullptr?-1:myNode->left->Height),(myNode->right==nullptr?-1:myNode->right->Height))+1;
}
//rotating any Node to the left direction
Node* AVLTree::left_rotation(Node *myNode){
    Node *temp=myNode->right;
    myNode->right=temp->left;
    temp->left=myNode;
    updateHeight(myNode);
    updateHeight(temp);
    return temp;
}
//rotating any Node to the right direction
Node* AVLTree::right_rotation(Node *myNode){
    Node *temp=myNode->left;
    myNode->left=temp->right;
    temp->right=myNode;
    updateHeight(myNode);
    updateHeight(temp);
    return temp;
}
// to balance any Node if its balance factor violated the constraint
Node* AVLTree::balance(Node *myNode){
    //balance the Node if its left is greater than its right by 1
    if(Bfactor(myNode)==2){
        if(Bfactor(myNode->left)==-1){
            myNode->left=left_rotation(myNode->left);
        }
        myNode=right_rotation(myNode);
    }
    //balance the Node if its right is greater than its left by 1
    else if(Bfactor(myNode)==-2){
        if(Bfactor(myNode->right)==1){
            myNode->right=right_rotation(myNode->right);
        }
        myNode=left_rotation(myNode);
    }
    return myNode;
}
//to insert a Node in AVL tree
Node* AVLTree::Insert(Node *myNode,Node *AddNode){
    if(length==0){
        myNode=AddNode;
    }
    else{
        if(AddNode->Id<myNode->Id){
            if(myNode->left==nullptr){
                myNode->left=AddNode;
            }
            else{
                myNode->left=Insert(myNode->left,AddNode);
            }
        }
        else{
            if(myNode->right==nullptr){
                myNode->right=AddNode;
            }
            else{
                myNode->right=Insert(myNode->right,AddNode);
            }
        }
    }
    updateHeight(myNode);
    myNode=balance(myNode);
    return myNode;
}
void AVLTree::Insert(Node *AddNode){
    try{
        //to check that this Node doesn't repeat any id in the tree
        if(Search(root,AddNode->Id)){
            throw out_of_range("ID already exists");
        }
        root=Insert(root,AddNode);
        length++;
        cout<<"The student is added."<<endl;
    }
    catch(out_of_range &e){
        cout<<"Error "<<e.what()<<endl;
    }
}

// to find the Node with maximum Student id
Node* AVLTree::findMax(Node *myNode){
    if(myNode->right!= nullptr)return findMax(myNode->right);
    else return myNode;
}
int AVLTree::findMax(){
    try{
        if(length==0){
            throw out_of_range("ID already exists");
        }
        return findMax(root)->Id;
    }
    catch(out_of_range &e){
        cout<<"Error "<<e.what()<<endl;
    }
}
//to find the Node with minimum Student id
Node* AVLTree::findMin(Node *myNode){
    if(myNode->left!= nullptr)return findMin(myNode->left);
    else return myNode;
}
int AVLTree::findMin(){
    try{
        if(length==0){
            throw out_of_range("ID already exists");
        }
        return findMin(root)->Id;
    }
    catch(out_of_range &e){
        cout<<"Error "<<e.what()<<endl;
    }
}

//to delete a Node from AVLTree
Node* AVLTree::Delete(Node *myNode,int id){
    if(myNode->right==nullptr && myNode->left==nullptr){
        myNode=nullptr;
    }
    else if(id<myNode->Id){
        myNode->left=Delete(myNode->left,id);
    }
    else if(id>myNode->Id){
        myNode->right=Delete(myNode->right,id);
    }
    else{
        if(myNode->left==nullptr && myNode->right!=nullptr){
            myNode=myNode->right;
        }
        else{
            Node *MyMax=findMax(myNode->left);
            myNode->Id=MyMax->Id;
            myNode->Name=MyMax->Name;
            myNode->Gpa=MyMax->Gpa;
            myNode->Department=MyMax->Department;
            myNode->left=Delete(myNode->left,myNode->Id);
        }
    }
    if(myNode){
        updateHeight(myNode);
        myNode=balance(myNode);
    }
    return myNode;
}
bool AVLTree::Delete(int id){
    try{
        Node *DelNode=Search(root,id);
        if(length==0 || !(DelNode)){
            throw out_of_range("Student is not found.");
        }
        root=Delete(root,id);
        length--;
        cout<<"The student is deleted."<<endl;
    }
    catch(out_of_range &e){
        cout<<e.what()<<endl;
    }
}

Node* AVLTree::Search(Node *myNode,int id){
    if(myNode==nullptr) return nullptr;
    else if(id==myNode->Id) return myNode;
    else if(id<myNode->Id) return Search(myNode->left,id);
    else return Search(myNode->right,id);
}

//to Search about Node by id if exists
bool AVLTree::Search(int id){
    Node *result=Search(root,id);
    if(result){
        cout<<"Student is found."<<endl;
        result->print();
    }
    else cout<<"Student is not found."<<endl;
}

//to print a Node sorted by id
void AVLTree::TraversalinDepth(Node *myNode){
    if(myNode->left)TraversalinDepth(myNode->left);
    myNode->print();
    if(myNode->right)TraversalinDepth(myNode->right);
}
void AVLTree::TraversalinDepth(){
    if(length){
        TraversalinDepth(root);
    }
}
