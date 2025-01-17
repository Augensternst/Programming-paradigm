
// ReSharper disable All
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

#define BOARD_SIZE 12
#define EMPTY 0
#define BLACK 1
#define WHITE 2

typedef int BOOL;
#define TRUE 1
#define FALSE 0

#define START "START"
#define PLACE "PLACE"
#define TURN "TURN"
#define END "END"
int enemy = -1; //敌方
int ai = -1; //AI
int current = -1;//当前
int new_aiX = -1; //AI当前最优下棋X
int new_aiY = -1; //AI当前最优下棋Y
int new_enemyX = -1; //敌方当前落子位置X
int new_enemyY = -1; //敌方当前落子位置Y
int board[BOARD_SIZE][BOARD_SIZE] = { 0 };//初始化棋盘
int myFlag;//我方颜色
int enemyFlag;//敌方颜色
#define RIGHT 0//方向：向右、向上、右上、左上
#define UP 1
#define UPRIGHT 2
#define UPLEFT 3
//各个棋型的代号 /权重 优化版（未完成）
#define OTHER 0//其他棋型
#define WIN 1//1000000,白赢
#define LOSE 2//-10000000
#define FLEX4 3//50000,白活4
#define flex4 4//-100000
#define BLOCK4 5//400
#define block4 6//-100000
#define FLEX3 7//400
#define flex3 8//-8000
#define BLOCK3 9//20
#define block3 10//-40
#define FLEX2 11//20
#define flex2 12//-40
#define BLOCK2 13//1
#define block2 14//-2
#define FLEX1 15//1
#define flex1 16//-2
//结构体表示点坐标
struct point
{
    int x;
    int y;
};
//敌方坐标表示
struct Condition
{
    int x;
    int y;
};
//指令输入棋盘坐标
struct Command
{
    int x;
    int y;
};
//debug输出
void debug(const char* str)
{
    printf("DEBUG %s\n", str);
    fflush(stdout);
}
//判断是否在棋盘内
BOOL isInBound(int x, int y)
{
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}
//放置棋子，更新棋盘（敌方）
void place(struct Command cmd)
{
    if (board[cmd.x][cmd.y] == EMPTY) {
        board[cmd.x][cmd.y] = enemyFlag;
    }
    else {
        debug("Position already occupied");
    }
}
//确认敌我方颜色
void initAI(int me)
{
    enemyFlag = 3 - me; // 初始化敌方标志位
}
//开始工作，清空棋盘，初始化ai
void start(int flag)
{
    memset(board, 0, sizeof(board)); // 清空棋盘
    int middlePlace = BOARD_SIZE / 2;
    // 初始化初始棋局
    board[middlePlace - 1][middlePlace - 1] = WHITE;
    board[middlePlace][middlePlace] = WHITE;
    board[middlePlace - 1][middlePlace] = BLACK;
    board[middlePlace][middlePlace - 1] = BLACK;
    initAI(flag); // 初始化AI
}
//声明
struct Condition AI_low(int color);
int exact_chess_point_score(int black, int white, int color);
//我方下棋轮
void turn()
{
    struct Condition result = AI_low(myFlag);
    if (board[result.x][result.y] == EMPTY) 
    {
        printf("%d %d\n", result.x, result.y);
        fflush(stdout);
        board[result.x][result.y] = myFlag;
    }
    else {
        debug("AI tried to place in an occupied position");
    }
}
//结束
void end(int x)
{
    exit(0);
}
//回合交替大循环
void loop()
{
    char tag[10] = { 0 };
    struct Command command =
    {
        .x = 0,
        .y = 0,
    };
    int status;
    while (TRUE)
    {
        memset(tag, 0, sizeof(tag));
        scanf("%s", tag);
        if (strcmp(tag, START) == 0)
        {
            scanf("%d", &myFlag); // 读取AI的标志位
            start(myFlag);
            printf("OK\n");
            fflush(stdout);
        }
        else if (strcmp(tag, PLACE) == 0)
        {
            scanf("%d %d", &command.x, &command.y); // 读取对手的落子位置
            place(command); // 在棋盘上放置对手的棋子
        }
        else if (strcmp(tag, TURN) == 0)
        {
            turn(); // AI下棋
        }
        else if (strcmp(tag, END) == 0)
        {
            scanf("%d", &status); // 读取比赛结果
            end(status); // 结束程序
        }
    }
}
struct EVALUATION {
    int score;
    int FEW[8];//储存部分棋形的个数,下标WIN=1为白连5,LOSE=2为黑连5,FLEX4=3为白活4,BLOCK4=5为白冲4,FLEX3=7为白活3
};
struct BEST {//最佳落子位置,[0]分数最高,[19]分数最低
    struct point pos[20];
    int score[20];//此处落子的局势分数
};
struct DECISION {
    struct point pos;//位置
    int eval;//对分数的评估
};
//AI大类
struct chess_ai {
    struct EVALUATION evaluation;
    struct BEST best;
    struct DECISION decision;
    int score[4][4][4][4][4][4];//评分数组,用来估计场上局势分数
};
//找点变为坐标，pos是方向，num是表示方向上几格
struct point find(int row, int col, int pos, int num)
{
    struct point aim;
    if (pos == RIGHT) {
        aim.x = row;
        aim.y = col + num;
    }
    else if (pos == UP) {
        aim.x = row - num;
        aim.y = col;
    }
    else if (pos == UPRIGHT) {
        aim.x = row - num;
        aim.y = col + num;
    }
    else if (pos == UPLEFT) {
        aim.x = row - num;
        aim.y = col - num;
    }
    return aim;
}
// 贪心算法部分
// 函数用于评估给定棋盘上特定点在四个方向上的五个连续位置的得分
int evaluate_point_score(int board[12][12], int x, int y, int color) {
    int sum = 0;
    for (int i = 0; i < 4; i++) {//四个方向
        for (int j = 0; j < 5; j++) {//每个方向上最多5个五元组
            struct point start = find(x, y, RIGHT + i, j - 4);//五元组顶点位置
            struct point  end = find(start.x, start.y, RIGHT + i, 4);//五元组最远位置
            if (isInBound(start.x, start.y) && isInBound(end.x, end.y)) {//若五元组下标均合法
                int blackChess = 0;
                int whiteChess = 0;
                for (int k = 0; k < 5; k++) {//对五元组5个位置考察
                    struct point tmp = find(start.x, start.y, RIGHT + i, k);
                    if (board[tmp.x][tmp.y] == BLACK)
                        blackChess++;
                    if (board[tmp.x][tmp.y] == WHITE)
                        whiteChess++;
                }
                sum += exact_chess_point_score(blackChess, whiteChess, color);
            }
        }
    }
    return sum;
}
//计算对应棋型的具体得分
int exact_chess_point_score(int black, int white, int color)
{
    //连5
    if (color == BLACK && black == 5)return 999999999;
    if (color == WHITE && white == 5)return 999999999;
    //全空
    if (black == 0 && white == 0)return 10;
    //形势无法判断，类似死棋
    else if (black >= 1 && white >= 1)return 0;
    //棋型判断
    else if (color == BLACK) {
        if (black == 1 && white == 0)return 40;
        else if (black == 2 && white == 0)return 800;
        else if (black == 3 && white == 0)return 15000;
        else if (black == 4 && white == 0)return 800000;
        else if (black == 0 && white == 1)return 15;
        else if (black == 0 && white == 2)return 400;
        else if (black == 0 && white == 3)return 7000;
        else if(black==0&&white==4)return 100000;
    }
    else if (color == WHITE){
        if (black == 1 && white == 0)return 15;
        else if (black == 2 && white == 0)return 400;
        else if (black == 3 && white == 0)return 7000;
        else if (black == 4 && white == 0)return 100000;
        else if (black == 0 && white == 1)return 40;
        else if (black == 0 && white == 2)return 800;
        else if (black == 0 && white == 3)return 15000;
        else if(black==0&&white==4)return 800000;
    }
}
//低端实现
struct Condition AI_low(int color)
{
    struct Condition p = { .x = -1, .y = -1 };  
    int bestScore = -1;  
    for (int i = 0; i < BOARD_SIZE; i++) 
    {
        for (int j = 0; j < BOARD_SIZE; j++) 
        {
            if (board[i][j] == EMPTY)
            {
                int score = evaluate_point_score(board, i, j, color);
                if (score > bestScore) 
                {
                    bestScore = score;
                    p.x = i;
                    p.y = j;
                }
            }
        }
    }

    if (p.x == -1 || p.y == -1) {
        debug("No valid move found");
    }

    return p;
}
//主函数
int main(int argc, char* argv[])
{
    loop();
    return 0;
}