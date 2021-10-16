#ifndef NOGO_FRAME_H_INCLUDED
#define NOGO_FRAME_H_INCLUDED
#include <iostream>
//游戏基础控制

using namespace std;

class frame
{
public:
    static int x;
    static int y;
    static int gamelevel;
    static int player;
    static int chosen;
    static int begin;
    static int stop;
    static int *lastChosen;
    static int state[9][9];
    static bool nothere[9][9];
    static bool checked[9][9];

    //General_frame.cpp
    void xy(int a, int b);
    void input();
    bool error();
    void initial();
    void gameframe();
    void button();
    //Options_frame.cpp
    void restart();
    void open();
    void save();
    void borw();
    void level();
    //Game_frame.cpp
    bool win();
    int *choose(int lastChosen[2]);
    bool print();
    bool isNoqi(int a, int b);
    void returnok();
    bool renew();
    void exit();
    bool HumanAction();
};

#endif
