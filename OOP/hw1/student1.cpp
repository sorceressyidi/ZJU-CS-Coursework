#include "student1.h"
student::student(string Name, int *Score){
    name = Name;
    for(int i = 0; i < num; i++){
        score[i] = Score[i];
    }
}
double student::average(){
    double sum = 0;
    for(int i = 0; i < num; i++){
        sum += score[i];
    }
    return sum / num;
}
string student::getName(){
    return name;
}
int student::getScore(int i){
    return score[i];
}