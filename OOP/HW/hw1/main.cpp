#include"student1.h"
#include<fstream>
#include<vector>
#include<sstream>
int main(){
    int count = 0;
    vector<student> students;
    ifstream file("student.txt");
    if (!file) {
        cout << "cannot open file" << endl;
        return 1;
    }
    string line;
    int cnt = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        int scores[num];
        ss >> name;
        for (int i = 0; i < num; i++) {
            ss >> scores[i];
        }
        student s(name, scores);
        students.push_back(s);
        count++;
    }
    file.close();
    cout << endl;
    cout << endl;
    cout << "no\t" << "name\t" << "score1\t" << "score2\t" << "score3\t" << "average\t" << endl;
    for(int i = 0; i < count; i++){
        cout << i + 1 << "\t" << students[i].getName() << "\t";
        for(int j = 0; j < num; j++){
            cout << students[i].getScore(j) << "\t";
        }
        cout << students[i].average() << endl;
    }
    //print average per course
    cout<<"\t"<<"average"<<"\t";
    for(int i=0;i<num;i++){
        double sum=0;
        for(int j=0;j<count;j++){
            sum+=students[j].getScore(i);
        }
        cout<<sum/count<<"\t";
    }
    // print min per course
    cout<<endl<<"\t"<<"min"<<"\t";
    for(int i=0;i<num;i++){
        int min=100;
        for(int j=0;j<count;j++){
            if(students[j].getScore(i)<min){
                min=students[j].getScore(i);
            }
        }
        cout << min << "\t";
    }
    // print max per course
    cout<<endl<<"\t"<<"max"<<"\t";
    for(int i=0;i<num;i++){
        int max=0;
        for(int j=0;j<count;j++){
            if(students[j].getScore(i)>max){
                max=students[j].getScore(i);
            }
        }
        cout << max << "\t";
    }
    return 0;

}