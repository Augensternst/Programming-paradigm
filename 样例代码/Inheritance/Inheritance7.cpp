//Ðé»ùÀà
//#include "stdafx.h"
#include <iostream>
using namespace std;

class R
{ 
	    int r;
public:
        R (int x = 0) : r(x) { }             //constructor in R
        void f(){ cout<<"r="<<r<<endl;}     
        void printOn(){cout<<"printOn R="<<r<<endl;}
};

class A : public virtual R
{  
	    int a;
public:
        A (int x, int y) : R(x), a(y)  { }    //constructor in A
        void f(){ cout<<"a="<<a<<endl;R::f();}
};

class B : public virtual R
{
	    int b;
public:
        B(int x, int z) : R(x), b(z) { }      //constructor in B
        void f(){ cout<<"b="<<b<<endl;R::f();}
};

class C : public A, public B
{ 
	   int c;
public:
// constructor in C, which constructs an R object first
       C(int x, int y, int z, int w) : R(x), A(x, y), B(x, z), c(w) { }
       void f(){ cout<<"c="<<c<<endl;A::f(); B::f();}
};

int main()
{  
   R rr(1000);
   A aa(2222,444);
   B bb(3333,111);
   C cc(1212,345,123,45);
   cc.printOn();          //uses R printOn but only 1 R..no ambiguity
   cc.f();                //shows multiple call of the R::f()
   system("pause");
   return 0;
}