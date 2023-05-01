#include <iostream>
#include "Trees.h"
using namespace std;
int main() {
    int Nstudents;
    cout<<"please enter the number of students ->>>"<<endl;
    cin>>Nstudents;
    vector<Node*>Students(Nstudents);
    for(int i=0;i<Nstudents;i++){
        Students[i]=new Node();
        cin>>Students[i]->Id;cin.ignore();
        getline(cin,Students[i]->Name);
        cin>>Students[i]->Gpa>>Students[i]->Department;
    }
    AVLTree mytree;
    for(int i=0;i<Nstudents;i++){
        mytree.Insert(Students[i]);
    }
    //interface
}
