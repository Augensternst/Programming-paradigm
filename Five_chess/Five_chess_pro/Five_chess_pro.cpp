// ReSharper disable All
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <list>
#include <algorithm>
#include <vector>
using namespace std;
// 定义棋盘游戏的常量
#define BOARD_SIZE 12 // 定义棋盘大小为12x12
#define EMPTY 0       // 空格
#define BLACK 1       // 黑子
#define WHITE 2       // 白子
#define EDGE 3        // 边界标识
#define TRUE 1        // 真值
#define FALSE 0       // 假值
#define START "START" // 开始指令
#define PLACE "PLACE" // 放置棋子指令
#define TURN "TURN"   // 轮换指令
#define END "END"     // 结束指令
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
//声明部分
struct Condition AI_low(int color);
int exact_chess_point_score(int black, int white, int color);
void run();
//结构体表示点坐标
struct point
{
    int x;
    int y;
};
//结构体复制点
struct aid {
    int x;
    int y;
    aid(int x, int y) : x(x), y(y) {}
};
//坐标表示
struct Condition
{
    int x;
    int y;
};
//最终落子
struct Final
{
    int x;
    int y;
    int SCORE;
}final;
//====================================================================================
//棋盘初始化和运行维护
class init_chess_board
{
    friend class low_ai;
    friend class ai_pro;
private:
    //指令输入棋盘坐标
    struct Command
    {
        int x;
        int y;
    };
public:
    void debug(const char* str);//debug输出
    bool isInBound(int x, int y);//判断是否在棋盘内
    void place(struct Command cmd);//放置棋子，更新棋盘（敌方）
    void initAI(int me);//确认敌我方颜色
    void start(int flag);//开始工作，清空棋盘，初始化ai
    void turn();//我方下棋轮
    void end(int x);//结束
    void loop();//回合交替大循环
}Init;
void init_chess_board::debug(const char* str)
{
    printf("DEBUG %s\n", str);
    fflush(stdout);
}
bool init_chess_board::isInBound(int x, int y)
{
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}
void init_chess_board::place(struct Command cmd)
{
    if (board[cmd.x][cmd.y] == EMPTY) {
        board[cmd.x][cmd.y] = enemyFlag;
    }
    else {
        debug("Position already occupied");
    }
}
void init_chess_board::initAI(int me)
{
    enemyFlag = 3 - me; // 初始化敌方标志位
}
void init_chess_board::start(int flag)
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
void init_chess_board::turn()
{
    //struct Condition result = AI_low(myFlag);
    /*int n;
    for(int i=0;i<12;i++)
    {
	    for(int j=0;j<12;j++)
	    {
            cin >> n;
            board[i][j] = n;
	    }
    }*/
    run();
    struct Condition result;
    result.x = final.x;
    result.y = final.y;
        if (board[result.x][result.y] == EMPTY)
        {
            printf("%d %d\n", result.x, result.y);
            fflush(stdout);
            board[result.x][result.y] = myFlag;
            //打印棋盘，调试时候用
           /*for (int i = 0; i < 12; i++)
            {
                for (int j = 0; j < 12; j++)
                {
                    cout << board[i][j] << " ";
                }
                cout << endl;
            }*/
        }
        else {
            debug("AI tried to place in an occupied position");
        }
}
void init_chess_board::end(int x)
{
    exit(0);
}
void init_chess_board::loop()
{
    char tag[10] = { 0 };
    Command command;
    command.x = 0;
    command.y = 0;
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
//====================================================================================
//工具函数部分（基于低端实现的改进，用作高端的必备工具函数）
//实现算法基础和全局记分，后边要用到
class low_ai
{
    friend class init_chess_board;
    friend class ai_pro;
public:
    struct point find(int row, int col, int pos, int num);//找点变为坐标，pos是方向，num是表示方向上几格
    int evaluate_point_score(int board[12][12], int x, int y, int color);// 函数用于评估给定棋盘上特定点在四个方向上的五个连续位置的得分
    int exact_chess_point_score(int black, int white, int color);//计算对应棋型的具体得分
}Low;
// low_ai类的find方法：在棋盘上找到特定方向和距离的点
struct point low_ai::find(int row, int col, int pos, int num)
{
    struct point aim;
    if (pos == RIGHT) {
        aim.x = row;          // 向右移动，行不变
        aim.y = col + num;    // 列增加
    }
    else if (pos == UP) {
        aim.x = row - num;    // 向上移动，行减少
        aim.y = col;          // 列不变
    }
    else if (pos == UPRIGHT) {
        aim.x = row - num;    // 向右上移动，行减少
        aim.y = col + num;    // 列增加
    }
    else if (pos == UPLEFT) {
        aim.x = row - num;    // 向左上移动，行减少
        aim.y = col - num;    // 列减少
    }
    return aim;
}
// low_ai类的evaluate_point_score方法：评估棋盘上一个点的得分
int low_ai:: evaluate_point_score(int board[12][12], int x, int y, int color) {
    int sum = 0;
    for (int i = 0; i < 4; i++) {//四个方向
        for (int j = 0; j < 5; j++) {//每个方向上最多5个五元组
            struct point start = find(x, y, RIGHT + i, j - 4);//五元组顶点位置
            struct point  end = find(start.x, start.y, RIGHT + i, 4);//五元组最远位置
            // 确保五元组的起始和结束点都在棋盘内
            if (Init.isInBound(start.x, start.y) && Init.isInBound(end.x, end.y)) {//若五元组下标均合法
                int blackChess = 0;
                int whiteChess = 0;
                // 遍历五元组中的每个位置
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
// low_ai类的exact_chess_point_score方法：根据棋型计算具体得分
int low_ai::exact_chess_point_score(int black, int white, int color)
{
    //连5
    if (color == BLACK && black == 5)
        return 999999999;
    if (color == WHITE && white == 5)
        return 999999999;
    //全空
    if (black == 0 && white == 0)
        return 10;
    //形势无法判断，类似死棋
    else if (black >= 1 && white >= 1)
        return 0;
    //棋型判断
    else if (color == BLACK) {
        if (black == 1 && white == 0)
            return 40;
        else if (black == 2 && white == 0)
            return 800;
        else if (black == 3 && white == 0)
            return 15000;
        else if (black == 4 && white == 0)
            return 800000;
        else if (black == 0 && white == 1)
            return 15;
        else if (black == 0 && white == 2)
            return 400;
        else if (black == 0 && white == 3)
            return 7000;
        else if (black == 0 && white == 4)
            return 100000;
    }
    else if (color == WHITE) {
        if (black == 1 && white == 0)
            return 15;
        else if (black == 2 && white == 0)
            return 400;
        else if (black == 3 && white == 0)
            return 7000;
        else if (black == 4 && white == 0)
            return 100000;
        else if (black == 0 && white == 1)
            40;
        else if (black == 0 && white == 2)
            return 800;
        else if (black == 0 && white == 3)
            return 15000;
        else if (black == 0 && white == 4)
            return 800000;
    }
}
//====================================================================================
//最大最小值算法和剪枝算法实现（高端实现）
//定义棋型权重(针对白棋）
#define WIN 1
#define LOSE 2
#define DRAW  3
#define OTHER 0//其他棋型
#define W_LIVE_4 1//白活4
#define B_LIVE_4 2//黑活4
#define W_AIM_4 3//白冲4
#define B_AIM_4 4//黑冲4
#define W_LIVE_3 5//白活3
#define B_LIVE_3 6//黑活3
#define W_SLEEP_3 7//白眠3
#define B_SLEEP_3 8//黑眠3
#define W_LIVE_2 9//白活2
#define B_LIVE_2 10//黑活2
#define W_SLEEP_2 11//白眠2
#define B_SLEEP_2 12//黑眠2
#define W_LIVE 13//白活1
#define B_LIVE 14//黑活1
#define W_WIN 15//白赢
#define B_WIN 16//黑赢
class ai_pro
{
    friend class low_ai;
    friend class init_chess_board;
private:
    int chess_arr[4][4][4][4][4][4];//定义六元数组储存棋型
    int score;//分数
    int big[14][14];//大棋盘
    int result;
    int imp_type[17];
public:
    struct best_point
    {
	    struct a
	    {
            int x;
            int y;
            int Score;
	    }pos[20];
    };
    ai_pro();
    static bool compareBest(const best_point::a& a, const best_point::a& b) {
        return a.Score > b.Score;
    }
    void copy_board(int arr_1[12][12], int arr_2[12][12], int color);//复制带有棋盘边缘的大棋盘(或反转色）
    void init_complete_board(int arr[12][12]);//初始化带边缘大棋盘
    void init_chess_array_kind_1();//初始化非边缘棋型
    void init_chess_array_kind_2();//初始化边缘棋型
    void calculation_score(int arr[12][12],int color);//计算分数评估函数
	best_point find_best_point(int color,int arr[12][12]);//寻找点
    int mock(int depth, int alpha, int beta,int arr[12][12],int color);//模拟落子
    vector<aid>find_kill_chess(int arr[12][12],int color);//寻找算杀点
    bool whether_kill(int depth, int arr[12][12],int color);//实现算杀
}High;
ai_pro::ai_pro()
{
    score = 0;
}
//复制带有棋盘边缘的大棋盘(或反转色）
void ai_pro::copy_board(int arr_1[12][12], int arr_2[12][12], int color)
{
    for(int i=0;i<12;i++)
    {
	    for(int j=0;j<12;j++)
	    {
		    if(color==WHITE)
		    {
                arr_2[i][j] = arr_1[i][j];

		    }
            if(color==BLACK)
            {
                if (arr_1[i][j] == EMPTY)
                    arr_2[i][j] = EMPTY;
                else if (arr_1[i][j] == BLACK)
                    arr_2[i][j] = WHITE;
                else if (arr_1[i][j] == WHITE)
                    arr_2[i][j] = BLACK;
            }
	    }
    }
}
//初始化带边缘大棋盘
void ai_pro::init_complete_board(int arr[12][12])
{
    for (int i = 0; i < 14; ++i)
        big[i][0] = 3;
    for (int i = 0; i < 14; ++i)
        big[i][13] = 3;
    for (int j = 0; j < 14; ++j)
        big[0][j] = 3;
    for (int j = 0; j < 14; ++j)
        big[13][j] = 3;
    for (int i = 0; i < 12; ++i)
        for (int j = 0; j < 12; ++j)
            big[i + 1][j + 1] = arr[i][j];
}
//初始化非边缘棋型
void ai_pro::init_chess_array_kind_1()
{
    memset(chess_arr, 0, sizeof(chess_arr));
    //白活4
    chess_arr[0][2][2][2][2][0] = W_LIVE_4;
    //黑活4
    chess_arr[0][1][1][1][1][0] = B_LIVE_4;
    //白活3
    chess_arr[0][2][2][2][0][0] = W_LIVE_3;
    chess_arr[0][0][2][2][2][0] = W_LIVE_3;
    chess_arr[0][2][0][2][2][0] = W_LIVE_3;
    chess_arr[0][2][2][0][2][0] = W_LIVE_3;
    //黑活3
    chess_arr[0][1][1][1][0][0] = B_LIVE_3;
    chess_arr[0][0][1][1][1][0] = B_LIVE_3;
    chess_arr[0][1][0][1][1][0] = B_LIVE_3;
    chess_arr[0][1][1][0][1][0] = B_LIVE_3;
    //白活2
    chess_arr[0][2][2][0][0][0] = W_LIVE_2;
    chess_arr[0][2][0][2][0][0] = W_LIVE_2;
    chess_arr[0][2][0][0][2][0] = W_LIVE_2;
    chess_arr[0][0][2][2][0][0] = W_LIVE_2;
    chess_arr[0][0][2][0][2][0] = W_LIVE_2;
    chess_arr[0][0][0][2][2][0] = W_LIVE_2;
    //黑活2
    chess_arr[0][1][1][0][0][0] = B_LIVE_2;
    chess_arr[0][1][0][1][0][0] = B_LIVE_2;
    chess_arr[0][1][0][0][1][0] = B_LIVE_2;
    chess_arr[0][0][1][1][0][0] = B_LIVE_2;
    chess_arr[0][0][1][0][1][0] = B_LIVE_2;
    chess_arr[0][0][0][1][1][0] = B_LIVE_2;
    //白活1
    chess_arr[0][2][0][0][0][0] = W_LIVE;
    chess_arr[0][0][2][0][0][0] = W_LIVE;
    chess_arr[0][0][0][2][0][0] = W_LIVE;
    chess_arr[0][0][0][0][2][0] = W_LIVE;
    //黑活1
    chess_arr[0][1][0][0][0][0] = B_LIVE;
    chess_arr[0][0][1][0][0][0] = B_LIVE;
    chess_arr[0][0][0][1][0][0] = B_LIVE;
    chess_arr[0][0][0][0][1][0] = B_LIVE;
    //输赢
    chess_arr[2][2][2][2][2][2] = W_WIN;
    chess_arr[2][2][2][2][2][0] = W_WIN;
    chess_arr[0][2][2][2][2][2] = W_WIN;
    chess_arr[2][2][2][2][2][1] = W_WIN;
    chess_arr[1][2][2][2][2][2] = W_WIN;
    chess_arr[3][2][2][2][2][2] = W_WIN;
    chess_arr[2][2][2][2][2][3] = W_WIN;
    chess_arr[1][1][1][1][1][1] = B_WIN;
    chess_arr[1][1][1][1][1][0] = B_WIN;
    chess_arr[0][1][1][1][1][1] = B_WIN;
    chess_arr[1][1][1][1][1][2] = B_WIN;
    chess_arr[2][1][1][1][1][1] = B_WIN;
    chess_arr[3][1][1][1][1][1] = B_WIN;
    chess_arr[1][1][1][1][1][3] = B_WIN;
}
//初始化边缘棋型
void ai_pro::init_chess_array_kind_2()
{
    int left_white = 0;
    int right_white = 0;
    int left_black = 0;
    int right_black = 0;
    for(int a1=0;a1<4;a1++)
    {
        for (int a2 = 0; a2 < 3; a2++)
        {
            for (int a3 = 0; a3 < 3; a3++)
            {
                for (int a4 = 0; a4 < 3; a4++)
                {
                    for (int a5 = 0; a5 < 3; a5++)
                    {
                        for (int a6 = 0; a6 < 4; a6++)
                        {
                            if (chess_arr[a1][a2][a3][a4][a5][a6] != EMPTY)
                                continue;
                            left_black = left_white = right_black = right_white = 0;
                            if (a1 == 1)
                                left_black++;
                            else if (a1 == 2) 
                                left_white++;
                            if (a2 == 1) {
                                left_black++;
                                right_black++;
                            }
                            else if (a2 == 2) {
                                left_white++;
                                right_white++;
                            }
                            if (a3 == 1) {
                                left_black++;
                                right_black++;
                            }
                            else if (a3 == 2) {
                                left_white++;
                                right_white++;
                            }
                            if (a4 == 1) {
                                left_black++;
                                right_black++;
                            }
                            else if (a4 == 2) {
                                left_white++;
                                right_white++;
                            }
                            if (a5 == 1) {
                                left_black++;
                                right_black++;
                            }
                            else if (a5 == 2) {
                                left_white++;
                                right_white++;
                            }
                            if (a6 == 1) right_black++;
                            else if (a6 == 2) right_white++;
                            //for循环结束
                            //处理边缘情况
                            if(a1==EDGE||a6==EDGE)
                            {
	                            if(a1==EDGE&&a6!=EDGE)
	                            {
		                            if(right_black==4&&right_white==0)//黑冲4
		                            {
                                        chess_arr[a1][a2][a3][a4][a5][a6] = B_AIM_4;
		                            }
                                    if(right_black==3&&right_white==0)//黑眠3
                                    {
                                        chess_arr[a1][a2][a3][a4][a5][a6] = B_SLEEP_3;

                                    }
                                    if(right_black==2&&right_white==0)//黑眠2
                                    {
                                        chess_arr[a1][a2][a3][a4][a5][a6] = B_SLEEP_2;
                                    }
                                    if (right_black == 0 && right_white == 4)//白冲4
                                    {
                                        chess_arr[a1][a2][a3][a4][a5][a6] = W_AIM_4;
                                    }
                                    if (right_black == 0 && right_white == 3)//白眠3
                                    {
                                        chess_arr[a1][a2][a3][a4][a5][a6] = W_SLEEP_3;

                                    }
                                    if (right_black == 0 && right_white == 2)//白眠2
                                    {
                                        chess_arr[a1][a2][a3][a4][a5][a6] = W_SLEEP_2;
                                    }
	                            }
                                if(a1!=EDGE&&a6==EDGE)
                                {
                                    if (left_black == 4 && left_white == 0)//黑冲4
                                    {
                                        chess_arr[a1][a2][a3][a4][a5][a6] = B_AIM_4;
                                    }
                                    if (left_black == 3 && left_white == 0)//黑眠3
                                    {
                                        chess_arr[a1][a2][a3][a4][a5][a6] = B_SLEEP_3;

                                    }
                                    if (left_black == 2 && left_white == 0)//黑眠2
                                    {
                                        chess_arr[a1][a2][a3][a4][a5][a6] = B_SLEEP_2;
                                    }
                                    if (left_black == 0 && left_white == 4)//白冲4
                                    {
                                        chess_arr[a1][a2][a3][a4][a5][a6] = W_AIM_4;
                                    }
                                    if (left_black == 0 && left_white == 3)//白眠3
                                    {
                                        chess_arr[a1][a2][a3][a4][a5][a6] = W_SLEEP_3;

                                    }
                                    if (left_black == 0 && left_white == 2)//白眠2
                                    {
                                        chess_arr[a1][a2][a3][a4][a5][a6] = W_SLEEP_2;
                                    }
                                }
                            }
                            else
                            {
                                //白冲4
                                if ((right_black == 0 && right_white == 4) || (left_black == 0 && left_white == 4)) {
                                    
                                    chess_arr[a1][a2][a3][a4][a5][a6] = W_AIM_4;
                                }
                                //黑冲4
                                if ((right_black == 4 && right_white == 0) || (left_black == 4 && left_white == 0)) {
                                   
                                    chess_arr[a1][a2][a3][a4][a5][a6] = B_AIM_4;
                                }
                                //白眠3
                                if ((right_black == 0 && right_white == 3) || (left_black == 0 && left_white == 3)) {
                                    
                                    chess_arr[a1][a2][a3][a4][a5][a6] = W_SLEEP_3;
                                }
                                //黑眠3
                                if ((right_black == 3 && right_white == 0) || (left_black == 3 && left_white == 0)) {
                                   
                                    chess_arr[a1][a2][a3][a4][a5][a6] = B_SLEEP_3;
                                }
                                //白眠2
                                if ((right_black == 0 && right_white == 2) || (left_black == 0 && left_white == 2)) {
                                   
                                    chess_arr[a1][a2][a3][a4][a5][a6] = W_SLEEP_2;
                                }
                                //黑眠2
                                if ((right_black == 2 && right_white == 0) || (left_black == 2 && left_white == 0)) {
                                  
                                    chess_arr[a1][a2][a3][a4][a5][a6] = B_SLEEP_2;
                                }
                            }


                        }
                    }
                    
                }
            }
        }
    }
    

}
//计算分数评估函数
 void ai_pro::calculation_score(int arr[12][12],int color)
{
    int chess_type[17]; 
    if (color == WHITE)
    {
        int temp[] = { 0, 49999, -99999, 400, -99999, 400, -8000, 20, -50, 20, -50, 1, -3, 1, -3, 10000000, -10000000 };
        memcpy(chess_type, temp, sizeof(temp));
    }
    else if (color == BLACK)
    {
        int temp[] = { 0, -99999, 49999, -99999, 400, -8000, 400, -50, 20, -50, 20, -3, 1, -3, 1, -10000000, 10000000 };
        memcpy(chess_type, temp, sizeof(temp));
    }

   int sum_type[4][17] = {{0}};//四个方向上棋型数量
   int type_num = 0;
   init_complete_board(arr);
   //向四个方向搜索上述棋型信息

    for(int i=0;i<=12;i++)
    {
	    for(int j=0;j<9;j++)
	    {
            type_num=chess_arr[big[i][j]][big[i][j + 1]][big[i][j + 2]][big[i][j + 3]][big[i][j + 4]][big[i][j + 5]];
            sum_type[0][type_num]++;
	    }
    }
    for (int j = 0; j <= 12; j++)
    {
        for (int i = 0; i < 9; i++)
        {
            type_num = chess_arr[big[i][j]][big[i + 1][j]][big[i + 2][j]][big[i + 3][j]][big[i + 4][j]][big[i + 5][j]];
            sum_type[1][type_num]++;
        }
    }
    for (int i = 0; i < 9; ++i) 
    {
        for (int j = 0; j < 9; ++j) 
        {
            type_num = chess_arr[big[i][j]][big[i + 1][j + 1]][big[i + 2][j + 2]][big[i + 3][j + 3]][big[i + 4][j + 4]][big[i + 5][j + 5]];
            sum_type[2][type_num]++;
        }
        for (int k = 5; k < 14; ++k)
        {
            type_num = chess_arr[big[i][k]][big[i + 1][k - 1]][big[i + 2][k -2]][big[i + 3][k -3]][big[i + 4][k - 4]][big[i + 5][k - 5]];
            sum_type[3][type_num]++;
        }
    }
    score = 0;
    result = 0;
    imp_type[17] = { 0 };
    if(color==WHITE)
	{
		for(int pos=1;pos<17;pos++)
		{
			int sum = sum_type[0][pos] + sum_type[1][pos] + sum_type[2][pos] + sum_type[3][pos];
			score += sum * chess_type[pos];
            if (pos == W_WIN)
                imp_type[W_WIN] = sum;
            else if (pos == B_WIN)
                imp_type[B_WIN] = sum;
            else if (pos == W_LIVE_4)
                imp_type[W_LIVE_4] = sum;
            else if (pos == W_AIM_4)
                imp_type[W_AIM_4] = sum;
            else if (pos == W_LIVE_3)
                imp_type[W_LIVE_3] = sum;
            else if (pos == B_LIVE_3)
                imp_type[B_LIVE_3] = sum;
            else if (pos == B_AIM_4)
                imp_type[B_AIM_4] = sum;
		}
    	result = DRAW;
    	if(imp_type[W_WIN]>0)
    	{
    		result = WIN;
    	}
    	if(imp_type[B_WIN]>0)
    	{
    		result = LOSE;
    	}
	}
    else if(color==BLACK)
    {

        for (int pos = 1; pos < 17; pos++)
        {
            int sum = sum_type[0][pos] + sum_type[1][pos] + sum_type[2][pos] + sum_type[3][pos];
            score += sum * chess_type[pos];
            if (pos == W_WIN)
                imp_type[W_WIN] = sum;
            else if (pos == B_WIN)
                imp_type[B_WIN] = sum;
            else if (pos == B_LIVE_4)
                imp_type[B_LIVE_4] = sum;
            else if (pos == B_AIM_4)
                imp_type[B_AIM_4] = sum;
            else if (pos == B_LIVE_3)
                imp_type[B_LIVE_3] = sum;
            else if (pos == W_LIVE_3)
                imp_type[W_LIVE_3] = sum;
            else if (pos == W_AIM_4)
                imp_type[W_AIM_4] = sum;
        }
        result = DRAW;
        if (imp_type[B_WIN] > 0)
        {
            result = WIN;
        }
        if (imp_type[W_WIN] > 0)
        {
            result = LOSE;
        }
    }
    //记得处理score和result初始化问题
}
//寻找点
ai_pro::best_point ai_pro::find_best_point(int color,int arr[12][12])
{
    struct best_point best;
    int worth = -1;
    bool check[12][12]={false};
    int point_value[12][12];
    //从三个深度进行遍历
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            if (arr[i][j] != EMPTY) {
                // 标记当前位置
                check[i][j] = true;
                // 检查当前位置的左侧和右侧三个位置
                for (int k = -3; k <= 3; k++) {
                    if (i + k >= 0 && i + k < 12) {
                        // 标记左侧位置
                        check[i + k][j] = true;
                        
                        if (j + k >= 0 && j + k < 12) {
                            // 标记左上角和右上角位置
                            check[i + k][j + k] = true;
                            check[i + k][j - k] = true;
                        }
                    }
                    if(j+k>=0&&j+k<12)
                    {
                        check[i][j + k] = true;
                    }
                }
            }
        }
    }
    for(int i=0;i<12;i++)
    {
	    for(int j=0;j<12;j++)
	    {
            point_value[i][j] = -INT_MAX;
            if(arr[i][j]==EMPTY&&check[i][j]==true)
            {
                point_value[i][j] = Low.evaluate_point_score(arr, i, j, color);



            }
	    }
    }
    for (int k = 0; k < 20; k++)
    {
        worth = -INT_MAX;
        for (int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 12; j++)
            {
                if (point_value[i][j] > worth)
                {
                    worth = point_value[i][j];
                    best.pos[k].x = i;
                    best.pos[k].y = j;
                }
            }
        }
        //模拟落子
        if (color == WHITE)
        {
            arr[best.pos[k].x][best.pos[k].y] = WHITE;
        }
        else if(color==BLACK)
        {
            arr[best.pos[k].x][best.pos[k].y] = BLACK;
        }
        calculation_score(arr,color);
        best.pos[k].Score = score;
        arr[best.pos[k].x][best.pos[k].y] = EMPTY;
        point_value[best.pos[k].x][best.pos[k].y] = -INT_MAX;
    }
    sort(best.pos, best.pos + 20, compareBest);
    return best;
}
//模拟落子
int ai_pro::mock(int depth,int alpha,int beta, int arr[12][12],int color)
{
    calculation_score(arr,color);
    if(depth==4)
	{
		if(color==WHITE)
		{
			if(imp_type[B_LIVE_3]>0||imp_type[B_AIM_4]>0)
			{
				best_point defend = find_best_point(color, arr);
				final.x = defend.pos[0].x;
				final.y = defend.pos[0].y;
				return defend.pos[0].Score;
			}
		}
        else if(color==BLACK)
        {
	        if(imp_type[W_LIVE_3]>0||imp_type[W_AIM_4]>0)
	        {
                best_point defend = find_best_point(color, arr);
                final.x = defend.pos[0].x;
                final.y = defend.pos[0].y;
                return defend.pos[0].Score;
	        }
        }
	}
    if(depth==0||result!=DRAW)
    {
	    if(depth==0)
	    {
            best_point good;
            good = find_best_point(color, arr);
            return good.pos[0].Score;
	    }
	    else
	    {
            return score;
	    }
    }
    else if(depth%2==0)
    {
        best_point better = find_best_point(color, arr);
        for(int i=0;i<20;i++)
        {
            int mock_board[12][12];
            copy_board(arr, mock_board, WHITE);
            mock_board[better.pos[i].x][better.pos[i].y] = color;
            int mock_score = mock(depth - 1, alpha, beta, mock_board, color);
            if(mock_score>alpha)
            {
                alpha = mock_score;
                if(depth==4)
                {
                    final.x = better.pos[i].x;
                    final.y = better.pos[i].y;
                    final.SCORE = mock_score;
                }
            }
            if(beta<=alpha)
            {
                break;
            }
        }
        return alpha;
    }
    else
    {
        int oppo_mock_board[12][12];
        copy_board(arr, oppo_mock_board, BLACK);
        best_point oppo_best = find_best_point(color, oppo_mock_board);
      for(int i=0;i<20;i++)
      {
          int mock_board[12][12];
          copy_board(arr, mock_board, WHITE);
        if(color==WHITE)
        {
	        mock_board[oppo_best.pos[i].x][oppo_best.pos[i].y] = BLACK;
        }
        else if(color==BLACK)
        {
	        mock_board[oppo_best.pos[i].x][oppo_best.pos[i].y] = WHITE;
        }
      	int mock_score = mock(depth - 1, alpha, beta, mock_board, color);
        if(mock_score<beta)
        {
            beta = mock_score;
        }
        if (beta<=alpha)
        {
            break;
        }
      }
      return beta;
    }
}
//寻找算杀点
vector<aid>ai_pro::find_kill_chess(int arr[12][12],int color)
{
    vector<aid>kill_chess;
    best_point kill = find_best_point(color, arr);
    int mock_board[12][12];
    copy_board(arr, mock_board, WHITE);
    for(int i=0;i<20;i++)
    {
        mock_board[kill.pos[i].x][kill.pos[i].y] = color;
        calculation_score(arr,color);
        if(color==WHITE)
        {
	        if(imp_type[W_WIN]>0)
	        {
	        	kill_chess.push_back(aid(kill.pos[i].x,kill.pos[i].y));
	        }
	        else if(imp_type[W_LIVE_4]>0)
	        {
	        	kill_chess.push_back(aid(kill.pos[i].x, kill.pos[i].y));
	        }
	        else if(imp_type[W_LIVE_3] > 0)
	        {
	        	kill_chess.push_back(aid(kill.pos[i].x, kill.pos[i].y));
	        }
	        else if(imp_type[W_AIM_4]>0)
	        {
	        	kill_chess.push_back(aid(kill.pos[i].x, kill.pos[i].y));
	        }
        }
        else if(color==BLACK)
        {
            if (imp_type[B_WIN] > 0)
            {
                kill_chess.push_back(aid(kill.pos[i].x, kill.pos[i].y));
            }
            else if (imp_type[B_LIVE_4] > 0)
            {
                kill_chess.push_back(aid(kill.pos[i].x, kill.pos[i].y));
            }
            else if (imp_type[B_LIVE_3] > 0)
            {
                kill_chess.push_back(aid(kill.pos[i].x, kill.pos[i].y));
            }
            else if (imp_type[B_AIM_4] > 0)
            {
                kill_chess.push_back(aid(kill.pos[i].x, kill.pos[i].y));
            }
        }
        mock_board[kill.pos[i].x][kill.pos[i].y] = EMPTY;
    }
    return kill_chess;
}
//实现算杀
bool ai_pro::whether_kill(int depth, int arr[12][12],int color)
{
    calculation_score(arr,color);
    int result_1 = result;
    if(depth==0||result_1!=DRAW)
    {
	    if(depth==0)
	    {
            best_point aim = find_best_point(color, arr);
            arr[aim.pos[0].x][aim.pos[0].y] = color;
            calculation_score(arr,color);
            if(result==WIN)
            {
                return true;
            }
            else
            {
                return false;
            }
	    }
        else if(result_1==WIN)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if(depth%2==0)
    {
	    if(depth==16||depth==14)
	    {
            best_point aim = find_best_point(color, arr);
            for(int i=0;i<10;i++)
            {
                int mock_board[12][12];
                copy_board(arr, mock_board,WHITE);
                mock_board[aim.pos[i].x][aim.pos[i].y] = color;
                if(whether_kill(depth-1,mock_board,color))
                {
                        final.x = aim.pos[i].x;
                        final.y = aim.pos[i].y;
	                     return true;
                }
            }
            return false;
	    }
	    else
	    {
            vector<aid>kill = find_kill_chess(arr,color);
            if (kill.empty())
            {
                return false;
            }
            for (auto it = kill.begin(); it != kill.end(); ++it)
            {
                int mock_board[12][12];
                copy_board(arr, mock_board, color);
                mock_board[it->x][it->y] = color;
                if(whether_kill(depth-1,arr,color))
                {
                    if(depth==16)
	                {
		                final.x = it->x;
	                	final.y = it->y;
	                }
                    return true;
                }
            }
            return false;
	    }
    }
    else
    {
            int oppo_board[12][12];
	        copy_board(arr, oppo_board, BLACK);
        	best_point oppo_best = find_best_point(color, oppo_board);
        	int mock_board[12][12];
        	copy_board(arr, mock_board, WHITE);
            if (color == WHITE) {
                mock_board[oppo_best.pos[0].x][oppo_best.pos[0].y] = BLACK;
            }
            else if(color==BLACK)
            {
                mock_board[oppo_best.pos[0].x][oppo_best.pos[0].y] = WHITE;
            }
        	return whether_kill(depth - 1, mock_board, color);
    }
}
//第二部分实现
void run()
{
    High.init_chess_array_kind_1();
    High.init_chess_array_kind_2();
	if(!High.whether_kill(16,board,myFlag))
	{
		int score = High.mock(4, -INT_MAX, INT_MAX, board, myFlag);
	}
	else
	{
       ;
	}
}
//主函数==============================================================================
int main()
{
    Init.loop();
    return 0;
}