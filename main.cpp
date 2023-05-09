#include <iostream>
#include <utility>
#include <vector>

using std::string;

template<typename T, typename Comparator = std::less<T>>
class Heap {
private:
    std::vector<T> v;
    Comparator cmp;
    // parent should give a Compartor True with children in order to be good Heap
public:
    Heap() {}

    int size(){
        return v.size();
    }

    int lchild(int idx) {
        return idx * 2 + 1;
    }

    int rchild(int idx) {
        return idx * 2 + 2;
    }

    int parent(int idx) {
        return (idx - 1) / 2;
    }

    void insert(T x) {
        v.push_back(x);
        int idx = v.size() - 1;
        while (idx && !cmp(v[parent(idx)], v[idx])) {
            std::swap(v[idx], v[parent(idx)]);
            idx = parent(idx);
        }
    }

    void pop() {
        if (!v.size())
            throw std::runtime_error("Pop from empty heap!\n");
        std::swap(v[0], v.back());
        v.pop_back();
        heapify(0);
    }

    T top(){
        if (!v.size())
            throw std::runtime_error("No top for Empty Heap!\n");
        return v[0];
    }

    void heapify(int idx) {
        if (idx >= v.size())
            return;
        int l = lchild(idx), r = rchild(idx), correct = idx;
        if (l < v.size() && !cmp(v[correct], v[l]))
            correct = l;
        if (r < v.size() && !cmp(v[correct], v[r]))
            correct = r;
        if (correct != idx) {
            std::swap(v[correct], v[idx]);
            heapify(correct);
        }
    }
};

struct Student{
    int id;
    double gpa;
    std::string fname, lname, dp;

    Student(int id, string f, string l, string dp, double gpa) :
    id(id), fname(std::move(f)), lname(std::move(l)), dp(std::move(dp)), gpa(gpa){

    }

    void print(){
        std::cout << "[" << id << ", " << fname << " "
        << lname << ", " << gpa << ", " << dp << "]" << std::endl;
    }
};

struct StudentGpaLess{
  bool operator()(Student& a, Student& b){
      return a.gpa < b.gpa;
  }
};

struct StudentGpaGreater{
    bool operator()(Student& a, Student& b){
        return a.gpa > b.gpa;
    }
};

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    std::cin >> n;
    Heap<Student, StudentGpaLess> minHeap;
    Heap<Student, StudentGpaGreater> maxHeap;

    for (int i = 0; i < n; ++i) {
        int id;
        double gpa;
        string fname, lname, dp;
        std::cin >> id >> fname >> lname >> gpa >> dp;
        Student newStudent(id, fname, lname, dp, gpa);
        maxHeap.insert(newStudent);
        minHeap.insert(newStudent);
    }

    std::cout << "Max Heap: " << std::endl;
    while(maxHeap.size()){
        maxHeap.top().print();
        maxHeap.pop();
    }

    std::cout << "\nMin Heap: " << std::endl;
    while(minHeap.size()){
        minHeap.top().print();
        minHeap.pop();
    }
}
