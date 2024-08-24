
#include<iostream>
#include<windows.h>
#include<time.h>
#include<conio.h>
#define H 22
#define W 22
using namespace std;

class chessboard
{
public:
    char qp[H][W];          //qb 地图，行动界面
    int i,j,x1,y1;          //x1,y1 食物坐标
    chessboard();
    void food();
    void prt(int grade,int score,int gamespeed);
 };


//初始化qp
chessboard::chessboard()
{
    for(i=1;i<=H-2;i++)
        for(j=1;j<=W-2;j++)
            qp[i][j]=' ';
    for(i=0;i<=H-1;i++)
        qp[0][i] = qp[H-1][i] = '#';
    for(i=1;i<=H-2;i++)
        qp[i][0] = qp[i][W-1] = '#';
    food();
}


//生成食物函数
void chessboard::food()
{
    srand(time(0));
    do
    {
        x1=rand()%W-2+1;
        y1=rand()%H-2+1;
    }
    while(qp[x1][y1]!=' ');
    qp[x1][y1]='$';
}


//画当前棋盘
void chessboard::prt(int grade,int score,int gamespeed)
{
    system("cls");
    cout << endl;
    for(i=0;i<H;i++)
    {
        cout << "\t";
        for(j=0;j<W;j++)
            cout<<qp[i][j]<<' ';
        if(i==0) cout << "\tGrade:" << grade;
        if(i==2) cout << "\tScore:" << score;
        if(i==4) cout << "\tAutomatic forward";
        if(i==5) cout << "\ttime interval:" << gamespeed << "ms";
        cout<<endl;
    }
}


class snake:public chessboard
{
public:
    int zb[2][100];
    long start;
    int head,tail,grade,score,gamespeed,length,timeover,x,y;    //长度length影响等级grade，grade影响速度gamespeed
    char direction;
    snake();
    void move();
 };
snake::snake()
{
    cout<<"\n\n\t\tThe game is about to begin!"<<endl;
    for(i=3;i>=0;i--)
    {
        start=clock();
        while(clock()-start<=1000);
        system("cls");
        if(i>0)
        cout << "\n\n\t\tCountdown:" << i << endl;
    }
    for(i=1;i<=3;i++)
        qp[1][i]='*';
    qp[1][4]='@';
    for(i=0; i<4; i++)
    {
        zb[0][i] = 1;
        zb[1][i] = i + 1;
    }
}
void snake::move()
{
    score=0;
    head = 3,tail = 0;
    grade = 1, length = 4;
    gamespeed = 500;
    direction = 77;
    while(1)
    {
        timeover = 1;
        start = clock();
        //不按按键时！kbhit是true
        //要while里面的条件是false才会退出这个while，按下按键就是false了
        //这里就是每过gamespeed时间和按下按键都会退出这个while
        while((timeover=(clock()-start<=gamespeed)) && !kbhit());
        //这里if如果是true，说明按下了按键
        if(timeover)
        {
            getch();
            direction = getch();
        }
        switch(direction)
        {
        case 72: x= zb[0][head]-1; y= zb[1][head];break;    //up
        case 80: x= zb[0][head]+1; y= zb[1][head];break;    //down
        case 75: x= zb[0][head]; y= zb[1][head]-1;break;    //left
        case 77: x= zb[0][head]; y= zb[1][head]+1;break;    //right
        }
        //碰到墙了
        if(x==0 || x==21 ||y==0 || y==21)
        {
            cout << "\tGame over!" << endl;break;
        }

        //碰的既不是空白也不是食物，就是碰到自身了
        if(qp[x][y]!=' '&&!(x==x1&&y==y1))
        {
            cout << "\tGame over!" << endl;break;
        }

        //碰到食物了
        if(x==x1 && y==y1)
        {
            length ++;
            score=score+100;
            if(length>=8)
            {
                length -= 8;
                grade ++;
                if(gamespeed>=200)
                    gamespeed = 550 - grade * 50;
            }
            qp[x][y]= '@';
            qp[zb[0][head]][zb[1][head]] = '*';
            head = (head+1)%100;
            zb[0][head] = x;
            zb[1][head] = y;
            food();
            prt(grade,score,gamespeed);
        }

        //没碰到食物，也要更新蛇的位置
        else
        {
            qp[zb[0][tail]][zb[1][tail]]=' ';
            tail=(tail+1)%100;
            qp[zb[0][head]][zb[1][head]]='*';
            head=(head+1)%100;
            zb[0][head]=x;
            zb[1][head]=y;
            qp[zb[0][head]][zb[1][head]]='@';
            prt(grade,score,gamespeed);
        }
    }
}
int main()
{
    chessboard cb;
    snake s;
    s.move();
}
