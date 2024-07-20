//¶à¼¶¼Ì³Ð
//Point-Circle-Cylinder
//#include "stdafx.h"
#include <iostream>
using namespace std;

//THE POINT CLASS
class Point
{
	friend ostream & operator<<(ostream &,Point &);
public:    
//constructor
	Point (double xval =0, double yval=0 )
    { x=xval; y=yval;};  
protected:       //accessed by derived class
    double  x;
    double  y;
};

ostream & operator << (ostream & os,Point & apoint)
{
	cout <<"Point:X:Y: "<<apoint.x << ","<<apoint.y <<endl;
	return os;  
}

//The Circle class inherits from Point class
class Circle : public Point
{
	friend ostream & operator<<(ostream &,Circle&);
public:
	Circle (double r=0,double xval=0,double yval=0) : Point(xval,yval), radius(r)
{ 
	//radius = r;
}

double area()
{ 
	return (3.14159* radius *radius);
}

protected:
	double radius;
};

//note casting circle to point
ostream & operator <<(ostream & os, Circle & aCircle)
{
	cout<< "Circle:radius: " << aCircle.radius <<endl;
	os<< aCircle.x <<endl; 
	os<< aCircle.y <<endl;        
	return os;      
}

//THE CYLINDER CLASS
class  Cylinder : public Circle
{
	friend ostream & operator << (ostream & ,Cylinder &);
public:
	Cylinder (double hv=0,double rv=0,double xv=0,double yv=0 ) : Circle( xv,yv,rv)
{
	height = hv;
}        
double area ();
protected:     //may have derived classes
	double  height;
};

double Cylinder :: area()
{ 
	//Note that cylinder area uses Circle area
	return  2.0* Circle::area() + 2.0*3.14159* radius*height;
}

ostream & operator << (ostream & os, Cylinder & acylinder)
{ 
	cout << "cylinder dimensions: ";
	cout << "x: " <<acylinder.x;
	cout << "  y: " <<acylinder.y ;
	cout << "  radius: " <<acylinder.radius ;
	cout << "  height: " <<acylinder.height <<endl;
	return os; 
}

int main()
{
	Point p(2,3);
	Circle c(7,6,5);
	Cylinder cyl(10,11,12,13);
	cout << p;
	cout << c;
	cout << "area of cirle:" << c.area() <<endl;
	cout<< cyl;
	cout<<"area of cylinder:"<< cyl.area()<<endl ;
	cout<<"area of cylinder base is " << cyl.Circle::area() <<endl;
	system("pause");
	return 0;
}
