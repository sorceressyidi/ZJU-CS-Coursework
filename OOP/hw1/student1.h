#ifndef STUDENT_1
#define STUDENT_1
#include <iostream>
using namespace std;
const int num = 3;
class student{
    private:
        int score[num];
        string name;
    public:
        student(string Name,int *Score);
        double average();
        string getName();
        int getScore(int i);
};
#endif