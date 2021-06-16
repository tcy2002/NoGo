#ifndef NOGO_FRAME_H_INCLUDED
#define NOGO_FRAME_H_INCLUDED
#include <iostream>

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
    static int state[9][9];
    static bool nothere[9][9];
    static bool checked[9][9];

    void xy(int a, int b);
    void input();
    void initial();
    void gameframe();
    void button();
    bool display();

    void level();
    void borw();
    void restart();
    void open();
    void save();

    bool win();
    void choose();
    bool print();
    bool isNoqi(int a, int b);
    void returnok();
    bool renew();
};

#endif
