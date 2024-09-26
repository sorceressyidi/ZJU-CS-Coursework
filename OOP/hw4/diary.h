#ifndef DIARY_HEADER
#define DIARY_HEADER
#include"entity.h"
class Diary{
private:
    vector<Entity> diary;
public:
    Diary(){}
    void addEntity(const Entity& entity);
    void listEntities() const;
    void ListEntities(int year1, int month1, int day1, int year2, int month2, int day2);
    int showEntity(int year, int month, int day) const;
    int removeEntity(int year, int month, int day);
    void Save(string name );
    void Load(string name);
    void sortDiary();
    void rewrite(string name)const;
};
#endif