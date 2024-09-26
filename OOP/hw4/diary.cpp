#include "diary.h"
#include "entity.h"
#include <algorithm>
/*
 * Compare two entities
 * @param a the first entity
 * @param b the second entity
 * @return 1 if a is greater than b, 0 if a is equal to b, -1 if a is less than b
 */
int EntityCompare(const Entity& a, const Entity& b){
    if (a.getYear() < b.getYear()){return 1;}
    else if (a.getYear() == b.getYear()){
        if (a.getMonth() < b.getMonth()){return 1;}
        else if (a.getMonth() == b.getMonth()){
            if (a.getDay() < b.getDay()){return 1;}
            if (a.getDay() == b.getDay()){return 2;}
        }
    }
    return 0;
}
/*
 * Add an entity to the diary
 * @param entity the entity to be added
 * @return none
 */
void Diary::addEntity(const Entity& entity){
    diary.push_back(entity);
}
/*
 * List all entities in the diary
 * @param none
 * @return none
 */
void Diary::listEntities() const{
    vector<Entity>::const_iterator it;
    for(it = diary.begin(); it != diary.end(); it++)
    {
        it->showInfo();
        it->showContent();
        cout << endl;
    }
}
/*
 * Show the entity of a specific date
 * @param year the year of the entity
 * @param month the month of the entity
 * @param day the day of the entity
 * @return 1 if the entity is found, 0 if the entity is not found
 */
int Diary::showEntity(int year, int month, int day) const{
    vector<Entity>::const_iterator it;
    bool flag = false;
    for(it = diary.begin(); it != diary.end(); it++)
    {
        if (it->getYear() == year && it->getMonth() == month && it->getDay() == day)
        {
            it->showContent();
            flag = true;
        }
    }
    if(!flag){
        cout << "Date Not FOUND!";
        return 0;
    }
    return 1;
}
/*
 * Remove an entity from the diary
 * @param year the year of the entity
 * @param month the month of the entity
 * @param day the day of the entity
 * @return 1 if the entity is removed, 0 if the entity is not found
 */
int Diary::removeEntity(int year, int month, int day){
    vector<Entity>::iterator it;
    for(it = diary.begin(); it != diary.end(); it++)
    {
        if (it->getYear() == year && it->getMonth() == month && it->getDay() == day)
        {
            diary.erase(it);
            return 1;
        }
    }
    return 0;
}
/*
 * Save the diary to a file
 * @param name the name of the file
 * @return none
 */
void Diary::Save(string name)
{
    ofstream file(name,ios::app);
    vector<Entity>::const_iterator it;
    for(it = diary.begin(); it != diary.end(); it++)
    {
        it->saveContent(file);
    }
}
/*
 * Load the diary from a file
 * @param name the name of the file
 * @return none
 */
void Diary::Load(string name){
    ifstream file(name);
    int year, month, day;
    while(file >> year >> month >> day)
    {
        Entity entity(year, month, day);
        entity.readContent(file);
        diary.push_back(entity);
    }
}
/*
 * Sort the diary
 * @param none
 * @return none
 */
void Diary::sortDiary() {
    sort(diary.begin(), diary.end(), EntityCompare);
}
/*
 * Rewrite the diary to a file
 * @param name the name of the file
 * @return none
 */
void Diary::rewrite(string name)const{
    ofstream file(name);
    vector<Entity>::const_iterator it;
    for(it = diary.begin(); it != diary.end(); it++)
    {
        it->saveContent(file);
    }
}
/*
 * List entities from year1/month1/day1 to year2/month2/day2
 * @param year1 the year of the first date
 * @param month1 the month of the first date
 * @param day1 the day of the first date
 * @param year2 the year of the second date
 * @param month2 the month of the second date
 * @param day2 the day of the second date
 * @return none
 */
void Diary::ListEntities(int year1, int month1, int day1, int year2, int month2, int day2){
    vector<Entity>::const_iterator it;
    it = diary.begin();
    bool flag = false;
    Entity begin(year1, month1, day1);
    Entity end(year2, month2, day2);
    while(it != diary.end())
    {
        if(!EntityCompare(begin,*it)){it++;}
        else{flag = true;break;}
    }
    if(!flag){cout << "No Entries Found!" << endl; return;}

    while(it != diary.end())
    {
        if(EntityCompare(end,*it)==1){break;}
        it->showInfo();
        it->showContent();
        cout << endl;
        it++;
    }
}