#include "student.h"

// Constructor: Initialize student object with name and set initial values
student::student(string Name){
    name = Name;  // Initialize student name
    num = 0;      // Initialize number of courses to 0
}

// Function to add a course with its ID and score to the student's record
void student::addCourse(string id, int score) {
    course c;         // Create a course object
    c.id = id;        // Assign course ID
    c.score = score;  // Assign course score
    courses.push_back(c);  // Add the course to the vector of courses
    num++;            // Increment the number of courses
}

// Function to calculate and return the average score of the student
double student::average(){
    double sum = 0;  // Initialize sum of scores
    // Iterate through each course and sum up the scores
    for(int i = 0; i < num; i++){
        sum += courses[i].score;
    }
    // Calculate and return the average score
    return sum / num;
}

// Function to return the name of the student
string student::getName(){
    return name;  // Return student name
}

// Function to return the score of the course at index i
int student::getScore(int i){
    return courses[i].score;  // Return score of the course
}

// Function to return the ID of the course at index i
string student::getCourse(int i){
    return courses[i].id;  // Return ID of the course
}

// Function to return the total number of courses taken by the student
int student::getNum(){
    return num;  // Return number of courses
}
