// ReSharper disable All
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <list>
#include <algorithm>
#include <vector>
using namespace std;
// ����������Ϸ�ĳ���
#define BOARD_SIZE 12 // �������̴�СΪ12x12
#define EMPTY 0       // �ո�
#define BLACK 1       // ����
#define WHITE 2       // ����
#define EDGE 3        // �߽��ʶ
#define TRUE 1        // ��ֵ
#define FALSE 0       // ��ֵ
#define START "START" // ��ʼָ��
#define PLACE "PLACE" // ��������ָ��
#define TURN "TURN"   // �ֻ�ָ��
#define END "END"     // ����ָ��
int enemy = -1; //�з�
int ai = -1; //AI
int current = -1;//��ǰ
int new_aiX = -1; //AI��ǰ��������X
int new_aiY = -1; //AI��ǰ��������Y
int new_enemyX = -1; //�з���ǰ����λ��X
int new_enemyY = -1; //�з���ǰ����λ��Y
int board[BOARD_SIZE][BOARD_SIZE] = { 0 };//��ʼ������
int myFlag;//�ҷ���ɫ
int enemyFlag;//�з���ɫ
#define RIGHT 0//�������ҡ����ϡ����ϡ�����
#define UP 1
#define UPRIGHT 2
#define UPLEFT 3
//��������
struct Condition AI_low(int color);
int exact_chess_point_score(int black, int white, int color);
void run();
//�ṹ���ʾ������
struct point
{
    int x;
    int y;
};
//�ṹ�帴�Ƶ�
struct aid {
    int x;
    int y;
    aid(int x, int y) : x(x), y(y) {}
};
//�����ʾ
struct Condition
{
    int x;
    int y;
};
//��������
struct Final
{
    int x;
    int y;
    int SCORE;
}final;
//====================================================================================
//���̳�ʼ��������ά��
class init_chess_board
{
    friend class low_ai;
    friend class ai_pro;
private:
    //ָ��������������
    struct Command
    {
        int x;
        int y;
    };
public:
    void debug(const char* str);//debug���
    bool isInBound(int x, int y);//�ж��Ƿ���������
    void place(struct Command cmd);//�������ӣ��������̣��з���
    void initAI(int me);//ȷ�ϵ��ҷ���ɫ
    void start(int flag);//��ʼ������������̣���ʼ��ai
    void turn();//�ҷ�������
    void end(int x);//����
    void loop();//�غϽ����ѭ��
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
    enemyFlag = 3 - me; // ��ʼ���з���־λ
}
void init_chess_board::start(int flag)
{
    memset(board, 0, sizeof(board)); // �������
    int middlePlace = BOARD_SIZE / 2;
    // ��ʼ����ʼ���
    board[middlePlace - 1][middlePlace - 1] = WHITE;
    board[middlePlace][middlePlace] = WHITE;
    board[middlePlace - 1][middlePlace] = BLACK;
    board[middlePlace][middlePlace - 1] = BLACK;
    initAI(flag); // ��ʼ��AI
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
            //��ӡ���̣�����ʱ����
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
            scanf("%d", &myFlag); // ��ȡAI�ı�־λ
            start(myFlag);
            printf("OK\n");
            fflush(stdout);
        }
        else if (strcmp(tag, PLACE) == 0)
        {
            scanf("%d %d", &command.x, &command.y); // ��ȡ���ֵ�����λ��
            place(command); // �������Ϸ��ö��ֵ�����
        }
        else if (strcmp(tag, TURN) == 0)
        {
            turn(); // AI����
        }
        else if (strcmp(tag, END) == 0)
        {
            scanf("%d", &status); // ��ȡ�������
            end(status); // ��������
        }
    }
}
//====================================================================================
//���ߺ������֣����ڵͶ�ʵ�ֵĸĽ��������߶˵ıر����ߺ�����
//ʵ���㷨������ȫ�ּǷ֣����Ҫ�õ�
class low_ai
{
    friend class init_chess_board;
    friend class ai_pro;
public:
    struct point find(int row, int col, int pos, int num);//�ҵ��Ϊ���꣬pos�Ƿ���num�Ǳ�ʾ�����ϼ���
    int evaluate_point_score(int board[12][12], int x, int y, int color);// �����������������������ض������ĸ������ϵ��������λ�õĵ÷�
    int exact_chess_point_score(int black, int white, int color);//�����Ӧ���͵ľ���÷�
}Low;
// low_ai���find���������������ҵ��ض�����;���ĵ�
struct point low_ai::find(int row, int col, int pos, int num)
{
    struct point aim;
    if (pos == RIGHT) {
        aim.x = row;          // �����ƶ����в���
        aim.y = col + num;    // ������
    }
    else if (pos == UP) {
        aim.x = row - num;    // �����ƶ����м���
        aim.y = col;          // �в���
    }
    else if (pos == UPRIGHT) {
        aim.x = row - num;    // �������ƶ����м���
        aim.y = col + num;    // ������
    }
    else if (pos == UPLEFT) {
        aim.x = row - num;    // �������ƶ����м���
        aim.y = col - num;    // �м���
    }
    return aim;
}
// low_ai���evaluate_point_score����������������һ����ĵ÷�
int low_ai:: evaluate_point_score(int board[12][12], int x, int y, int color) {
    int sum = 0;
    for (int i = 0; i < 4; i++) {//�ĸ�����
        for (int j = 0; j < 5; j++) {//ÿ�����������5����Ԫ��
            struct point start = find(x, y, RIGHT + i, j - 4);//��Ԫ�鶥��λ��
            struct point  end = find(start.x, start.y, RIGHT + i, 4);//��Ԫ����Զλ��
            // ȷ����Ԫ�����ʼ�ͽ����㶼��������
            if (Init.isInBound(start.x, start.y) && Init.isInBound(end.x, end.y)) {//����Ԫ���±���Ϸ�
                int blackChess = 0;
                int whiteChess = 0;
                // ������Ԫ���е�ÿ��λ��
                for (int k = 0; k < 5; k++) {//����Ԫ��5��λ�ÿ���
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
// low_ai���exact_chess_point_score�������������ͼ������÷�
int low_ai::exact_chess_point_score(int black, int white, int color)
{
    //��5
    if (color == BLACK && black == 5)
        return 999999999;
    if (color == WHITE && white == 5)
        return 999999999;
    //ȫ��
    if (black == 0 && white == 0)
        return 10;
    //�����޷��жϣ���������
    else if (black >= 1 && white >= 1)
        return 0;
    //�����ж�
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
//�����Сֵ�㷨�ͼ�֦�㷨ʵ�֣��߶�ʵ�֣�
//��������Ȩ��(��԰��壩
#define WIN 1
#define LOSE 2
#define DRAW  3
#define OTHER 0//��������
#define W_LIVE_4 1//�׻�4
#define B_LIVE_4 2//�ڻ�4
#define W_AIM_4 3//�׳�4
#define B_AIM_4 4//�ڳ�4
#define W_LIVE_3 5//�׻�3
#define B_LIVE_3 6//�ڻ�3
#define W_SLEEP_3 7//����3
#define B_SLEEP_3 8//����3
#define W_LIVE_2 9//�׻�2
#define B_LIVE_2 10//�ڻ�2
#define W_SLEEP_2 11//����2
#define B_SLEEP_2 12//����2
#define W_LIVE 13//�׻�1
#define B_LIVE 14//�ڻ�1
#define W_WIN 15//��Ӯ
#define B_WIN 16//��Ӯ
class ai_pro
{
    friend class low_ai;
    friend class init_chess_board;
private:
    int chess_arr[4][4][4][4][4][4];//������Ԫ���鴢������
    int score;//����
    int big[14][14];//������
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
    void copy_board(int arr_1[12][12], int arr_2[12][12], int color);//���ƴ������̱�Ե�Ĵ�����(��תɫ��
    void init_complete_board(int arr[12][12]);//��ʼ������Ե������
    void init_chess_array_kind_1();//��ʼ���Ǳ�Ե����
    void init_chess_array_kind_2();//��ʼ����Ե����
    void calculation_score(int arr[12][12],int color);//���������������
	best_point find_best_point(int color,int arr[12][12]);//Ѱ�ҵ�
    int mock(int depth, int alpha, int beta,int arr[12][12],int color);//ģ������
    vector<aid>find_kill_chess(int arr[12][12],int color);//Ѱ����ɱ��
    bool whether_kill(int depth, int arr[12][12],int color);//ʵ����ɱ
}High;
ai_pro::ai_pro()
{
    score = 0;
}
//���ƴ������̱�Ե�Ĵ�����(��תɫ��
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
//��ʼ������Ե������
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
//��ʼ���Ǳ�Ե����
void ai_pro::init_chess_array_kind_1()
{
    memset(chess_arr, 0, sizeof(chess_arr));
    //�׻�4
    chess_arr[0][2][2][2][2][0] = W_LIVE_4;
    //�ڻ�4
    chess_arr[0][1][1][1][1][0] = B_LIVE_4;
    //�׻�3
    chess_arr[0][2][2][2][0][0] = W_LIVE_3;
    chess_arr[0][0][2][2][2][0] = W_LIVE_3;
    chess_arr[0][2][0][2][2][0] = W_LIVE_3;
    chess_arr[0][2][2][0][2][0] = W_LIVE_3;
    //�ڻ�3
    chess_arr[0][1][1][1][0][0] = B_LIVE_3;
    chess_arr[0][0][1][1][1][0] = B_LIVE_3;
    chess_arr[0][1][0][1][1][0] = B_LIVE_3;
    chess_arr[0][1][1][0][1][0] = B_LIVE_3;
    //�׻�2
    chess_arr[0][2][2][0][0][0] = W_LIVE_2;
    chess_arr[0][2][0][2][0][0] = W_LIVE_2;
    chess_arr[0][2][0][0][2][0] = W_LIVE_2;
    chess_arr[0][0][2][2][0][0] = W_LIVE_2;
    chess_arr[0][0][2][0][2][0] = W_LIVE_2;
    chess_arr[0][0][0][2][2][0] = W_LIVE_2;
    //�ڻ�2
    chess_arr[0][1][1][0][0][0] = B_LIVE_2;
    chess_arr[0][1][0][1][0][0] = B_LIVE_2;
    chess_arr[0][1][0][0][1][0] = B_LIVE_2;
    chess_arr[0][0][1][1][0][0] = B_LIVE_2;
    chess_arr[0][0][1][0][1][0] = B_LIVE_2;
    chess_arr[0][0][0][1][1][0] = B_LIVE_2;
    //�׻�1
    chess_arr[0][2][0][0][0][0] = W_LIVE;
    chess_arr[0][0][2][0][0][0] = W_LIVE;
    chess_arr[0][0][0][2][0][0] = W_LIVE;
    chess_arr[0][0][0][0][2][0] = W_LIVE;
    //�ڻ�1
    chess_arr[0][1][0][0][0][0] = B_LIVE;
    chess_arr[0][0][1][0][0][0] = B_LIVE;
    chess_arr[0][0][0][1][0][0] = B_LIVE;
    chess_arr[0][0][0][0][1][0] = B_LIVE;
    //��Ӯ
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
//��ʼ����Ե����
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
                            //forѭ������
                            //�����Ե���
                            if(a1==EDGE||a6==EDGE)
                            {
	                            if(a1==EDGE&&a6!=EDGE)
	                            {
		                            if(right_black==4&&right_white==0)//�ڳ�4
		                            {
                                        chess_arr[a1][a2][a3][a4][a5][a6] = B_AIM_4;
		                            }
                                    if(right_black==3&&right_white==0)//����3
                                    {
                                        chess_arr[a1][a2][a3][a4][a5][a6] = B_SLEEP_3;

                                    }
                                    if(right_black==2&&right_white==0)//����2
                                    {
                                        chess_arr[a1][a2][a3][a4][a5][a6] = B_SLEEP_2;
                                    }
                                    if (right_black == 0 && right_white == 4)//�׳�4
                                    {
                                        chess_arr[a1][a2][a3][a4][a5][a6] = W_AIM_4;
                                    }
                                    if (right_black == 0 && right_white == 3)//����3
                                    {
                                        chess_arr[a1][a2][a3][a4][a5][a6] = W_SLEEP_3;

                                    }
                                    if (right_black == 0 && right_white == 2)//����2
                                    {
                                        chess_arr[a1][a2][a3][a4][a5][a6] = W_SLEEP_2;
                                    }
	                            }
                                if(a1!=EDGE&&a6==EDGE)
                                {
                                    if (left_black == 4 && left_white == 0)//�ڳ�4
                                    {
                                        chess_arr[a1][a2][a3][a4][a5][a6] = B_AIM_4;
                                    }
                                    if (left_black == 3 && left_white == 0)//����3
                                    {
                                        chess_arr[a1][a2][a3][a4][a5][a6] = B_SLEEP_3;

                                    }
                                    if (left_black == 2 && left_white == 0)//����2
                                    {
                                        chess_arr[a1][a2][a3][a4][a5][a6] = B_SLEEP_2;
                                    }
                                    if (left_black == 0 && left_white == 4)//�׳�4
                                    {
                                        chess_arr[a1][a2][a3][a4][a5][a6] = W_AIM_4;
                                    }
                                    if (left_black == 0 && left_white == 3)//����3
                                    {
                                        chess_arr[a1][a2][a3][a4][a5][a6] = W_SLEEP_3;

                                    }
                                    if (left_black == 0 && left_white == 2)//����2
                                    {
                                        chess_arr[a1][a2][a3][a4][a5][a6] = W_SLEEP_2;
                                    }
                                }
                            }
                            else
                            {
                                //�׳�4
                                if ((right_black == 0 && right_white == 4) || (left_black == 0 && left_white == 4)) {
                                    
                                    chess_arr[a1][a2][a3][a4][a5][a6] = W_AIM_4;
                                }
                                //�ڳ�4
                                if ((right_black == 4 && right_white == 0) || (left_black == 4 && left_white == 0)) {
                                   
                                    chess_arr[a1][a2][a3][a4][a5][a6] = B_AIM_4;
                                }
                                //����3
                                if ((right_black == 0 && right_white == 3) || (left_black == 0 && left_white == 3)) {
                                    
                                    chess_arr[a1][a2][a3][a4][a5][a6] = W_SLEEP_3;
                                }
                                //����3
                                if ((right_black == 3 && right_white == 0) || (left_black == 3 && left_white == 0)) {
                                   
                                    chess_arr[a1][a2][a3][a4][a5][a6] = B_SLEEP_3;
                                }
                                //����2
                                if ((right_black == 0 && right_white == 2) || (left_black == 0 && left_white == 2)) {
                                   
                                    chess_arr[a1][a2][a3][a4][a5][a6] = W_SLEEP_2;
                                }
                                //����2
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
//���������������
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

   int sum_type[4][17] = {{0}};//�ĸ���������������
   int type_num = 0;
   init_complete_board(arr);
   //���ĸ�������������������Ϣ

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
    //�ǵô���score��result��ʼ������
}
//Ѱ�ҵ�
ai_pro::best_point ai_pro::find_best_point(int color,int arr[12][12])
{
    struct best_point best;
    int worth = -1;
    bool check[12][12]={false};
    int point_value[12][12];
    //��������Ƚ��б���
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            if (arr[i][j] != EMPTY) {
                // ��ǵ�ǰλ��
                check[i][j] = true;
                // ��鵱ǰλ�õ������Ҳ�����λ��
                for (int k = -3; k <= 3; k++) {
                    if (i + k >= 0 && i + k < 12) {
                        // ������λ��
                        check[i + k][j] = true;
                        
                        if (j + k >= 0 && j + k < 12) {
                            // ������ϽǺ����Ͻ�λ��
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
        //ģ������
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
//ģ������
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
//Ѱ����ɱ��
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
//ʵ����ɱ
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
//�ڶ�����ʵ��
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
//������==============================================================================
int main()
{
    Init.loop();
    return 0;
}