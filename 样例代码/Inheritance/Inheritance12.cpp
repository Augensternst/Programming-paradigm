//类的兼容性规则
//#include "stdafx.h"
#include <iostream>
using namespace std;

class Base
{ 
public:  
	void func() 
	{cout << "Base class function."<<endl;} 
};

class Derived : public Base
{ 
public:  
	void func() 
	{cout << "Derived class function."<<endl;}
};

void foo(Base b)
	{ b.func(); }

int main()
{
	Derived d;
	Base b;
	Base * p = &d;
	Base& br = d;
	b = d;
	b.func();
	d.func();
	p -> func();
	foo(d);
	br.func();
	system("pause");
	return 0;
}