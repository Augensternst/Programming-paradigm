
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
//�������͵Ĵ��� /Ȩ�� �Ż��棨δ��ɣ�
#define OTHER 0//��������
#define WIN 1//1000000,��Ӯ
#define LOSE 2//-10000000
#define FLEX4 3//50000,�׻�4
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
//�ṹ���ʾ������
struct point
{
    int x;
    int y;
};
//�з������ʾ
struct Condition
{
    int x;
    int y;
};
//ָ��������������
struct Command
{
    int x;
    int y;
};
//debug���
void debug(const char* str)
{
    printf("DEBUG %s\n", str);
    fflush(stdout);
}
//�ж��Ƿ���������
BOOL isInBound(int x, int y)
{
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}
//�������ӣ��������̣��з���
void place(struct Command cmd)
{
    if (board[cmd.x][cmd.y] == EMPTY) {
        board[cmd.x][cmd.y] = enemyFlag;
    }
    else {
        debug("Position already occupied");
    }
}
//ȷ�ϵ��ҷ���ɫ
void initAI(int me)
{
    enemyFlag = 3 - me; // ��ʼ���з���־λ
}
//��ʼ������������̣���ʼ��ai
void start(int flag)
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
//����
struct Condition AI_low(int color);
int exact_chess_point_score(int black, int white, int color);
//�ҷ�������
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
//����
void end(int x)
{
    exit(0);
}
//�غϽ����ѭ��
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
struct EVALUATION {
    int score;
    int FEW[8];//���沿�����εĸ���,�±�WIN=1Ϊ����5,LOSE=2Ϊ����5,FLEX4=3Ϊ�׻�4,BLOCK4=5Ϊ�׳�4,FLEX3=7Ϊ�׻�3
};
struct BEST {//�������λ��,[0]�������,[19]�������
    struct point pos[20];
    int score[20];//�˴����ӵľ��Ʒ���
};
struct DECISION {
    struct point pos;//λ��
    int eval;//�Է���������
};
//AI����
struct chess_ai {
    struct EVALUATION evaluation;
    struct BEST best;
    struct DECISION decision;
    int score[4][4][4][4][4][4];//��������,�������Ƴ��Ͼ��Ʒ���
};
//�ҵ��Ϊ���꣬pos�Ƿ���num�Ǳ�ʾ�����ϼ���
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
// ̰���㷨����
// �����������������������ض������ĸ������ϵ��������λ�õĵ÷�
int evaluate_point_score(int board[12][12], int x, int y, int color) {
    int sum = 0;
    for (int i = 0; i < 4; i++) {//�ĸ�����
        for (int j = 0; j < 5; j++) {//ÿ�����������5����Ԫ��
            struct point start = find(x, y, RIGHT + i, j - 4);//��Ԫ�鶥��λ��
            struct point  end = find(start.x, start.y, RIGHT + i, 4);//��Ԫ����Զλ��
            if (isInBound(start.x, start.y) && isInBound(end.x, end.y)) {//����Ԫ���±���Ϸ�
                int blackChess = 0;
                int whiteChess = 0;
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
//�����Ӧ���͵ľ���÷�
int exact_chess_point_score(int black, int white, int color)
{
    //��5
    if (color == BLACK && black == 5)return 999999999;
    if (color == WHITE && white == 5)return 999999999;
    //ȫ��
    if (black == 0 && white == 0)return 10;
    //�����޷��жϣ���������
    else if (black >= 1 && white >= 1)return 0;
    //�����ж�
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
//�Ͷ�ʵ��
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
//������
int main(int argc, char* argv[])
{
    loop();
    return 0;
}