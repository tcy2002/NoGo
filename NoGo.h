#ifndef NOGO_H_INCLUDED
#define NOGO_H_INCLUDED
#include "NoGo_frame.h"

class nogo: public frame
{
public:
    static int data[9][9];
    static int data0[9][9];
    static double data1[9][9];
    static int wins[9][9];
    static int loses[9][9];
    static int row;
    static int column;

    void returndata(int a, int b);
    void returndata0(int a, int b);
    void returndata1(int a, int b);
    void level1();//完全随机
    void level2();//单层搜索
    void level3();//双层搜索
    void level4();//多层搜索+部分遍历
    void imitate(int a, int b);
    int checkok();
};

#endif
