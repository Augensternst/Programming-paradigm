//´¿Ðéº¯Êý£¬¶àÌ¬
//#include "stdafx.h"
#include <iostream>
#include <cmath>
using namespace std;  

class Point
{
private:
        double x;
        double y;
public:
        Point(double i, double j) : x(i), y(j) { } 
        void print() const
        { cout << "(" << x << ", " << y << ")"; }
};
class Figure
{
private:
        Point center;
public:
        Figure (double i = 0, double j = 0) : center(i, j) { }         
        
Point& location()
{
	return center;
}   // return an lvalue

void move(Point p)
{
	center = p;
	draw();
}
virtual void draw() = 0; // draw the figure
virtual void rotate(double) = 0; 
// rotate the figure by an angle                
};
class Circle : public Figure
{
private:
        double radius;
public:
        Circle(double i = 0, double j = 0, double r = 0) : Figure(i, j), radius(r) { }
        void draw()
        {
                cout << "A circle with center ";
                location().print();
                cout << " and radius " << radius << endl;
        }
        void rotate(double)
        {
                cout << "no effect."<< endl;
        }        // must be defined
};
class Square : public Figure
{
private:
        double side;        // length of the side
        double angle;       // the angle between a side and the x-axis
public:
        Square(double i = 0, double j = 0, double d = 0, double a = 0): Figure(i, j), side(d), angle(a) { }
		void draw()
        {
             cout << "A square with center ";
             location().print();
             cout << " side length " << side << endl;  
             cout<< "The angle between one side and the X-axis is " << angle << endl;
        }
        void rotate(double a)
        {
             angle += a;
             cout << "The angle between one side and the X-axis is " << angle << endl;
        }
        void vertices()
        {
             cout << "The vertices of the square are:"<< endl;
             // calculate coordinates of the vertices of the square
          }
};

int main()
{
        Circle c(1, 2, 3);
        Square s(4, 5, 6);
		Figure *f = &c, &g = s;
        f -> draw();
        f -> move(Point(2, 2));
        g.draw();
        g.rotate(1);
        
		s.vertices();
		// Cannot use g here since vertices() is not a member of Figure.
		system("pause");
        return 0;
}