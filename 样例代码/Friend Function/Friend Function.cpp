//#include "stdafx.h"
#include "math.h"
#include <iostream> 
using namespace std; 

class Point 
{ 
public: 
    Point(double xx, double yy) 
    {
        x=xx; 
        y=yy; 
    }
    void Getxy(); 
    friend double Distance(Point &a, Point &b);        //类Point的友元函数
    friend class Yao;                //类Point的友元类
private: 
    double x, y; 
}; 


class Yao
{
public:
    double Multi(Point &a)
    {
        return a.x * a.y + 1;
    }
};

void Point::Getxy() 
{ 
    cout<<"("<<x<<","<<y<<")"<<endl; 
} 

double Distance(Point &a, Point &b)            //类Point的友元函数
{ 
    double dx = a.x - b.x; 
    double dy = a.y - b.y; 
    return sqrt(dx*dx+dy*dy); 
} 

int main() 
{ 
    Point p1(3.0, 4.0), p2(6.0, 8.0); 
    p1.Getxy(); 
    p2.Getxy(); 
    double d = Distance(p1, p2);            //Distance是类Point的友元函数，不是成员函数
    cout<<"Distance is "<<d<<endl; 
    Yao yao;
    d = yao.Multi(p1);
    cout<<"Math.Multi is "<<d<<endl;
	system("pause");
    return 0;
}