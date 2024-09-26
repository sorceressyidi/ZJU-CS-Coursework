#include"student.h"
//#include"student.cpp"
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;
int main() {
    string line;
    vector<student> students; // Vector to store student objects
    vector<string> titles;    // Vector to store column titles
    ifstream file("students.txt");  // Open the file named "students.txt" for reading
    titles.push_back("no");
    titles.push_back("name");
    if(file.is_open()) {
        while (getline(file, line)) {
            vector<string> tokens;
            string token;
             // Tokenize each line by space
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == ' ') {
                    tokens.push_back(token);
                    token = "";
                } else {
                    token += line[i];
                }
            }
            tokens.push_back(token);
            // Create a student object using the first token (name)
            student s(tokens[0]);
             // Add courses and scores to the student object
            for (int i = 1; i < tokens.size(); i += 2) {
                s.addCourse(tokens[i], stoi(tokens[i + 1]));
                // Add new titles if they don't exist in the titles vector
                for(int j = 0; j < titles.size(); j++){
                    if(titles[j] == tokens[i]){
                        break;
                    }
                    if(j == titles.size() - 1){
                        titles.push_back(tokens[i]);
                    }
                }
            }
            // Add the student object to the students vector
            students.push_back(s);
        }
        file.close(); // Close the file
    }
    titles.push_back("average");
    for(int i=0;i<titles.size();i++){
        cout<<titles[i]<<"\t";
    }
    cout<<endl;
    vector<student>::iterator p;
     // Print student data
    for(p=students.begin();p<students.end();p++){
        cout<<p-students.begin()+1<<"\t"<<p->getName()<<"\t";
        for(int i=0;i<titles.size()-3;i++){
            int flag = 0;
            for(int j=0;j<p->getNum();j++){
                if(p->getCourse(j)==titles[i+2]){
                    cout<<p->getScore(j)<<"\t";
                    flag = 1;
                    break;
                }
                
            }
            if(flag == 0){
                cout<<"None\t";
            }
        }
        cout<<p->average()<<endl;
    }

    // Calculate and print average, min, and max scores for each course
    vector<int> max;
    vector<int> min;
    vector<double> avg;
    for(int i=0;i<titles.size()-3;i++){
        double sum=0;
        int max1=0;
        int min1=100;
        // Calculate sum, min, and max scores for each course
        for(int j=0;j<students.size();j++){
            for(int k=0;k<students[j].getNum();k++){
                if(students[j].getCourse(k)==titles[i+2]){
                    sum+=students[j].getScore(k);
                    if(students[j].getScore(k)>max1){
                        max1=students[j].getScore(k);
                    }
                    if(students[j].getScore(k)<min1){
                        min1=students[j].getScore(k);
                    }
                }
            }
        }
         // Calculate and store average, min, and max scores
        avg.push_back(sum/students.size());
        max.push_back(max1);
        min.push_back(min1);
    }
    cout<<"\t"<<"average"<<"\t";
    for(int i=0;i<avg.size();i++){
        cout<<avg[i]<<"\t";
    }
    cout<<endl<<"\t"<<"min"<<"\t";
    for(int i=0;i<min.size();i++){
        cout<<min[i]<<"\t";
    }
    cout<<endl<<"\t"<<"max"<<"\t";
    for(int i=0;i<max.size();i++){
        cout<<max[i]<<"\t";
    }
    return 0;
}

