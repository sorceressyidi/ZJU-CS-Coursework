#include "entity.h"
#include "diary.h"
#include <sstream>

int main(int argc, char *argv[]) {
    ifstream file("diary.txt"); 
    Diary diary;
    diary.Load("diary.txt");
    // sort the diary
    diary.sortDiary();
    // argc is the number of arguments
    // argv is an array of arguments
    // argv[0] is the name of the program
    if (argc == 1) {
        diary.listEntities(); 
    } else {
        // if the user provides arguments
        if (argc < 6) {
            cout << "Usage: " << argv[0] << " startyear startmonth startday endyear endmonth endday" << std::endl;
            return 1;
        }
        int year1 = stoi(argv[1]);
        int month1 = stoi(argv[2]);
        int day1 = stoi(argv[3]);
        int year2 = stoi(argv[4]);
        int month2 = stoi(argv[5]);
        int day2 = stoi(argv[6]);
        cout << "List entities from " << year1 << "/" << month1 << "/" << day1 << " to " << year2 << "/" << month2 << "/" << day2 << endl;
        // list entities from year1/month1/day1 to year2/month2/day2
        diary.ListEntities(year1, month1, day1, year2, month2, day2);
    }
    
    return 0;
}
