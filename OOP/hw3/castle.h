#ifndef CASTLE_H
#define CASTLE_H
#include <iostream>
using namespace std;
#include <vector>
//Define the room structure
struct room{
    int exit_num;
    string name;
    bool up,down,east,west;
    bool princess;
    bool loss;
    int up_to;
    int down_to;
    int east_to;
    int west_to;
};
//Define the castle class
class castle{
    private:
        int num;
        bool princess;
        vector<room> rooms;
        vector<string> names;
    public:
        castle(int num, vector<string> names);
        void set_room(int room_num,string action,int exit_num);
        int move(int room_num, string action);
        int show_place(int room_num);
        void set_monster(int num);
        void set_princess(int num);
};
#endif