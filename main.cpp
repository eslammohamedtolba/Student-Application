#include <iostream>
#include <iostream>
#include <string>
#include <fstream>
#include "min_max_heap.h"
#include "AVLTree.h"
#include "BST.h"
#include "Student.h"
using namespace std;

Heap<Student, StudentGpaLess> minHeap;
Heap<Student, StudentGpaGreater> maxHeap;
AVLTree avl;
BST<Student, StudentIdLess> bst;

enum class Tree {
    bst,
    minHeap,
    maxHeap,
    avl
};

void run();
void loadStudentData();
void bstMenu();
void avlMenu();
void minHeapMenu();
void maxHeapMenu();
void findStudent(Tree);
void addStudent(Tree);
void removeStudent(Tree);
void printHeap(Tree);


int main() {
    loadStudentData();
    run();
}

void run() {
    cout << R"(Choose Data Structure:
    1. BST
    2. AVL
    3. Min Heap
    4. Max Heap
    5. Exit Program
)";

    int choice;
    cin >> choice;

    bool running = true;
    while (running) {
        switch (choice)
        {
        case 1:
            bstMenu();
        case 2:
            avlMenu();
            break;
        case 3:
            minHeapMenu();
        case 4:
            maxHeapMenu();
            break;
        case 5:
            running = false;
            break;
        default:
            cout << "Invalid. Try again\n";
            break;
        }
    }
}

void bstMenu() {
    cout << R"(1. Add student
2. Remove student
3. Search student
4. Print All(sorted by id)
5. Return to main menu
)";

    int choice;

    while (true) {
        cout << "\nEnter number of option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent(Tree::bst);
            break;
        case 2:
            removeStudent(Tree::bst);
            break;
        case 3:
            findStudent(Tree::bst);
            break;
        case 4:
            bst.print();
            break;
        case 5:
            return;
        default:
            cout << "Invalid. Try again\n";
            break;
        }
    }
}

void avlMenu() {
    cout << R"(1. Add student
2. Remove student
3. Search student
4. Print All(sorted by id)
5. Return to main menu
)";

    int choice;

    while (true) {
        cout << "\nEnter number of option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent(Tree::avl);
            break;
        case 2:
            removeStudent(Tree::avl);
            break;
        case 3:
            findStudent(Tree::avl);
            break;
        case 4:
            avl.TraversalinDepth();
            break;
        case 5:
            return;
        default:
            cout << "Invalid. Try again\n";
            break;
        }
    }
}

void minHeapMenu() {
    cout << R"(1. Add student
2. Print All (sorted by gpa)
)";

    int choice;

    while (true) {
        cout << "Enter number of option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent(Tree::minHeap);
            break;
        case 2:
            printHeap(Tree::minHeap);
            break;
        default:
            cout << "Invalid. Try again\n";
            break;
        }
    }
}

void maxHeapMenu() {
    cout << R"(1. Add student
2. Print All (sorted by gpa)
)";

    int choice;

    while (true) {
        cout << "Enter number of option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent(Tree::maxHeap);
            break;
        case 2:
            printHeap(Tree::maxHeap);
            break;
        default:
            cout << "Invalid. Try again\n";
            break;
        }
    }
}

void removeStudent(Tree t) {
    int id;
    cout << "id: ";
    cin >> id;

    switch (t)
    {
    case Tree::bst:
        if (auto s = bst.find(Student{ id, "", "", "", 0 })) {
            cout << "Student is found.\n" << *s;
            bst.remove(*s);
            cout << "Student is deleted.";
        }
        break;
    case Tree::avl:
        avl.Delete(id);
        break;
    default:
        break;
    }
}

void findStudent(Tree t) {
    int id;
    cout << "id: ";
    cin >> id;

    Student s{ id, "", "", "", 0 };

    switch (t)
    {
    case Tree::bst:
        if (bst.find(s) != nullptr) {
            cout << "Student is found.\n";
            cout << *bst.find(s) << "\n";
        }
        else
            cout << "Student is not found.\n";
        break;

    case Tree::avl:
        avl.Search(id);
        break;
    default:
        break;
    }
}

void addStudent(Tree t) {
    int id;
    string fname, lname;
    double gpa;
    string department;

    cout << "id: ";
    cin >> id;
    cout << "name: ";
    cin >> fname >> lname;
    cout << "GPA: ";
    cin >> gpa;
    cout << "Department: ";
    cin >> department;

    Student s{ id, fname, lname, department, gpa };
    switch (t)
    {
    case Tree::bst:
        bst.insert(s);
        break;
    case Tree::avl:
        avl.Insert(s.id, s.fname + " " + s.lname, gpa, department);
        break;
    case Tree::minHeap:
        minHeap.insert(s);
        break;
    case Tree::maxHeap:
        maxHeap.insert(s);
        break;
    }

    cout << "\nThe student is added.\n";
}

void loadStudentData() {
    ifstream inputFile;

    inputFile.open("input.text");

    int n;
    inputFile >> n;

    for (int i = 0; i < n; ++i) {
        int id;
        double gpa;
        string fname, lname, dp;
        inputFile >> id >> fname >> lname >> gpa >> dp;
        Student newStudent(id, fname, lname, dp, gpa);
        
        maxHeap.insert(newStudent);

        minHeap.insert(newStudent);

        string name = fname + " " + lname;
        avl.Insert(id, name, gpa, dp);

        bst.insert(newStudent);
    }
}

void printHeap(Tree t) {
    if (t == Tree::minHeap) {
        auto temp = minHeap;
        while (temp.size()) {
            std::cout << temp.top();
            temp.pop();
        }
    }
    else if (t == Tree::maxHeap) {
        auto temp = maxHeap;
        while (temp.size()) {
            std::cout << temp.top();
            temp.pop();
        }
    }
}
