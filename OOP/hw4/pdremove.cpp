#include "entity.h"
#include "diary.h"
#include<sstream>
int main() {
    ifstream file("diary.txt");
    Diary diary;
    diary.Load("diary.txt");
    cout << "*************************************************\n";
    cout << "Welcome to show content of a diary. PLZ input date you want to remove:\n";
    cout << "There are a few rules to follow:\n";
    cout << "1. The date must be in the format: xxxx xx xx\n";
    cout << "2. To exit, enter -1\n";
    cout << "3. You should confirm the content you want to delete\n";
    cout << "*************************************************\n";
    int year,month,day;
    while(1){
        cout << "Enter the date (year month day): ";
        cin >> year;
        if (cin.eof()) {
                cout << "End of input detected.\n";
                return 0;
        }
        if (cin.fail()) {
            // Clear the input buffer and reset the input stream state
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please try again.\n";
            continue;
        }
        // Check if the user wants to quit
        if(year==-1){return 0;}
        cin >> month >> day;
        // Show the content of the diary
        if(diary.showEntity(year,month,day)){
            cout <<"Is it the content that you want to delete?(Y/N)";
            char choice;
            cin >> choice;
            // Check if the user wants to delete the content
            if(choice == 'Y'){
                diary.removeEntity(year,month,day);
                diary.rewrite("diary.txt");
            }
            continue;
        }
        cout << "Try agin please.";
    }
    return 0;
}