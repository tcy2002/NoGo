#include "NoGo_frame.h"
#include "NoGo.h"
#include <Windows.h>

int main()
{
    frame g;
    nogo n;
    system("color f1");
    system("mode con cols=47 lines=20");

    g.initial();
    g.gameframe(); //初始化框架
    g.borw();      //选择先后手
    g.level();     //选择难度级别
    g.gameframe(); //刷新框架
    g.button();    //选项

    while (1)
    {
        g.exit();                        //玩家落子后判断是否终止
        n.AIaction();                    //AI落子
        g.exit();                        //AI落子后判断是否终止
        if (!g.HumanAction()) return(0);//玩家选点落子
    }
}
