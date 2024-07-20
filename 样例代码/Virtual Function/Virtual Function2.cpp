//#include "stdafx.h"
#include <iostream>    
using namespace std;
    
class A    
{    
public:    
    virtual void print()    
    { cout << "A::print()" <<endl;}    
};    
class B: public A    
{    
public:    
    virtual void print()    
    { cout << "B::print()" <<endl;}    
};    
class C: public A    
{    
public:    
    virtual void print()    
    { cout << "C::print()" <<endl;}    
};    
void print(A &a)    
{    
    a.print();    
}  
  
int main()    
{    
    A a,*aa,*ab,*ac;    
    B b;    
    C c;    
    aa=&a;    
    ab=&b;    
    ac=&c;    
    a.print();    
    b.print();    
    c.print();    
    aa->print();    
    ab->print();    
    ac->print();    
    print(a);    
    print(b);    
    print(c); 
	system("pause");
    return 0;
}    