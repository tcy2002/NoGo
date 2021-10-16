#ifndef NOGO_H_INCLUDED
#define NOGO_H_INCLUDED
#include "NoGo_frame.h"
#define MAXBranchNum 81
//AI程序
//实现：NoGo.cpp

class nogo: public frame
{
    friend class frame;
public:
    static int data[9][9]; //第一层估值
    static int data0[9][9];//第二层估值
    static int wins[9][9]; //可落子点
    static int loses[9][9];//不可落子点
    static int row;
    static int column;

    void returndata(int a, int b);
    void returndata0(int a, int b);
    void level1();                                  //完全随机
    void level2();                                  //单层搜索（极大值）
    void level3();                                  //双层搜索（极大值极小值）
    void level4(int chosen, int *lastChosen);//蒙特卡洛
    void AIaction();
    void imitate(int a, int b);
    int checkok();
};

//以下为level4支撑代码
bool inBoard_judge(int x, int y);//判断是否在棋盘内
bool air_judge(int board[9][9], int x, int y);//判断是否有气
bool put_available(int board[9][9], int x, int y, int color);//判断能否下颜色为color的棋
int getValidPositions(int board[9][9], int result[9][9]);//找到能下的位置,result[9][9]表示各个位置的情况，0不能下，1可以下；该函数返回值是可下的位置数，也即result==1的点数

class nogoMCTS: public frame
{
public:
    nogoMCTS *parent;                 //父节点
    nogoMCTS *children[MAXBranchNum]; //子节点
    int board[9][9];
    int childrenAction[MAXBranchNum][2];
    int childrenCount;
    int childrenCountMax;
    double value;      //该节点的总value
    int n;             //当前节点探索次数，UCB中的ni
    double UCB;        //当前节点的UCB值
    int *countPointer; //总节点数的指针

    nogoMCTS(int parentBoard[9][9], int opp_action[2], nogoMCTS *parentPointer, int *countp); //构造函数 nogoMCTS *p是父类指针, int *countp应该是总探索次数的指针
    nogoMCTS *treeRules(); //搜索法则
    double simulation(); //模拟
    void backup(double deltaValue); //回传估值,从当前叶节点以及往上的每一个父节点都加上估值
    void evaluate(); //计算能下的位置,修改了childrenCountMax、childrenAction
};

#endif
