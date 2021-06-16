#include "NoGo_frame.h"
#include <Windows.h>
#include <fstream>

void frame::level()
{
    for (int i = 4; i < 8; i++)
    {
        xy(19, i * 2 + 3);
        cout << "═ ═ ═";
    }

    for (int i = 2; i < 4; i++)
    {
        xy(18, i * 4 + 4);
        cout << "║       ║";
    }

    for (int i = 2; i < 4; i++)
    {
        xy(18, i * 4 + 3);
        cout << "╔";
        xy(22, i * 4 + 3);
        cout << "╗";
        xy(18, i * 4 + 5);
        cout << "╚";
        xy(22, i * 4 + 5);
        cout << "╝";
    }

    xy(19, 4);
    cout << "入  门";
    xy(19, 8);
    cout << "简  单";
    xy(20, 10);
    cout << "or";
    xy(19, 12);
    cout << "普  通";
    xy(20, 14);
    cout << "or";
    xy(19, 16);
    cout << "困  难";

    do {input();} while (x < 18 || x > 22 || y < 3 || y > 17 || y % 4 == 2);

    if (y < 6)
        gamelevel = 1;
    else if (y < 10)
        gamelevel = 2;
    else if (y < 14)
        gamelevel = 3;
    else
        gamelevel = 4;
}

void frame::borw()
{
    for (int i = 0; i < 4; i++)
    {
        xy(19, i * 2 + 3);
        cout << "═ ═ ═";
    }

    for (int i = 0; i < 2; i++)
    {
        xy(18, i * 4 + 4);
        cout << "║       ║";
    }

    for (int i = 0; i < 2; i++)
    {
        xy(18, i * 4 + 3);
        cout << "╔";
        xy(22, i * 4 + 3);
        cout << "╗";
        xy(18, i * 4 + 5);
        cout << "╚";
        xy(22, i * 4 + 5);
        cout << "╝";
    }

    xy(19, 4);
    cout << "黑  棋";
    xy(20, 6);
    cout << "or";
    xy(19, 8);
    cout << "白  棋";

    do {input();} while (x < 18 || x > 22 || y < 3 || y > 9 || y == 6);

    if (y < 6)
        chosen = 0;
    else
        chosen = 1;
}

void frame::restart()
{
    player = 0;
    begin = 1;
    stop = 0;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            state[i][j] = 0;

    system("cls");
    gameframe();
    borw();
    level();
    gameframe();
    button();
}

void frame::open()
{
    ifstream file;

    file.open("D:\\my_project\\Nogo1\\Nogo.txt");
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            file >> state[i][j];
    file >> player;
    file >> begin;
    file.close();

    system("cls");
    gameframe();
    button();

    stop = 0;
}

void frame::save()
{
    ofstream file;

    file.open("D:\\my_project\\Nogo1\\Nogo.txt");
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            file << state[i][j] << "\n";
    file << player << "\n";
    file << begin;
    file.close();

    xy(1, 0);
    cout << "当前棋局已保存";
    Sleep(1000);
    cout << "\r                ";
}
