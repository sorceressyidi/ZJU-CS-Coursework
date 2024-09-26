#include"entity.h"
/*
 * set the date of the entity
 * @param _year the year of the entity
 * @param _month the month of the entity
 * @param _day the day of the entity
 * @return none
 */
void Entity::setDate(int _year, int _month, int _day)
{
    year = _year;
    month = _month;
    day = _day;
}
/*
 * add content to the entity
 * @param line the content to be added
 * @return none
 */
void Entity::addContent(const string& line)
{
    content.push_back(line);
}
/*
 * Show the date of the entity
 * @param none
 * @return none
 */
void Entity::showInfo() const
{
    cout << year << " " << month << " " << day;
}
/*
 * Show the content of the entity
 * @param none
 * @return none
 */
void Entity::showContent() const
{
    vector<string>::const_iterator it;
    for(it = content.begin(); it!= content.end(); it++){
        cout << *it << endl;
    }
    
}
/*
 * Get the year of the entity
 * @param none
 * @return the year of the entity
 */
int Entity::getYear() const{
    return year;
}
/*
 * Get the month of the entity
 * @param none
 * @return the month of the entity
 */
int Entity::getMonth() const{
    return month;
}
/*
 * Get the day of the entity
 * @param none
 * @return the day of the entity
 */
int Entity::getDay() const{
    return day;
}
/*
 * Save the content of the entity to a file
 * @param file the file to save the content
 * @return none
 */
void Entity::saveContent(ofstream& file) const
{
    file << year << " " << month << " " << day;
    vector<string>::const_iterator it;
    for(it = content.begin(); it != content.end(); it++)
    {
        file << *it << endl;
    }
    file << "." << endl;
}
/*
 * Read the content of the entity from a file
 * @param file the file to read the content
 * @return none
 */
void Entity::readContent(ifstream& file)
{
    string line;
    while(getline(file, line))
    {
        if (line == ".")
        {
            break;
        }
        content.push_back(line);
    }
}