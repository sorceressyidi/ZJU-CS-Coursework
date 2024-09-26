#ifndef ENTITY_HEADER
#define ENTITY_HEADER
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
class Entity {
private:
    vector<string> content;
    int year;
    int month;
    int day;
public:
    Entity(int _year = 0, int _month = 0, int _day = 0) : year(_year), month(_month), day(_day) { }
    void addContent(const string& line);
    void setDate(int _year, int _month, int _day);
    void showInfo() const;
    void showContent() const;
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    void saveContent(ofstream& file) const;
    void readContent(ifstream& file);
};
#endif
