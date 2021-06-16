#include "NoGo_frame.h"
#include <Windows.h>

int frame::x;
int frame::y;
int frame::gamelevel;
int frame::player;
int frame::chosen;
int frame::begin = 1;
int frame::stop = 0;
int frame::state[9][9] = {{0}};
bool frame::checked[9][9] = {{false}};
bool frame::nothere[9][9] = {{false}};

void frame::xy(int a, int b)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {a * 2, b};
    SetConsoleCursorPosition(hOut, pos);
}

void frame::input()
{
    while (!GetAsyncKeyState(VK_LBUTTON));

    POINT p;
    HWND h = GetForegroundWindow();
    GetCursorPos(&p);
    ScreenToClient(h, &p);
    x = p.x / 16, y = p.y / 16;

    Sleep(200);
}

void frame::initial()
{
    CONSOLE_CURSOR_INFO c = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    SetConsoleMode(hStdin, mode);
}

void frame::gameframe()
{
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++)
        {
            xy(i * 2 + 3, j * 2 + 3);
            cout << "┼";
        }

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 9; j++)
        {
            xy(i * 2 + 2, j * 2 + 1);
            cout << "─";
        }

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 8; j++)
        {
            xy(i * 2 + 1, j * 2 + 2);
            cout << "│";
        }

    for (int i = 0; i < 7; i++)
    {
        xy(i * 2 + 3, 1);
        cout << "┬";
        xy(1, i * 2 + 3);
        cout << "├";
        xy(17, i * 2 + 3);
        cout << "┤";
        xy(i * 2 + 3, 17);
        cout << "┴";
    }

    xy(1, 1);
    cout << "┌";
    xy(1, 17);
    cout << "└";
    xy(17, 1);
    cout << "┐";
    xy(17, 17);
    cout << "┘";

    xy(19, 1);
    cout << "不围棋";
    xy(2, 18);
    cout << "操作方法：鼠标左键单击    当前玩家：";

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            xy(i * 2 + 1, j * 2 + 1);
            if (state[i][j] == 1)
                cout << "●";
            else if (state[i][j] == 2)
                cout << "○";
        }
}

void frame::button()
{
    for (int i = 0; i < 8; i++)
    {
        xy(19, i * 2 + 3);
        cout << "═ ═ ═";
    }

    for (int i = 0; i < 4; i++)
    {
        xy(18, i * 4 + 4);
        cout << "║       ║";
    }

    for (int i = 0; i < 4; i++)
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
    cout << "新开始";
    xy(20, 6);
    cout << "  ";
    xy(19, 8);
    cout << "打  开";
    xy(20, 10);
    cout << "  ";
    xy(19, 12);
    cout << "保  存";
    xy(20, 14);
    cout << "  ";
    xy(19, 16);
    cout << "结  束";

    xy(20, 18);
    if (player == 0)
        cout << "●";
    else
        cout << "○";
}

bool frame::display()
{
    xy(1, 0);
    cout << "此处无法落子";
    Sleep(1000);
    cout << "\r              ";

    return true;
}
