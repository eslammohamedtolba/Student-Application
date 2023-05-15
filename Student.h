#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
using namespace std;

struct Student{
    int id;
    double gpa;
    std::string fname, lname, dp;

    Student(int id, string f, string l, string dp, double gpa)
        : id(id)
        , fname(std::move(f))
        , lname(std::move(l))
        , dp(std::move(dp))
        , gpa(gpa)
    {
        
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

struct StudentIdLess {
    bool operator()(const Student& a, const Student& b) {
        return a.id < b.id;
    }
};

ostream& operator<<(ostream& os, const Student& s) {
    cout << "[" << s.id << ", " << s.fname << " "
        << s.lname << ", " << s.gpa << ", " << s.dp << "]" << std::endl;

    return os;
}



#endif