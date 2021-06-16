#include "NoGo.h"
#include <cstdlib>
#include <ctime>

double nogo::data1[9][9];
int nogo::wins[9][9];
int nogo::loses[9][9];
int nogo::row;
int nogo::column;

void nogo::level4()
{
    //数据初始化
    int maxs[9][9] = {{0}};
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            data[i][j] = -40;
            data1[i][j] = -200;
            wins[i][j] = loses[i][j] = 0;
        }

    //返回data值
    if (checkok() <= 8)
    {
        for (int i = 0; i < 9; i++)
            for ( int j = 0; j < 9; j++)
                if (!nothere[i][j])
                {
                    row = i;
                    column = j;
                    imitate(i, j);
                    data1[i][j] = 1.0 * wins[i][j] / (wins[i][j] + loses[i][j]);
                    returnok();
                }
    }
    else
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                if (!nothere[i][j])
                {
                    returndata1(i, j);
                    returnok();
                }

    //寻找最大data0值
    int max = -200;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (data1[i][j] >= max)
            {
                if (data1[i][j] > max)
                    for (int m = 0; m < 9; m++)
                        for (int n = 0; n < 9; n++)
                            maxs[m][n] = 0;

                maxs[i][j] = 1;
                max = data1[i][j];
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

int nogo::checkok()
{
    int sum = 0;
    returnok();
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (!nothere[i][j])
                sum++;

    return sum;
}

void nogo::imitate(int a, int b)
{
    state[a][b] = player + 1;
    player = (player + 1) % 2;

    if (win() && player == chosen)
        wins[row][column]++;
    else if (win() && player != chosen)
        loses[row][column]++;
    else if (!win())
    {
        returnok();
        for (int i = 0; i < 9; i++)
            for ( int j = 0; j < 9; j++)
                if (!nothere[i][j])
                    imitate(i, j);
    }

    player = (player + 1) % 2;
    state[a][b] = 0;
}

void nogo::returndata1(int a, int b)
{
    int win = 0, half = 0, lose = 0;
    int dewin = 0, dehalf = 0, delose = 0;
    bool me[9][9], deme[9][9];

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

    player = (player + 1) % 2;
    state[a][b] = player + 1;

    returnok();
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            deme[i][j] = nothere[i][j];

    player = (player + 1) % 2;
    returnok();
    player = (player + 1) % 2;

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (!deme[i][j] && nothere[i][j])
                dewin++;
            else if (deme[i][j] && !nothere[i][j])
                delose++;

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            returnok();
            if (!nothere[i][j])
            {
                returndata(i, j);
                if (data[i][j] > dewin - delose)
                    dehalf++;
            }
        }

    state[a][b] = 0;
    player = (player + 1) % 2;

    half == 1 && (half = -1);
    dehalf == 1 && (dehalf = -1);

    data1[a][b] = win * 8 - lose * 4 + half + dewin * 8 - delose * 4 + dehalf;
}
