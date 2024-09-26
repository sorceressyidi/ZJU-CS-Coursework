#include "entity.h"
#include "diary.h"

int main() {
    int year, month, day;
    vector<string> lines;
    Diary diary;
    cout << "*************************************************\n";
    cout << "Welcome to add content to a diary.\n";
    cout << "There are a few rules to follow:\n";
    cout << "1. The date must be in the format: xxxx xx xx\n";
    cout << "2. The content must end with a line '.'\n";
    cout << "3. To exit, enter 0 0 0\n";
    cout << "4. To end the program, press Ctrl-D\n(The already input diary will be saved to 'diary.txt')\n";
    cout << "5. The diary will be saved to 'diary.txt'\n";
    cout << "*************************************************\n";
    string line;
    
    while (1) {
        cout << "Enter the date (year month day): ";
        while (!(cin >> year >> month >> day) && !(cin.eof())) {
            cin.clear(); // 清除输入状态
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please try again.\n";
            cout << "Enter the date (year month day): ";
            cout << "Enter 0 0 0 to exit.\n";
        }
        //cin >> year >> month >> day;
        if (cin.eof()) {
                diary.Save("diary.txt");
                cout << "End of input detected.\n";
                return 0;
            }
        if (cin.fail()) {
            // clear the input buffer and reset the input stream state
            cin.clear();
            cout << "Invalid input. Please try again.\n";
            continue;
        }

        if (year == 0 && month == 0 && day == 0) {
            break;
        }

        // Read lines until encountering '.' or EOF
        while (getline(cin, line) && line != ".") {
            // Check for EOF (Ctrl-D)
            if (cin.eof()) {
                break;
            }
            lines.push_back(line);
        }
        Entity entity(year, month, day);
        for (const string& content : lines) {
            entity.addContent(content);
        }
        diary.addEntity(entity);
        cout << "Entity added successfully.\n";
        if (cin.eof()) {
            cout << "End of input detected.\n";
            break;
        }
        // Clear the lines vector for the next iteration
        lines.clear();
    }
    diary.Save("diary.txt");
    cout << "*********************************************************\n";
    cout << "End of input detected. The diary will be saved to 'diary.txt'.\n";
    cout << "Thank you for using the diary program.\n";
    cout << "Goodbye!\n";
    cout << "*********************************************************\n";
    return 0;
}
