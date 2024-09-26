#ifndef STUDENT
#define STUDENT
#include <iostream>
using namespace std;
#include<vector>
class student{
    private:
        int num;
        string name;
        struct course{
            string id;
            int score;
        };
        vector<course> courses;
    public:
        student(string Name);
        void addCourse(string id, int score);
        double average();
        string getName();
        int getScore(int i);
        string getCourse(int i);
        int getNum();
};
#endif