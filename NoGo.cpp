#include "NoGo.h"
#include <cstdlib>
#include <ctime>

int nogo::data[9][9];
int nogo::data0[9][9];

void nogo::level1()
{
    returnok();

    srand((unsigned)time(NULL));
    int r, c;
    do
    {
        r = rand() % 9;
        c = rand() % 9;
    }while (nothere[r][c] || (begin && r == 4 && c == 4));

    x = r * 2 + 1;
    y = c * 2 + 1;
    print();

    begin = 0;
}

void nogo::level2()
{
    //数据初始化
    returnok();
    int maxs[9][9] = {{0}};
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            data[i][j] = -40;

    //返回data值
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (!nothere[i][j])
            {
                returndata(i, j);
                returnok();
            }

    //寻找最大data值
    int max = -40;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
                if (data[i][j] >= max)
                {
                    if (data[i][j] > max)
                        for (int m = 0; m < 9; m++)
                            for (int n = 0; n < 9; n++)
                                maxs[m][n] = 0;

                    maxs[i][j] = 1;
                    max = data[i][j];
                }

    int r, c;
    srand((unsigned)time(NULL));
    do
    {
        r = rand() % 9;
        c = rand() % 9;
    }while (nothere[r][c] || !maxs[r][c] || (begin && r == 4 && c == 4));

    x = r * 2 + 1;
    y = c * 2 + 1;
    print();

    begin = 0;
}

void nogo::level3()
{
    //数据初始化
    returnok();
    int maxs[9][9] = {{0}};
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            data[i][j] = -40;
            data0[i][j] = -200;
        }

    //返回data值
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (!nothere[i][j])
            {
                returndata0(i, j);
                returnok();
            }

    //寻找最大data0值
    int max = -200;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
                if (data0[i][j] >= max)
                {
                    if (data0[i][j] > max)
                        for (int m = 0; m < 9; m++)
                            for (int n = 0; n < 9; n++)
                                maxs[m][n] = 0;

                    maxs[i][j] = 1;
                    max = data0[i][j];
                }

    int r, c;
    srand((unsigned)time(NULL));
    do
    {
        r = rand() % 9;
        c = rand() % 9;
    }while (nothere[r][c] || !maxs[r][c] || (begin && r == 4 && c == 4));

    x = r * 2 + 1;
    y = c * 2 + 1;
    print();

    begin = 0;
}

void nogo::returndata(int a, int b)
{
    int win = 0, lose = 0;
    bool me[9][9];

    state[a][b] = player + 1;

    returnok();
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            me[i][j] = nothere[i][j];

    player = (player + 1) % 2;
    returnok();
    player = (player + 1) % 2;

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (!me[i][j] && nothere[i][j])
                win++;
            else if (me[i][j] && !nothere[i][j])
                lose++;

    state[a][b] = 0;

    data[a][b] = win - lose;
}

void nogo::returndata0(int a, int b)
{
    int win = 0, lose = 0, half = 0;
    bool me[9][9];

    state[a][b] = player + 1;

    returnok();
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            me[i][j] = nothere[i][j];

    player = (player + 1) % 2;
    returnok();
    player = (player + 1) % 2;

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (!me[i][j] && nothere[i][j])
                win++;
            else if (me[i][j] && !nothere[i][j])
                lose++;

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            returnok();
            if (!nothere[i][j])
            {
                returndata(i, j);
                if (data[i][j] > win - lose)
                    half++;
            }
        }

    state[a][b] = 0;

    data0[a][b] = win * 4 + half - lose * 2;
}
