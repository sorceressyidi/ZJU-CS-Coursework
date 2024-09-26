#include "entity.h"
#include "diary.h"
#include<sstream>
int main() {
    ifstream file("diary.txt");
    Diary diary;
    diary.Load("diary.txt");
    cout << "*************************************************\n";
    cout << "Welcome to show content of a diary.\n";
    cout << "There are a few rules to follow:\n";
    cout << "1. The date must be in the format: xxxx xx xx\n";
    cout << "2. To exit, enter -1\n";
    cout << "*************************************************\n";

    int year, month, day;
    while (1) {
        cout << "Enter the date (year month day): ";
        cin >> year;
        if (cin.eof()) {
                cout << "End of input detected.\n";
                return 0;
        }
        // check if the input is valid
        if (cin.fail()) {
            // clear the input buffer and reset the input stream state
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please try again.\n";
            continue;
        }
        // check if the user wants to quit
        if (year == -1) {
            return 0;
        }
        cin >> month >> day;
        // show the content of the diary
        if (diary.showEntity(year, month, day)) {
            continue;
        }
        cout << "Try again please."<<endl;
    }
    return 0;
}
