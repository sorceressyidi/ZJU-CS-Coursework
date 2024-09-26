#include "castle.h"
castle::castle(int num, vector<string> names){
    //Initialize the castle
    this->num = num;
    princess = false;
    room temp;
    temp.name = "";
    temp.exit_num = 0;
    temp.loss = false;
    temp.princess = false;
    temp.up = false;
    temp.down = false;
    temp.east = false;
    temp.west = false;
    temp.up_to = 0;
    temp.down_to = 0;
    temp.east_to = 0;
    temp.west_to = 0;
    for(int i = 0; i < num; i++){
        rooms.push_back(temp);
    }
    for(int i = 0; i < names.size(); i++){
        this->names.push_back(names[i]);
    }
}
/*
set_room function is used to set the room information
Input: room_num,action,exit_num
Output: None
*/
void castle::set_room(int room_num,string action,int exit_num){
    rooms[room_num].exit_num++;
    if(action == "up"){
        rooms[room_num].up = true;
        rooms[room_num].up_to = exit_num;
    }
    if(action == "down"){
        rooms[room_num].down = true;
        rooms[room_num].down_to = exit_num;
    }
    if(action == "east"){
        rooms[room_num].east = true;
        rooms[room_num].east_to = exit_num;
    }
    if(action == "west"){
        rooms[room_num].west = true;
        rooms[room_num].west_to = exit_num;
    }
}
/*
move function is used to move the player to the next room
Input: room_num,action
Output: exit_num
*/
int castle:: move(int room_num, string action){
    vector<string> actions;
    if(rooms[room_num].up){
        actions.push_back("up");
    }
    if(rooms[room_num].down){
        actions.push_back("down");
    }
    if(rooms[room_num].east){
        actions.push_back("east");
    }
    if(rooms[room_num].west){
        actions.push_back("west");
    }
    vector<string>::iterator it;
    int exit_num = -1;
    for(it = actions.begin(); it < actions.end(); it++){
        if(*it == action){
            if(action == "up"){
                exit_num= rooms[room_num].up_to;
            }
            if(action == "down"){
                exit_num = rooms[room_num].down_to;
            }
            if(action == "east"){
                exit_num = rooms[room_num].east_to;
            }
            if(action == "west"){
                exit_num = rooms[room_num].west_to;
            }
            break;
        }
    }
    return exit_num;
}

/*
show_place function is used to show the information of the room
Input: room_num
Output: 0 if the game is not over, 1 if the player wins, -1 if the player loses
*/
int castle::show_place(int room_num){
    cout << "You are in the " << names[room_num]<<". ";
    if(rooms[room_num].loss){
        cout << "Oh no!You are eaten by the monster!" << endl;
        cout << "Game Over!" << endl;
        return -1;
    }
    //Win the game
    if(room_num == 0&&princess){
        cout << "Congratulations!You Win the game!" << endl;
        return 1;
    }
    //Find the princess
    if(rooms[room_num].princess){
        cout << "Congratulations!You found the princess" << endl;
        cout << "Princess:Oh,my hero!Please take me out of here!Remeber the only way out is the LOBBY!Be aware of the MONSTER!" << endl;
        cout << "You:Don't worry!Let's go!" << endl;
        cout << endl;
        princess = true;
    }
    vector<string> actions;
    if(rooms[room_num].up){
        actions.push_back("up");
    }
    if(rooms[room_num].down){
        actions.push_back("down");
    }
    if(rooms[room_num].east){
        actions.push_back("east");
    }
    if(rooms[room_num].west){
        actions.push_back("west");
    }
    //Show the exits
    cout << "There are " << rooms[room_num].exit_num << " exits: ";
    vector<string>::iterator it;
    for(it = actions.begin(); it < actions.end(); it++){
        cout << *it << " ";
    }
    cout << endl;
    cout << "Which way do you want to go?  ";
    return 0;
}
/*
set_monster function is used to set the monster in the room
Input: num
Output: None
*/
void castle::set_monster(int num){
    rooms[num].loss = true;
}
/*
set_princess function is used to set the princess in the room
Input: num
Output: None
*/
void castle::set_princess(int num){
    rooms[num].princess = true;
}