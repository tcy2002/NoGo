#include "NoGo_frame.h"
#include "NoGo.h"
#include <Windows.h>

int main()
{
    frame g;
    nogo n;
    system("mode con cols=47 lines=26");
    system("color f1");

    g.initial();
    g.gameframe();
    g.borw();
    g.level();
    g.gameframe();
    g.button();

    while (1)
    {
        if (g.win() && (g.stop = 1))
        {
            g.xy(1, 0);
            if (g.player)
                cout << "黑方获胜";
            else
                cout << "白方获胜";
        }
        else if (g.player != g.chosen && !g.stop)
        {
            if (g.gamelevel == 1)
                n.level1();
            else if (g.gamelevel == 2)
                n.level2();
            else if (g.gamelevel == 3)
                n.level3();
            else
                n.level4();
        }

        if (g.win() && (g.stop = 1))
        {
            g.xy(1, 0);
            if (g.player)
                cout << "黑方获胜";
            else
                cout << "白方获胜";
        }

        do {g.choose();} while (g.x <= 17 && g.nothere[(g.x - 1) / 2][(g.y - 1) / 2] && !g.stop && g.display());

        if (g.x <= 17)
            !g.stop && g.print() && (g.begin = 0);
        else if (g.y < 6)
            g.restart();
        else if (g.y < 10)
            g.open();
        else if (g.y < 14)
            g.save();
        else
        {
            g.xy(0, 20);
            system("pause");
            return 0;
        }
    }
}
