#include "Trees.h"
//the Node empty constructor
Node::Node():left(nullptr),right(nullptr){}
//printing the Node
void Node::print() {
    cout<<"[ "<<Id<<" "<<Name<<" "<<Gpa<<" "<<Department<<" ]"<<endl;
}



//the AVLTree parameterize constructor
AVLTree::NodeAVL::NodeAVL(Node *myNode){
    this->Id=myNode->Id;
    this->Name=myNode->Name;
    this->Department=myNode->Department;
    this->Gpa=myNode->Gpa;
    left=right= nullptr;
    Height=0;
}

//AVL Tree balance factor function
int AVLTree::Bfactor(NodeAVL *myNode){
    return ((myNode->left==nullptr?-1:myNode->left->Height)-(myNode->right==nullptr?-1:myNode->right->Height));
}
//to update the Node Height
void AVLTree::updateHeight(NodeAVL *myNode){
    myNode->Height=max((myNode->left==nullptr?-1:myNode->left->Height),(myNode->right==nullptr?-1:myNode->right->Height))+1;
}

//rotating any Node to the left direction
AVLTree::NodeAVL* AVLTree::left_rotation(NodeAVL *myNode){
    NodeAVL *temp=myNode->right;
    myNode->right=temp->left;
    temp->left=myNode;
    updateHeight(myNode);
    updateHeight(temp);
    return temp;
}
//rotating any Node to the right direction
AVLTree::NodeAVL* AVLTree::right_rotation(NodeAVL *myNode){
    NodeAVL *temp=myNode->left;
    myNode->left=temp->right;
    temp->right=myNode;
    updateHeight(myNode);
    updateHeight(temp);
    return temp;
}
// to balance any Node if its balance factor violated the constraint
AVLTree::NodeAVL* AVLTree::balance(NodeAVL *myNode){
    //balance the Node if its left is greater than its right by 2
    if(Bfactor(myNode)==2){
        if(Bfactor(myNode->left)==-1){
            myNode->left=left_rotation(myNode->left);
        }
        myNode=right_rotation(myNode);
    }
    //balance the Node if its right is greater than its left by 2
    else if(Bfactor(myNode)==-2){
        if(Bfactor(myNode->right)==1){
            myNode->right=right_rotation(myNode->right);
        }
        myNode=left_rotation(myNode);
    }
    return myNode;
}

AVLTree::NodeAVL* AVLTree::Insert(NodeAVL *myNode,NodeAVL *AddNode){
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
//to insert a Node in AVL tree
void AVLTree::Insert(Node *AddNode){
    try{
        NodeAVL *AddNodeAVL =new NodeAVL(AddNode);
        //to check that this Node doesn't repeat any id in the tree
        if(Search(root,AddNode->Id)){
            throw out_of_range("ID already exists");
        }
        root=Insert(root,AddNodeAVL);
        length++;
        cout<<"The student is added."<<endl;
    }
    catch(out_of_range &e){
        cout<<"Error "<<e.what()<<endl;
    }
}

AVLTree::NodeAVL* AVLTree::findMax(NodeAVL *myNode){
    if(myNode->right!= nullptr)return findMax(myNode->right);
    else return myNode;
}
// to find the Node with maximum Student id
int AVLTree::findMax(){
    try{
        if(length==0){
            throw out_of_range("The Tree is empty!");
        }
        return findMax(root)->Id;
    }
    catch(out_of_range &e){
        cout<<"Error "<<e.what()<<endl;
    }
}

AVLTree::NodeAVL* AVLTree::findMin(NodeAVL *myNode){
    if(myNode->left!= nullptr)return findMin(myNode->left);
    else return myNode;
}
//to find the Node with minimum Student id
int AVLTree::findMin(){
    try{
        if(length==0){
            throw out_of_range("The Tree is empty!");
        }
        return findMin(root)->Id;
    }
    catch(out_of_range &e){
        cout<<"Error "<<e.what()<<endl;
    }
}

AVLTree::NodeAVL* AVLTree::Delete(NodeAVL *myNode,int id){
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
//to delete a Node from AVLTree
bool AVLTree::Delete(int id){
    try{
        bool isfound=Search(id);
        if(length==0){
            throw out_of_range("Student is not found.");
        }
        else if(isfound){
            root=Delete(root,id);
            length--;
            cout<<"The student is deleted."<<endl;
        }
    }
    catch(out_of_range &e){
        cout<<e.what()<<endl;
    }
}

AVLTree::NodeAVL* AVLTree::Search(NodeAVL *myNode,int id){
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
        return true;
    }
    else{
        cout<<"Student is not found."<<endl;
        return false;
    };
}

//to print a Node sorted by id
void AVLTree::TraversalinDepth(NodeAVL *myNode){
    if(myNode->left)TraversalinDepth(myNode->left);
    myNode->print();
    if(myNode->right)TraversalinDepth(myNode->right);
}
void AVLTree::TraversalinDepth(){
    if(length){
        TraversalinDepth(root);
    }
}
