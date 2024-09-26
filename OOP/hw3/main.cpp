#include"castle.h"
#include<fstream>
#include<sstream>
#include<string>
int main(){
    int num;
    ifstream file ("test_data.txt");
    string line;
    getline(file,line);
    num = stoi(line);
    vector<string> names;
    //Initialize the castle
    for(int i = 0; i < num; i++){
        getline(file,line);
        names.push_back(line);
    }
    castle c(num,names);
    getline(file,line);
    int num_monster = stoi(line);
    c.set_monster(num_monster);
    getline(file,line);
    int num_princess = stoi(line);
    c.set_princess(num_princess);
    //Set the room
    while (getline(file, line)) {
        stringstream ss(line);
        int room_num;
        string action;
        int exit_num;
        ss >> room_num >> action >> exit_num;
        c.set_room(room_num,action,exit_num);
    }
    file.close();

    //Initialize the game
    int room_num = 0;
    string action;
    int exit_num;
    room_num = 0;
    int success = 0;
    //Start the game
    while(true){
        success = c.show_place(room_num);
        if(success != 0){
            break;
        }
        string go;
        cin >> go;
        cin >> action;
        while (action != "up" && action != "down" && action != "east" && action != "west" && go != "go"){
            printf("Invalid move,Try again:");
            cin >> go;
            cin >> action;
        }
        while(true){
            exit_num = c.move(room_num,action);
            if(exit_num != -1){
                break;
            }
            printf("Invalid move,Try again:");
            cin >> go;
            cin >> action;
        }
        room_num = exit_num;
    }
    return 0;
}