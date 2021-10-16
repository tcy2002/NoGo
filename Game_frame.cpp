#include "NoGo_frame.h"
#include <Windows.h>

int *frame::choose(int lastChosen[2])
{
    bool flag;

    do
    {
        flag = false;
        input();

        if (x < 18 || x > 22 || y < 3 || y > 17 || y % 4 == 2)
            if (x > 17 || y > 17 || x % 2 == 0 || y % 2 == 0)
                flag = true;
        if (begin && !player && x == 9 && y == 9)
        {
            flag = true;
            xy(1, 0);
            cout << "黑方首次落子不可位于中心点！";
            Sleep(1000);
            cout << "\r                              ";
        }
    }while (flag);


    lastChosen[0] = (x - 1) / 2;
    lastChosen[1] = (y - 1) / 2;

    return lastChosen;
}

bool frame::print()
{
    if (state[(x - 1) / 2][(y - 1) / 2] == 0)
    {
        state[(x - 1) / 2][(y - 1) / 2] = player + 1;

        xy(x, y);
        if (!player)
            cout << "●";
        else
            cout << "○";

        player = (player + 1) % 2;

        xy(20, 18);
        if (!player)
            cout << "●";
        else
            cout << "○";
    }

    return true;
}

bool frame::HumanAction()
{
    do {lastChosen = choose(lastChosen);} while (x <= 17 && nothere[(x - 1) / 2][(y - 1) / 2] && !stop && error());

    if (x <= 17)
        !stop && print() && (begin = 0); //落子
    else if (y < 6)
        restart();                           //重新开始
    else if (y < 10)
        open();                              //读档
    else if (y < 14)
        save();                              //存档
    else
    {
        xy(0, 20);                           //结束
        system("pause");
        return false;
    }
    return true;
}

bool frame::isNoqi(int a, int b)
{
    checked[a][b] = true;
    bool check[5] = {true, true, true, true, true};

    if (a > 0)
    {
        if (!state[a - 1][b])
            return false;
        else if (!checked[a - 1][b] && state[a - 1][b] == state[a][b])
            check[1] = isNoqi(a - 1, b);
    }
    if (a < 8)
    {
        if (!state[a + 1][b])
            return false;
        else if (!checked[a + 1][b] && state[a + 1][b] == state[a][b])
            check[2] = isNoqi(a + 1, b);
    }
    if (b > 0)
    {
        if (!state[a][b - 1])
            return false;
        else if (!checked[a][b - 1] && state[a][b - 1] == state[a][b])
            check[3] = isNoqi(a, b - 1);
    }
    if (b < 8)
    {
        if (!state[a][b + 1])
            return false;
        else if (!checked[a][b + 1] && state[a][b + 1] == state[a][b])
            check[4] = isNoqi(a, b + 1);
    }

    for (int i = 1; i < 5; i++)
        if (!check[i])
            check[0] = false;

    return check[0];
}

bool frame::win()
{
    returnok();

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (!nothere[i][j])
                return false;

    return true;
}

void frame::returnok()
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            nothere[i][j] = false;

    for (int i = 0; i < 9; i++)
        for (int j = 0; j <9; j++)
            if (!state[i][j])
            {
                state[i][j] = player + 1;
                if ((renew() && isNoqi(i, j)) ||
                    (i > 0 && state[i - 1][j] && renew() && isNoqi(i - 1, j)) ||
                    (j > 0 && state[i][j - 1] && renew() && isNoqi(i, j - 1)) ||
                    (i < 8 && state[i + 1][j] && renew() && isNoqi(i + 1, j)) ||
                    (j < 8 && state[i][j + 1] && renew() && isNoqi(i, j + 1)))
                    nothere[i][j] = true;
                state[i][j] = 0;
            }
            else
                nothere[i][j] = true;
}

bool frame::renew()
{
    for (int m = 0; m < 9; m++)
        for (int n = 0; n < 9; n++)
            checked[m][n] = false;

    return true;
}

void frame::exit()
{
    if (win() && (stop = 1))
    {
        xy(1, 0);
        if (player)
            cout << "黑方获胜";
        else
            cout << "白方获胜";
    }
}
