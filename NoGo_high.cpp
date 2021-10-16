#include <climits>
#include <cstring>
#include <ctime>
#include <iostream>
#include <math.h>
#include <random>
#include <string>
#include "NoGo.h"

void nogo::level4(int chosen, int *lastChosen)
{
    int count = 0; //总节点数
    int board[9][9] = {0};
    srand(clock());
    int start = clock();
    int timeout = CLOCKS_PER_SEC;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            if (!state[i][j])
                continue;
            if (chosen)
                board[i][j] = state[i][j] * 2 - 3;
            else
                board[i][j] = 3 - state[i][j] * 2;
        }

    nogoMCTS rootNode(board, lastChosen, nullptr, &count); //创建根节点，根节点的父节点为空

    while (clock() - start < timeout)
    {
        count++;                                 //计算的节点数++
        nogoMCTS *node = rootNode.treeRules();   //拓展一次，node指向的是一次拓展的叶节点
        double result = node->simulation();     //结果估值
        node->backup(result);

    }
    int bestChildren[MAXBranchNum] = {0}; //所有最优子节点的序号
    int bestChildrenNum = 0;              //最优子节点个数
    int maxValue = INT_MIN;               //当前最优子节点分数

    for (int i = 0; i < rootNode.childrenCount; ++i)
    {
        if (maxValue < rootNode.children[i]->value)
        {
            //重置
            memset(bestChildren, 0, sizeof(bestChildren));
            bestChildrenNum = 0;

            bestChildren[bestChildrenNum++] = i;
            maxValue = rootNode.children[i]->value;
        }
        else if (maxValue == rootNode.children[i]->value)
        {
            bestChildren[bestChildrenNum++] = i;
        }
    }

    int r = rand() % bestChildrenNum;                           //在所有最优中任选一个
    int *bestAction = rootNode.childrenAction[bestChildren[r]]; //最优子节点对应走法

    x = bestAction[0] * 2 + 1;
    y = bestAction[1] * 2 + 1;
    print();

    begin = 0;
}

int dx[4] = {-1, 0, 1, 0}; //行位移
int dy[4] = {0, -1, 0, 1}; //列位移
bool visited_by_air_judge[9][9] = {false}; //在air_judge函数判断某一点有无气时作标记，防止重复而死循环

bool inBoard_judge(int x, int y) { return 0 <= x && x < 9 && 0 <= y && y < 9; }

bool air_judge(int board[9][9], int x, int y)
{
    visited_by_air_judge[x][y] = true; //标记，表示这个位置已经搜过有无气了
    bool flag = false;
    for (int dir = 0; dir < 4; ++dir)
    {
        int x_dx = x + dx[dir], y_dy = y + dy[dir];
        if (inBoard_judge(x_dx, y_dy)) //界内
        {
            if (board[x_dx][y_dy] == 0) //旁边这个位置没有棋子
                flag = true;
            if (board[x_dx][y_dy] == board[x][y] && !visited_by_air_judge[x_dx][y_dy]) //旁边这个位置是没被搜索过的同色棋
                if (air_judge(board, x_dx, y_dy))
                    flag = true;
        }
    }
    return flag;
}

bool put_available(int board[9][9], int x, int y, int color)
{
    if (!inBoard_judge(x, y))
        return false;
    if (board[x][y]) //如果这个点本来就有棋子
        return false;

    board[x][y] = color;
    memset(visited_by_air_judge, 0, sizeof(visited_by_air_judge)); //重置

    if (!air_judge(board, x, y)) //如果下完这步这个点没气了,说明是自杀步，不能下
    {
        board[x][y] = 0;
        return false;
    }

    for (int i = 0; i < 4; ++i) //判断下完这步周围位置的棋子是否有气
    {
        int x_dx = x + dx[i], y_dy = y + dy[i];
        if (inBoard_judge(x_dx, y_dy)) //在棋盘内
        {
            if (board[x_dx][y_dy] && !visited_by_air_judge[x_dx][y_dy]) //对于有棋子的位置（标记访问过避免死循环）
                if (!air_judge(board, x_dx, y_dy))                      //如果导致(x_dx,y_dy)没气了，则不能下
                {
                    board[x][y] = 0; //回溯
                    return false;
                }
        }
    }
    board[x][y] = 0; //回溯
    return true;
}

int getValidPositions(int board[9][9], int result[9][9])
{
    memset(result, 0, MAXBranchNum * 4);
    int right = 0;
    for (int x = 0; x < 9; ++x)
    {
        for (int y = 0; y < 9; ++y)
        {
            if (put_available(board, x, y, 1))
            {
                right++;
                result[x][y] = 1;
            }
        }
    }
    return right;
}

nogoMCTS::nogoMCTS(int parentBoard[9][9], int opp_action[2], nogoMCTS *parentPointer, int *countp)
{
    for (int i = 0; i < 9; ++i) //把棋盘反过来，要落子方是1 ，对手是-1
    {
        for (int j = 0; j < 9; ++j)
        {
            board[i][j] = -parentBoard[i][j];
        }
    }

    if (opp_action[0] >= 0 && opp_action[0] < 9 && opp_action[1] >= 0 && opp_action[1] < 9)
        board[opp_action[0]][opp_action[1]] = -1;
    parent = parentPointer;
    value = 0;
    n = 0;
    childrenCount = 0;     //已经拓展的子节点数
    countPointer = countp; //count的指针
    evaluate();            //计算能下的位置,修改了childrenCountMax、childrenAction
}

typename nogoMCTS::nogoMCTS *nogoMCTS::treeRules()
{
    //如果没有位置下了（终局）
    if (childrenCountMax == 0)
    {
        return this; //到达终局当前叶节点
    }

    //如果是叶节点，Node Expansion，拓展下一层节点
    if (childrenCountMax > childrenCount)
    {
        nogoMCTS *newNode = new nogoMCTS(board, childrenAction[childrenCount], this, countPointer); //拓展一个子节点
        children[childrenCount] = newNode;
        childrenCount++; //已拓展的子节点数++
        return newNode;
    }

    //计算当前节点的每个子节点的UCB值（点亮某个节点）
    for (int i = 0; i < childrenCount; ++i)
    {
        children[i]->UCB = children[i]->value / double(children[i]->n) + 0.2 * sqrt(log(double(*countPointer)) / double(children[i]->n)); //UCB公式
    }
    int bestChild = 0;
    double maxUCB = 0;

    //找出所有子节点中UCB值最大的子节点
    for (int i = 0; i < childrenCount; ++i)
    {
        if (maxUCB < children[i]->UCB)
        {
            bestChild = i;
            maxUCB = children[i]->UCB;
        }
    }

    return children[bestChild]->treeRules(); //对UCB最大的子节点进行下一层搜索
}

double nogoMCTS::simulation()
{
    int board_opp[9][9]; //对手棋盘
    int res[9][9];
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            board_opp[i][j] = -board[i][j];
        }
    }
    int x = getValidPositions(board, res);     //落子方可下位置数
    int y = getValidPositions(board_opp, res); //非落子方可下位置数
    return x - y;
}

void nogoMCTS::backup(double deltaValue)
{
    nogoMCTS *node = this;
    int side = 0;
    while (node != nullptr) //当node不是根节点的父节点时
    {
        if (side == 1) //落子方
        {
            node->value += deltaValue;
            side--;
        }
        else //非落子方
        {
            node->value -= deltaValue;
            side++;
        }
        node->n++; //当前节点被探索次数++
        node = node->parent;
    }
}

void nogoMCTS::evaluate()
{
    int result[9][9];
    int validPositionCount = getValidPositions(board, result); //能下的位置数
    int validPositions[MAXBranchNum];                          //能下的位置坐标
    int availableNum = 0;
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            if (result[i][j])
            {
                validPositions[availableNum] = i * 9 + j; //可下的位置
                availableNum++;                           //可下的位置数
            }
        }
    }
    childrenCountMax = validPositionCount; //总共能下的位置数
    for (int i = 0; i < validPositionCount; ++i)
    {
        childrenAction[i][0] = validPositions[i] / 9;
        childrenAction[i][1] = validPositions[i] % 9;
    }
}
