//protected 访问控制属性在继承的意义 
//Example of treating derived class object as base class objects. Point------Circle
//#include "stdafx.h"
#include <iostream>
using namespace std;

//THE POINT CLASS
class Point
{ 
friend ostream & operator<<(ostream &,Circle&);
public:
Point (double xval =0, double yval=0 ) { x=xval; y=yval;};  
public:
void print()
{
cout <<" Point:X:Y: "<<x << "," <<y<< "/n";
}
protected:       // accessed by derived class
double  x;    double  y;
};
ostream & operator << (ostream & os, Point &  apoint)
{
cout <<" Point:X:Y: "<<apoint.x << ","<< apoint.y<< "/n";
  return os;  
}

//The Circle class  inherits from class Point
class Circle : public Point
{
friend ostream & operator<<(ostream &,Circle&);
public:
Circle (double r=0,double xval=0,double yval=0):Point(xval,yval)
{ radius = r;};
void print()
{
cout<< "Circle:radius:" <<radius<<endl;
cout <<" Point:X:Y: "<<x << "," <<y<< "/n";
}
double area()
{ return (3.14159* radius *radius);};
protected:
double radius;
};
//note casting circle to point
ostream & operator <<(ostream & os, Circle & aCircle)
{
cout<< "Circle:radius:" << aCircle.radius;
cout<< (Point) aCircle << "/n";           
return os;      
}

//We will look at a few main programs based on previous class definitions. Casting and assignments
int main (void )
{
Point p(2,3);         cout <<"Point P=  "<< p;
Point pp(0,0);       cout <<"Point PP=  "<< pp;
Circle c(7,6,5);     cout <<"Circle c=  "<< c;        //radius =7
pp = p;             cout <<"Point PP=  "<< pp;    //built in assign =
// a circle is a member of the point class so assign a circle to a point.
pp = c;           //legal; also assignment O.K.
cout <<"Point PP=  "<< pp;
pp= (Point) c;    // but better  use the cast
cout <<"Point PP=  "<< pp;  //note we get only the point part of the Circle
//c = (Circle) pp;   //  illegal Cannot convert 'class Point' to 'class Circle'
//c=pp;                 //illegal assignment not defined
Point*  p;
p = &c;
P->print();    //call base class print
((Circle*)p)->print();
Point& r = c;
r.print();
((Circle&)r).print();
system("pause");
return 0;
}
 
