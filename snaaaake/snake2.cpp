#include <iostream>
#include <windows.h>
#include <time.h>
#include <conio.h>
#define H 22
#define W 22
using namespace std;

char map[H][W];
int snake[200][2];
int head, tail;
int x, y;                           // 临时存储的横纵坐标
int fx, fy;                         // 食物的横纵坐标
int mx, my;                         // 地图上的横纵坐标
int direction = 77, interval = 500; // 初始向右，间隔500ms
int score = 0, grade = 1;
bool is_over;

void food();

void init()
{
    // 开始倒计时
    cout << "\n\n\t\t The game is about to start!" << endl;
    for (int i = 3; i >= 0; i--)
    {
        long start = clock();
        while (clock() - start <= 1000)
            ;
        system("cls");
        if (i != 0)
        {
            cout << "\n\n\t\t Countdown: " << i << endl;
        }
    }

    // 初始化地图
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (i == 0 || i == H - 1 || j == 0 || j == W - 1)
            {
                map[i][j] = '#';
            }
            else
            {
                map[i][j] = ' ';
            }
        }
    }

    // 初始化蛇蛇
    head = 3;
    tail = 0;
    for (int i = tail; i <= head; i++)
    {
        snake[i][0] = 1;
        snake[i][1] = i + 3;
        map[1][i + 3] = '*';
    }
    map[1][6] = '@';

    //  初始化食物
    food();
}

void food()
{
    srand(time(0));
    do
    {
        fx = rand() % W - 2 + 1;
        fy = rand() % H - 2 + 1;
    } while (map[fx][fy] != ' ');
    map[fx][fy] = '$';
}

void prt()
{
    system("cls");
    for (int i = 0; i < H; i++)
    {
        cout << "\t\t";
        for (int j = 0; j < W; j++)
        {
            cout << map[i][j] << " ";
        }
        if (i == 1)
        {
            cout << "\tGrade:" << grade;
        }
        if (i == 4)
        {
            cout << "\tScore:" << score;
        }
        if (i == 7)
        {
            cout << "\tInterval:" << interval;
        }
        cout << endl;
    }
}

bool move()
{
    x = snake[head][0];
    y = snake[head][1];
    switch (direction)
    {
    case 72:
        x--;
        break; // up
    case 80:
        x++;
        break; // down
    case 75:
        y--;
        break; // left
    case 77:
        y++;
        break; // right
    default:
        break;
    }

    // 原来的头变成身体
    mx = snake[head][0];
    my = snake[head][1];
    map[mx][my] = '*';

    // 新的头
    head = (head + 1) % 100;
    snake[head][0] = x;
    snake[head][1] = y;

    // 结束判定
    if (map[x][y] == '#' || map[x][y] == '*')
    {
        // 原来的尾部变成空白
        mx = snake[tail][0];
        my = snake[tail][1];
        map[mx][my] = ' ';
        tail = (tail + 1) % 100;
        return true;
    }
    map[x][y] = '@';

    // 没吃到东西
    if (x != fx || y != fy)
    {
        // 原来的尾部变成空白
        mx = snake[tail][0];
        my = snake[tail][1];
        map[mx][my] = ' ';
        tail = (tail + 1) % 100;
    }
    // 吃到东西了
    else
    {
        score += 100;
        if (score % 700 == 0)
        {
            grade++;
            if (interval >= 150)
            {
                interval -= 50;
            }
        }
        food();
    }
    return false;
}

// 每隔interval秒或者每次按下方向键就移动一次
void run()
{
    while (true)
    {
        long start = clock();
        int timeover;
        while (((timeover = clock() - start) <= interval) && !kbhit())
        {
        }

        // 没有按下按键，正常运行
        if (timeover >= interval)
        {
            is_over = move();
        }
        // 按下了按键，先获取方向再运行
        else
        {
            getch();
            int new_direction = getch();
            // 当新方向和原方向不相逆的时候，才会改为新方向
            if (direction + new_direction != 152)
                direction = new_direction;
            is_over = move();
        }
        prt();

        if (is_over)
        {
            cout << "\t\tGame over!" << endl;
            return;
        }
    }
}

int main()
{
    init();
    prt();
    run();
}
